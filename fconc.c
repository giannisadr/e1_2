
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
const char defaultOutfile[] = "fconc.out";

struct {
  const char *infile1;
  const char *infile2;
  const char *outfile;
} args;

void printUsage()
{
  printf(usageMessage);
}

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

int main(int argc, char **argv)
{
  if (parseArgs(argc, argv) < 0) return -1;

  int infile1FD = open(args.infile1, O_RDONLY);
  ifdie(infile1FD < 0, args.infile1);

  int infile2FD = open(args.infile2, O_RDONLY);
  ifdie(infile2FD < 0, args.infile2);

  printf("%d %d\n", infile1FD, infile2FD);

  ifdie(close(infile1FD) < 0, args.infile1);
  ifdie(close(infile2FD) < 0, args.infile2);

  return 0;
}
