#pragma once

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int cs_term_form_list(const char *msg, const char **choices, size_t size);

#ifdef __cplusplus
}
#endif