#pragma once

#include <stdbool.h>
//#include <termios.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

// 0xc0 == (0xe0 & c)

#define CS_CTRL_KEY(k) ((k)&0x1f)
/*#define CS_UTF8_4C(k) (0xf0 == (0xf8 & (k)))
#define CS_UTF8_3C(k) (0xe0 == (0xf0 & (k)))
#define CS_UTF8_2C(k) (0xc0 == (0xe0 & (k)))
#define CS_UTF(k) (CS_UTF8_4C(k) || CS_UTF8_3C(k) || CS_UTF8_2C(k))*/

enum cs_term_control_keys_t {
  ENTER_KEY = 13,
  BACKSPACE = 127,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN,

  UNICODE_4C,
  UNICODE_3C,
  UNICODE_2C
};

bool cs_term_enable_raw_mode();

bool cs_term_disable_raw_mode();

void cs_term_clear_screen();

int cs_term_read_key();
void cs_term_nread_key(char *buf, int c);

int cs_term_cursor_pos_get(int *row, int *col);
void cs_term_cursor_pos_set(int row, int col);

void cs_term_cursor_up(int n);
void cs_term_cursor_down(int n);
void cs_term_cursor_forward(int n);
void cs_term_cursor_backward(int n);
void cs_term_erase_line();
void cs_term_erase_current_line();
void cs_term_cursor_show();
void cs_term_cursor_hide();

int cs_term_size(int *rows, int *cols);

#ifdef __cplusplus
}
#endif