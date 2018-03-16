#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef enum cs_hash_type_t {
  HASH_SHA1 = 1,
  HASH_SHA224,
  HASH_SHA256,
  HASH_SHA384,
  HASH_SHA512,
  HASH_MD5
} cs_hash_type_t;

typedef struct cs_crypto_ctx_s {
  cs_hash_type_t hash_type;
  void *engine;
} cs_crypto_ctx_t;

size_t cs_hash_size(cs_hash_type_t type);

bool cs_crypto_init(cs_crypto_ctx_t *ctx, cs_hash_type_t type);
void cs_crypto_update(cs_crypto_ctx_t *ctx, const char *data);
bool cs_crypto_digest(cs_crypto_ctx_t *ctx, char *output);
void cs_crypto_free(cs_crypto_ctx_t *ctx);