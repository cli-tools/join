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
  int c;

  while ((c = getopt (argc, argv, "rd:")) != -1) {
    switch (c) {
      case 'r':
        truncate_empty_records = 1;
        break;
      case 'd':
        sep = optarg;
        break;
    }
  }

  do
  {
    size_t rc = 0;
    char * record = NULL;
    size_t n = 0;
    while (getline(&record, &n, stdin) > 0)
    {
      record[strcspn(record, "\r\n")] = 0; /* credit: https://stackoverflow.com/a/28462221/3504575 */
      if (truncate_empty_records && strlen(record) == 0) {
        free(record);
        record = NULL;
        n = 0;
        continue;
      }
      rc++;
      if (rc > 1) {
        fputs(sep, stdout);
      }
      fputs(record, stdout);
      free(record);
      record = NULL;
      n = 0;
    }
  }
  while (0);
  fputc('\n', stdout);
  return 0;
}
