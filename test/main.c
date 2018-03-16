#include <unity.h>

extern void test_path_join();
extern void test_crypto();

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_path_join);
  RUN_TEST(test_crypto);
  return UNITY_END();
}