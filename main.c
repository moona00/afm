#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define TEMPFILE "afm_temp.dat"

void add(char *);
void del(char *);
int do_cmd(char *, char *);
char is_folder(char *);

int main(int argc, char *argv[]) {
  system("ls");

  while (1) {
    char *mode = malloc(2);
    char *arg = malloc(FILENAME_MAX + 2);
    scanf("%s %s", mode, arg);

    switch (mode[0]) {
    case '+':
      add(arg);
      break;

    case '-':
      del(arg);
      break;

    case 'e':
      do_cmd("vim %s", arg);
      break;

    case 'b':
      do_cmd("./%scompile.sh", arg[0] == '.' ? "" : arg);
      break;

    case 'r':
      do_cmd("./%s", arg);
      break;

    case 'm':
      if (!do_cmd("cd %s;\nafm .", arg)) {
        goto quit;
      }
      system("ls");
      break;

    case 'q':
      goto quit;

    default:
      break;
    }

    free(mode);
    free(arg);
  }

quit:
  return argc - 1;
}

void add(char *n) { is_folder(n) ? mkdir(n, 0777) : creat(n, 0777); }

void del(char *n) { is_folder(n) ? rmdir(n) : remove(n); }

int do_cmd(char *s1, char *s2) {
  char *cmd = malloc(FILENAME_MAX);
  sprintf(cmd, s1, s2);
  int ret = system(cmd);
  free(cmd);
  return ret;
}

char is_folder(char *n) { return n[strlen(n) - 1] == '/'; }
