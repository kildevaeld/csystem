#pragma once
#include <stdbool.h>

enum cs_term_control_keys_t {
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
};

bool cs_term_enable_raw_mode();

bool cs_term_disable_raw_mode();

void cs_term_clear_screen();

int cs_term_read_key();

int cs_term_cursor_pos_get(int *row, int *col);
void cs_term_cursor_pos_set(int row, int col);

int cs_term_size(int *rows, int *cols);
