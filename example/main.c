#include <csystem/terminal/terminal.h>
#include <stdio.h>

int main() {
  // cs_term_clear_screen();
  cs_term_enable_raw_mode();
  cs_term_cursor_pos_set(20 - 4, 10);
  char c = cs_term_read_key();
  printf("%c\n", c);
  int x, y;
  cs_term_cursor_pos_get(&y, &x);
  printf("%i, %i\n", x, y);

  return 0;
}