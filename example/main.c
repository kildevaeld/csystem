#include <csystem/terminal/terminal.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int print_line(const char *msg, bool highlight) {
  int len = strlen(msg) + 20;
  char buf[len];
  if (!highlight)
    snprintf(buf, len, "%s\r", msg);
  else
    snprintf(buf, len, "\x1b[7m%s\x1b[0m\r", msg);
  write(STDOUT_FILENO, buf, strlen(buf));
}

int input(const char *msg, const char *list[], size_t len) {
  cs_term_enable_raw_mode();

  char buf[strlen(msg) + 3];
  snprintf(buf, strlen(msg) + 3, "%s\r\n", msg);
  write(STDOUT_FILENO, buf, strlen(buf));
  for (int i = 0; i < len; i++) {
    print_line(list[i], i == 0);
    write(STDOUT_FILENO, "\n", 1);
  }
  cs_term_cursor_up(len);
  int i = 0;
  while (1) {
    int c = cs_term_read_key();
    switch (c) {
    case CS_CTRL_KEY('c'):
      i = -1;
      goto end;
    case ARROW_DOWN:
      if (i >= len - 1)
        break;
      cs_term_erase_line();
      print_line(list[i], 0);

      cs_term_cursor_down(1);
      print_line(list[++i], 1);
      break;
    case ARROW_UP:
      if (i == 0)
        break;
      cs_term_erase_line();
      print_line(list[i], 0);

      cs_term_cursor_up(1);
      print_line(list[--i], 1);

      break;
    case ENTER_KEY:
      goto end;
    }
  }

end:

  do {
    int diff = len - i;
    int l = len;
    cs_term_cursor_down(diff);
    while (len--) {
      cs_term_erase_line();
      cs_term_cursor_up(1);
    }
  } while (0);

  cs_term_cursor_up(1);
  int slen = strlen(msg) + 1 + strlen(list[i]) + 4;
  char sbuf[slen];
  snprintf(sbuf, slen, "%s %s\r\n", msg, list[i]);
  write(STDOUT_FILENO, sbuf, strlen(sbuf));
  cs_term_disable_raw_mode();
  return i;
}

int main() {
  // cs_term_clear_screen();
  /*cs_term_enable_raw_mode();
  cs_term_cursor_pos_set(20 - 4, 10);
  char c = cs_term_read_key();
  printf("%c\n", c);
  int x, y;
  cs_term_cursor_pos_get(&y, &x);
  printf("%i, %i\n", x, y);*/
  /*cs_term_enable_raw_mode();
  while (1) {
    int c = cs_term_read_key();
    switch (c) {
    case CS_CTRL_KEY('c'):
      return 0;
    }
    write(STDOUT_FILENO, "1", 1);
  }
  int c = cs_term_read_key();
  printf("%c", c);*/

  const char *list[] = {"lwg", "ost", "test", "mig i øret"};

  int c = input("valg:", list, 4);
  if (c > -1) {
    printf("picked %s\n", list[c]);
  }

  return 0;
}