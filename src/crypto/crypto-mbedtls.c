#include <csystem/crypto/crypto.h>
#include <mbedtls/md5.h>
#include <mbedtls/sha1.h>
#include <mbedtls/sha256.h>
#include <mbedtls/sha512.h>
#include <stdlib.h>

void *cs_crypto_engine_create(cs_hash_type_t type) {
  void *hd = NULL;
  switch (type) {
  case HASH_MD5:
    hd = malloc(sizeof(mbedtls_md5_context));
    mbedtls_md5_init(hd);
    mbedtls_md5_starts_ret(hd);
    break;
  case HASH_SHA1:
    hd = malloc(sizeof(mbedtls_sha1_context));
    mbedtls_sha1_init(hd);
    mbedtls_sha1_starts_ret(hd);
    break;
  case HASH_SHA224:
  case HASH_SHA256:
    hd = malloc(sizeof(mbedtls_sha256_context));
    mbedtls_sha256_init(hd);
    mbedtls_sha256_starts_ret(hd, type == HASH_SHA224);
    break;
  case HASH_SHA384:
  case HASH_SHA512:
    hd = malloc(sizeof(mbedtls_sha512_context));
    mbedtls_sha512_init(hd);
    mbedtls_sha512_starts_ret(hd, type == HASH_SHA512);
    break;
  }

  return hd;
}

void cs_crypto_engine_update(cs_crypto_ctx_t *ctx, const unsigned char *data,
                             size_t size) {

  switch (ctx->hash_type) {
  case HASH_MD5:
    mbedtls_md5_update(ctx->engine, data, size);
    break;
  case HASH_SHA1:
    mbedtls_sha1_update(ctx->engine, data, size);
    break;
  case HASH_SHA224:
  case HASH_SHA256:
    mbedtls_sha256_update(ctx->engine, data, size);
    break;
  case HASH_SHA384:
  case HASH_SHA512:
    mbedtls_sha256_update(ctx->engine, data, size);
    break;
  }
}

bool cs_crypto_engine_digest(cs_crypto_ctx_t *ctx, unsigned char *data) {
  switch (ctx->hash_type) {
  case HASH_MD5: {
    int ret = mbedtls_md5_finish_ret(ctx->engine, data);
    mbedtls_sha1_starts(ctx->engine);
    return ret == 0;
  }
  case HASH_SHA1:
    return mbedtls_sha1_finish_ret(ctx->engine, data) == 0;
  case HASH_SHA224:
  case HASH_SHA256:
    return mbedtls_sha256_finish_ret(ctx->engine, data) == 0;
  case HASH_SHA384:
  case HASH_SHA512:
    return mbedtls_sha512_finish_ret(ctx->engine, data) == 0;
  }
}

extern void cs_crypto_engine_free(cs_crypto_ctx_t *ctx) {
  switch (ctx->hash_type) {
  case HASH_MD5:
    mbedtls_md5_free(ctx->engine);
    break;
  case HASH_SHA1:
    mbedtls_sha1_free(ctx->engine);
    break;
  case HASH_SHA224:
  case HASH_SHA256:
    mbedtls_sha256_free(ctx->engine);
    break;
  case HASH_SHA384:
  case HASH_SHA512:
    mbedtls_sha512_free(ctx->engine);
    break;
  }
}