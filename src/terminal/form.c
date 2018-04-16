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

void print_input(const char *msg, cs_string_t *str) {
  int len = strlen(msg) + 3 + cs_str_len(str);
  char buf[len + 1];
  int x, y;
  // cs_term_cursor_pos_get(&y, &x);
  // cs_term_erase_current_line();
  snprintf(buf, strlen(msg) + 3, "\r%s ", msg);
  // write(STDOUT_FILENO, buf, strlen(buf));
  cs_str_copy(str, buf + strlen(msg) + 3);
  buf[len] = '\0';
  write(STDOUT_FILENO, buf, len);
  // cs_term_cursor_pos_set(y, x);
}

char *cs_term_form_input(const char *msg) {
  cs_term_enable_raw_mode();

  char buf[strlen(msg) + 3];
  snprintf(buf, strlen(msg) + 3, "%s ", msg);
  write(STDOUT_FILENO, buf, strlen(buf));

  cs_string_t *str = cs_str_alloc();
  int idx = strlen(str) + 3;
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
      if (cur >= cs_str_len(str))
        break;
      cur++;
      cs_term_cursor_forward(1);
      break;
    case BACKSPACE:
      if (cur == idx)
        break;
      cs_str_remove(str, cur--, 1);
      print_input(msg, str);
      cs_term_cursor_backward(1);
      break;
    default: {
      // char buf[1];
      // buf[0] = key;
      // write(STDOUT_FILENO, buf, 1);
      cs_str_append_char(str, key);
      print_input(msg, str);
      cur++;
    }
    }
  }

end:
  cs_term_disable_raw_mode();
  return NULL;
}