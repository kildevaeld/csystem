#pragma once

#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int cs_term_form_list(const char *msg, const char **choices, size_t size);
bool cs_term_form_confirm(const char *msg, bool clear);

#ifdef __cplusplus
}
#endif