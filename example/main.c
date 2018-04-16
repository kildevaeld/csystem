#include <csystem/terminal/form.h>
#include <csystem/terminal/terminal.h>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

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

  /*const char *list[] = {"lwg", "ost", "test", "mig i øret"};

  int c = cs("valg:", list, 4);
  if (c > -1) {
    printf("picked %s\n", list[c]);
  }*/

  char *out = cs_term_form_input("test mig:");
  printf("OUT %s\n", out);
  free(out);
  return 0;
}