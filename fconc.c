
#include <stdio.h>  // printf() etc
#include <stdlib.h> // exit()

#include <sys/types.h> // open()
#include <sys/stat.h>  // open()
#include <fcntl.h>     // open()

#include <unistd.h> // close()


void ifdie(int condition, const char *message)
{
  if (condition) {
    perror(message); // ok if message is NULL
    exit(-1);
  }
}

const char usageMessage[] = "Usage: ./fconc infile1 infile2 [outfile (default:fconc.out)]\n";
const char tempOutfile[] = "fconc.out.temp";
const char defaultOutfile[] = "fconc.out";
const ssize_t blockSize = 4 * 1024; // 4 KiB

struct {
  const char *infile1;
  const char *infile2;
  const char *outfile;
} args;

int parseArgs(int argc, char **argv)
{
  if (argc < 3) {
    printf("Too few arguements\n");
    printf(usageMessage);
    return -1;
  }
  else if (argc > 4) {
    printf("Too many arguements\n");
    printf(usageMessage);
    return -1;
  }

  args.infile1 = argv[1];
  args.infile2 = argv[2];
  args.outfile = (argc > 3) ? argv[3] : defaultOutfile;

  return 0;
}

void write_file(int outfileFD, const char *infile)	{
  int infileFD = open(infile, O_RDONLY);
  ifdie(infileFD < 0, infile);

  char buffer[blockSize];
  ssize_t readCount;
  do {
    readCount = read(infileFD, buffer, sizeof(buffer));
    ifdie(readCount < 0, infile);
    write(outfileFD, buffer, readCount);
  } while (readCount == blockSize);

  ifdie(close(infileFD) < 0, infile);
}

int main(int argc, char **argv)
{
  if (parseArgs(argc, argv) < 0) return -1;

  int outfileFD = open(tempOutfile,
                       O_CREAT | O_WRONLY | O_TRUNC,
                       S_IRUSR | S_IWUSR);

  write_file(outfileFD, args.infile1);
  write_file(outfileFD, args.infile2);

  ifdie(close(outfileFD) < 0, "Can't close temporary output file");

  ifdie(rename(tempOutfile, args.outfile) < 0, args.outfile);

  return 0;
}
