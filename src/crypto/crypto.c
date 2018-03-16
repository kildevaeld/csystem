#include "crypto-private.h"
#include <csystem/crypto/crypto.h>
#include <stdlib.h>
#include <string.h>

extern void *cs_crypto_engine_create(cs_hash_type_t type);
extern void cs_crypto_engine_update(cs_crypto_ctx_t *ctx,
                                    const unsigned char *data, size_t size);
extern bool cs_crypto_engine_digest(cs_crypto_ctx_t *ctx, unsigned char *data);
extern void cs_crypto_engine_free(cs_crypto_ctx_t *ctx);

size_t cs_hash_size(cs_hash_type_t type) {
  switch (type) {
  case HASH_MD5:
    return 16;
  case HASH_SHA1:
    return 20;
  case HASH_SHA224:
  case HASH_SHA256:
    return 32;
  case HASH_SHA384:
  case HASH_SHA512:
    return 64;
  }
}

bool cs_crypto_init(cs_crypto_ctx_t *ctx, cs_hash_type_t type) {
  ctx->hash_type = type;
  ctx->engine = cs_crypto_engine_create(type);
  if (ctx->engine == NULL) {
    return false;
  }
  return true;
}

void cs_crypto_update(cs_crypto_ctx_t *ctx, const char *data) {
  cs_crypto_engine_update(ctx, (const unsigned char *)data, strlen(data));
}
bool cs_crypto_digest(cs_crypto_ctx_t *ctx, char *output) {
  return cs_crypto_engine_digest(ctx, (unsigned char *)output);
}
void cs_crypto_free(cs_crypto_ctx_t *ctx) { cs_crypto_engine_free(ctx); }