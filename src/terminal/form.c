#include <csystem/string.h>
#include <csystem/terminal/form.h>
#include <csystem/terminal/terminal.h>
#include <stdio.h>

static int print_line(const char *msg, bool highlight) {
  int len = strlen(msg) + 20;
  char buf[len];
  if (!highlight)
    snprintf(buf, len, "%s\r", msg);
  else
    snprintf(buf, len, "\x1b[7m%s\x1b[0m\r", msg);
  write(STDOUT_FILENO, buf, strlen(buf));
}

int cs_term_form_list(const char *msg, const char **list, size_t len) {
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

bool cs_term_form_confirm(const char *msg, bool clear) {
  cs_term_enable_raw_mode();

  char buf[strlen(msg) + 3];
  snprintf(buf, strlen(msg) + 3, "%s ", msg);
  write(STDOUT_FILENO, buf, strlen(buf));
  bool ret = false;
  char *result = NULL;
  while (1) {
    int c = cs_term_read_key();

    switch (c) {
    case 'j':
    case 'y':
      ret = true;
      result = "yes\r\n";
      goto end;
    case 'n':
      result = "no\r\n";
      goto end;
    }
  }

end:

  if (clear) {
    cs_term_erase_current_line();
    write(STDOUT_FILENO, "\r", 1);
  } else {
    write(STDOUT_FILENO, result, strlen(result));
  }

  cs_term_disable_raw_mode();

  return ret;
}

void print_input(cs_string_t *str, int row, int col) {
  cs_term_erase_current_line();
  char buf[cs_str_len(str) + 1];
  buf[0] = '\r';
  cs_str_copy(str, buf + 1);
  write(STDOUT_FILENO, buf, cs_str_len(str) + 1);
  cs_term_cursor_pos_set(row, col);
}

char *cs_term_form_input(const char *msg) {
  cs_term_enable_raw_mode();

  size_t msg_l = strlen(msg) + 2;

  cs_string_t *str = cs_str_alloc();
  cs_str_appendf(str, "%s ", msg);

  int row, col;
  cs_term_cursor_pos_get(&row, &col);

  print_input(str, row, msg_l - 1);

  int idx = msg_l;
  int cur = idx;
  while (1) {
    int key = cs_term_read_key();

    switch (key) {
    case CS_CTRL_KEY('c'):
      goto end;
    case ARROW_LEFT:
      if (idx == cur)
        break;
      cur--;
      cs_term_cursor_backward(1);
      break;
    case ARROW_RIGHT:
      if (cur >= cs_str_len(str) + idx)
        break;
      cur++;
      cs_term_cursor_forward(1);
      break;
    case BACKSPACE:
      if (cur <= idx)
        break;
      cur--;
      cs_term_cursor_backward(1);
      cs_str_remove(str, cur - 1, 1);
      print_input(str, row, cur - 1);
      break;
    case ENTER_KEY:
      write(STDOUT_FILENO, "\n\r", 2);
      goto end;
    case ARROW_DOWN:
    case ARROW_UP:
      break;
    default: {
      cs_str_insert_char(str, cur - 1, key);
      print_input(str, row, cur);
      cur++;
    }
    }
  }

end:
  cs_term_disable_raw_mode();
  cs_str_remove(str, 0, msg_l - 1);
  char *out = cs_str_string(str);
  cs_str_free(str);
  return out;
}