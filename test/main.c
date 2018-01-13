#include <unity.h>

extern void test_path_join();

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_path_join);
  return UNITY_END();
}