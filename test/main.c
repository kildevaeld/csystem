#include <unity.h>

extern void test_path_join();
extern void test_crypto();
extern void test_string();
extern void test_string_utf8();
extern void test_string_utf8_size();

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_path_join);
  RUN_TEST(test_crypto);
  RUN_TEST(test_string);
  RUN_TEST(test_string_utf8);
  RUN_TEST(test_string_utf8_size);

  return UNITY_END();
}