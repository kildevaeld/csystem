#include <CommonCrypto/CommonDigest.h>
#include <csystem/crypto/crypto.h>

void *cs_crypto_engine_create(cs_hash_type_t type) {
  void *hd = NULL;
  switch (type) {
  case HASH_MD5:
    hd = malloc(sizeof(CC_MD5_CTX));
    CC_MD5_Init(hd);
    break;
  case HASH_SHA1:
    hd = malloc(sizeof(CC_SHA1_CTX));
    CC_SHA1_Init(hd);
    break;
  case HASH_SHA224:
    hd = malloc(sizeof(CC_SHA256_CTX));
    CC_SHA224_Init(hd);
    break;
  case HASH_SHA256:
    hd = malloc(sizeof(CC_SHA256_CTX));
    CC_SHA256_Init(hd);
    break;
  case HASH_SHA384:
    hd = malloc(sizeof(CC_SHA512_CTX));
    CC_SHA384_Init(hd);
  case HASH_SHA512:
    hd = malloc(sizeof(CC_SHA512_CTX));
    CC_SHA512_Init(hd);
    break;
  }

  return hd;
}
void cs_crypto_engine_update(cs_crypto_ctx_t *ctx, const unsigned char *data,
                             size_t size) {
  switch (ctx->hash_type) {
  case HASH_MD5:
    CC_MD5_Update(ctx->engine, data, size);
    break;
  case HASH_SHA1:
    CC_SHA1_Update(ctx->engine, data, size);
    break;
  case HASH_SHA224:
    CC_SHA224_Update(ctx->engine, data, size);
    break;
  case HASH_SHA256:
    CC_SHA256_Update(ctx->engine, data, size);
    break;
  case HASH_SHA384:
    CC_SHA384_Update(ctx->engine, data, size);
    break;
  case HASH_SHA512:
    CC_SHA512_Update(ctx->engine, data, size);
    break;
  }
}
bool cs_crypto_engine_digest(cs_crypto_ctx_t *ctx, unsigned char *data) {
  int ret = -1;
  switch (ctx->hash_type) {
  case HASH_MD5: {
    ret = CC_MD5_Final(data, ctx->engine);
    return ret == 1;
  }
  case HASH_SHA1:
    ret = CC_MD5_Final(data, ctx->engine);
    return ret == 1;
  case HASH_SHA224:
    ret = CC_SHA224_Final(data, ctx->engine);
    return ret == 1;
  case HASH_SHA256:
    ret = CC_SHA256_Final(data, ctx->engine);
    return ret == 1;
  case HASH_SHA384:
    ret = CC_SHA384_Final(data, ctx->engine);
    return ret == 1;
  case HASH_SHA512:
    ret = CC_SHA512_Final(data, ctx->engine);
    return ret == 1;
  }
}
void cs_crypto_engine_free(cs_crypto_ctx_t *ctx) {}