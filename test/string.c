#include <csystem/string.h>
#include <stdlib.h>
#include <unity.h>

void test_string_utf8_size() {

  cs_string_t *str = cs_str_alloc();

  for (int i = 0; i < 1000; i++) {
    cs_str_utf8_append(str, "T");
  }
  printf("%d\n", cs_str_len(str));
}

void test_string_utf8() {
  cs_string_t *str = cs_str_alloc();

  cs_str_utf8_append(str, "Kød");
  TEST_ASSERT_EQUAL_STRING("Kød", cs_str_string(str));
  TEST_ASSERT_EQUAL(3, cs_str_utf8_len(str));
  TEST_ASSERT_EQUAL(4, cs_str_len(str));

  cs_str_utf8_insert(str, 1, "å");
  TEST_ASSERT_EQUAL_STRING("Kåød", cs_str_string(str));

  cs_str_utf8_insert(str, 4, "piæ");
  TEST_ASSERT_EQUAL_STRING("Kåødpiæ", cs_str_string(str));

  cs_str_utf8_remove(str, 1, 2);
  TEST_ASSERT_EQUAL_STRING("Kdpiæ", cs_str_string(str));
}

void test_string() {
  cs_string_t *str = cs_str_alloc();
  TEST_ASSERT_NOT_NULL(str);

  cs_str_append(str, "Hello, World");
  TEST_ASSERT_EQUAL(12, cs_str_len(str));
  char buf[13];
  cs_str_copy(str, buf);
  buf[12] = '\0';
  TEST_ASSERT_EQUAL_STRING("Hello, World", buf);

  cs_str_append(str, "Hello to you too.");
  TEST_ASSERT_EQUAL(12 + 17, cs_str_len(str));

  char buf2[12 + 17 + 1];
  cs_str_copy(str, buf2);
  buf2[12 + 17] = '\0';
  TEST_ASSERT_EQUAL_STRING("Hello, WorldHello to you too.", buf2);

  int len = cs_str_len(str);
  cs_str_remove(str, 7, 5);
  TEST_ASSERT_EQUAL(len - 5, cs_str_len(str));
  cs_str_copy(str, buf2);
  buf2[cs_str_len(str)] = '\0';
  TEST_ASSERT_EQUAL_STRING("Hello, Hello to you too.", buf2);

  cs_str_insert(str, 7, "World. ");

  char buf4[200];
  cs_str_copy(str, buf4);
  buf4[cs_str_len(str)] = '\0';
  TEST_ASSERT_EQUAL_STRING("Hello, World. Hello to you too.", buf4);

  cs_str_clear(str);
  cs_str_compact(str);

  cs_str_append(str, "Hello");
  TEST_ASSERT_EQUAL(5, cs_str_len(str));

  cs_str_remove(str, 4, 2);
  TEST_ASSERT_EQUAL_STRING("Hell", cs_str_string(str));

  cs_str_insert_char(str, 2, 'o');
  printf("%s\n", cs_str_string(str));
}