
#include <stdio.h>

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
  if (parseArgs(argc, argv)) return -1;

  printf("args: %s %s %s\n", args.infile1, args.infile2, args.outfile);

  return 0;
}
