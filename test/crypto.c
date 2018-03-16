#include <csystem/crypto/crypto.h>
#include <csystem/string.h>
#include <stdlib.h>
#include <unity.h>

void test_crypto() {
  cs_crypto_ctx_t ctx;
  cs_hash_type_t hash_type = HASH_MD5;
  TEST_ASSERT_EQUAL(true, cs_crypto_init(&ctx, hash_type));

  size_t hash_size = cs_hash_size(hash_type);

  cs_crypto_update(&ctx, "Hello, World. You Are alone");
  char buf[hash_size + 1];
  TEST_ASSERT_EQUAL(true, cs_crypto_digest(&ctx, buf));
  buf[hash_size] = '\0';
  printf("%s\n", buf);
  char hex[hash_size * 2 + 1];
  // cs_str_hex_str(buf, hex, hash_size * 2 + 1);
  printf("HEX: '%s'\n", cs_str_hex_str(buf, NULL, 0));
  // for (size_t i = 0; i < hash_size; ++i)
  /// printf("%02x", buf[i]);
}