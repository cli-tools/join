#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int getopt(int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;

ssize_t getline(char **lineptr, size_t *n, FILE *stream);
ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);

int
main(int argc, char **argv)
{
  char * sep = " ";
  int truncate_empty_records = 0;
  int trailing_newline = 1;
  size_t rc = 0;
  int c;

  while ((c = getopt (argc, argv, "hd:nr")) != -1) {
    switch (c) {
      case 'd':
        sep = optarg;
        break;
      case 'h':
        puts("Usage: join [OPTION]...\n"
             "Join line records together on a single line delimited by spaces.\n"
             "\n"
             "   -d DELIMITER          use DELIMITER string as output record delimiter\n"
             "   -n                    do not output the trailing newline\n"
             "   -r                    ignore empty line records from input\n"
             "\n"
             "join source code: <https://github.com/cli-tools/join/>\n"
             "join community: <https://gitter.im/cli-tools/community>\n"
             );
        exit(EXIT_SUCCESS);
        break;
      case 'n':
        trailing_newline = 0;
        break;
      case 'r':
        truncate_empty_records = 1;
        break;
      default:
        fputs("Try 'join -h' for more information.\n", stderr);
        exit(EXIT_FAILURE);
    }
  }

  while (1)
  {
    char * record = NULL;
    size_t n = 0;
    if (getline(&record, &n, stdin) < 0) {
      break;
    }
    /* Credit: https://stackoverflow.com/a/28462221/3504575 */
    record[strcspn(record, "\r\n")] = 0;
    if (truncate_empty_records && strlen(record) == 0) {
      free(record);
      continue;
    }
    rc++;
    if (rc > 1) {
      fputs(sep, stdout);
    }
    fputs(record, stdout);
    free(record);
  }
  if (trailing_newline) {
    fputc('\n', stdout);
  }
  exit(EXIT_SUCCESS);
}
