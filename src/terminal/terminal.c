#include <csystem/terminal/terminal.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k)&0x1f)

struct Terminal {
  struct termios orig_termios;
  int cx;
  int cy;
};

struct Terminal T;

struct termios orig_termios;

bool cs_term_disable_raw_mode() {
  return tcsetattr(STDIN_FILENO, TCSAFLUSH, &T.orig_termios) == -1;
}

bool cs_term_enable_raw_mode() {
  if (tcgetattr(STDIN_FILENO, &T.orig_termios) == -1)
    return false;
  atexit(cs_term_disable_raw_mode);
  struct termios raw = T.orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    return false;
  return true;
}

void cs_term_clear_screen() { write(STDOUT_FILENO, "\x1b[2J", 4); }

int cs_term_read_key() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN)
      return '\0';
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1)
      return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
      return '\x1b';
    if (seq[0] == '[') {
      if (seq[1] >= '0' && seq[1] <= '9') {
        if (read(STDIN_FILENO, &seq[2], 1) != 1)
          return '\x1b';
        if (seq[2] == '~') {
          switch (seq[1]) {
          case '1':
            return HOME_KEY;
          case '3':
            return DEL_KEY;
          case '4':
            return END_KEY;
          case '5':
            return PAGE_UP;
          case '6':
            return PAGE_DOWN;
          case '7':
            return HOME_KEY;
          case '8':
            return END_KEY;
          }
        }
      } else {
        switch (seq[1]) {
        case 'A':
          return ARROW_UP;
        case 'B':
          return ARROW_DOWN;
        case 'C':
          return ARROW_RIGHT;
        case 'D':
          return ARROW_LEFT;
        case 'H':
          return HOME_KEY;
        case 'F':
          return END_KEY;
        }
      }
    } else if (seq[0] == 'O') {
      switch (seq[1]) {
      case 'H':
        return HOME_KEY;
      case 'F':
        return END_KEY;
      }
    }
    return '\x1b';
  } else {
    return c;
  }
}

int cs_term_cursor_pos_get(int *rows, int *cols) {
  char buf[32];
  unsigned int i = 0;
  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
    return -1;
  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1)
      break;
    if (buf[i] == 'R')
      break;
    i++;
  }
  buf[i] = '\0';
  if (buf[0] != '\x1b' || buf[1] != '[')
    return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
    return -1;
  return 0;
}

void cs_term_cursor_pos_set(int row, int col) {
  char buf[32];
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH", row + 1, col + 1);
  write(STDIN_FILENO, buf, strlen(buf));
}

int cs_term_size(int *rows, int *cols) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
      return -1;
    return cs_term_cursor_pos_get(rows, cols);
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}