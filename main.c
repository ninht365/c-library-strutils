#include <stdio.h>
#include <string.h>
#include "strutils.h"

static int g_pass = 0;
static int g_fail = 0;

#define RUN_TEST(expr, msg) \
    do { \
        if (expr) { \
            printf("  [\033[32mPASS\033[0m] %s\n", msg); \
            g_pass++; \
        } else { \
            printf("  [\033[31mFAIL\033[0m] %s\n", msg); \
            g_fail++; \
        } \
    } while (0)

void test_str_reverse(void) {
    printf("\n=== TEST 1: str_reverse ===\n");

    /* Case bình thường */
    char s1[] = "Hello World";
    str_reverse(s1);
    RUN_TEST(strcmp(s1, "dlroW olleH") == 0, "Dao chuoi thong thuong: 'Hello World' -> 'dlroW olleH'");

    /* Case đối xứng */
    char s2[] = "racecar";
    str_reverse(s2);
    RUN_TEST(strcmp(s2, "racecar") == 0, "Chuoi doi xung: 'racecar' -> 'racecar'");

    /* Case biên: 1 ký tự */
    char s3[] = "A";
    str_reverse(s3);
    RUN_TEST(strcmp(s3, "A") == 0, "Chuoi 1 ky tu: 'A' -> 'A'");

    /* Case biên: chuỗi rỗng */
    char s4[] = "";
    str_reverse(s4);
    RUN_TEST(strcmp(s4, "") == 0, "Chuoi rong: '' -> ''");

    /* Case lỗi: con trỏ NULL */
    bool res = str_reverse(NULL);
    RUN_TEST(res == false, "Xu ly dau vao NULL an toan (tra ve false)");
}

void test_str_trim(void) {
    printf("\n=== TEST 2: str_trim ===\n");

    /* Case bình thường: cả 2 đầu */
    char s1[] = "   hello world   ";
    str_trim(s1);
    RUN_TEST(strcmp(s1, "hello world") == 0, "Xoa khoang trang ca 2 dau: '   hello world   '");

    /* Case chỉ khoảng trắng ở đầu */
    char s2[] = "\t\n  embedded";
    str_trim(s2);
    RUN_TEST(strcmp(s2, "embedded") == 0, "Xoa tab/newline o dau chuoi");

    /* Case chỉ khoảng trắng ở cuối */
    char s3[] = "linux   \r\n";
    str_trim(s3);
    RUN_TEST(strcmp(s3, "linux") == 0, "Xoa khoang trang o cuoi chuoi");

    /* Case chuỗi chỉ toàn khoảng trắng */
    char s4[] = "    \t   ";
    str_trim(s4);
    RUN_TEST(strcmp(s4, "") == 0, "Chuoi toan khoang trang -> thanh chuoi rong");

    /* Case chuỗi không có khoảng trắng */
    char s5[] = "clean_string";
    str_trim(s5);
    RUN_TEST(strcmp(s5, "clean_string") == 0, "Chuoi khong co khoang trang giu nguyen");

    /* Case lỗi: NULL */
    bool res = str_trim(NULL);
    RUN_TEST(res == false, "Xu ly dau vao NULL an toan (tra ve false)");
}

void test_str_to_int(void) {
    printf("\n=== TEST 3: str_to_int ===\n");

    int val = 0;
    int ret;

    /* Case số dương hợp lệ */
    ret = str_to_int("12345", &val);
    RUN_TEST(ret == 0 && val == 12345, "Chuyen so duong: '12345' -> 12345");

    /* Case số âm hợp lệ */
    ret = str_to_int("-9876", &val);
    RUN_TEST(ret == 0 && val == -9876, "Chuyen so am: '-9876' -> -9876");

    /* Case có dấu cộng và khoảng trắng */
    ret = str_to_int("  +42  ", &val);
    RUN_TEST(ret == 0 && val == 42, "Chuyen so co dau + va khoang trang: '  +42  ' -> 42");

    /* Case biên: INT_MAX */
    ret = str_to_int("2147483647", &val);
    RUN_TEST(ret == 0 && val == 2147483647, "Gia tri bien INT_MAX: '2147483647'");

    /* Case biên: INT_MIN */
    ret = str_to_int("-2147483648", &val);
    RUN_TEST(ret == 0 && val == -2147483648, "Gia tri bien INT_MIN: '-2147483648'");

    /* Case lỗi: ký tự không hợp lệ */
    ret = str_to_int("123abc", &val);
    RUN_TEST(ret == -1, "Phat hien ky tu khong hop le: '123abc' (tra ve -1)");

    /* Case lỗi: chuỗi rỗng */
    ret = str_to_int("", &val);
    RUN_TEST(ret == -1, "Phat hien chuoi rong: '' (tra ve -1)");

    /* Case lỗi: tràn số dương */
    ret = str_to_int("99999999999999", &val);
    RUN_TEST(ret == -2, "Phat hien tran so duong: '99999999999999' (tra ve -2)");

    /* Case lỗi: tràn số âm */
    ret = str_to_int("-99999999999999", &val);
    RUN_TEST(ret == -2, "Phat hien tran so am: '-99999999999999' (tra ve -2)");

    /* Case lỗi: NULL */
    ret = str_to_int(NULL, &val);
    RUN_TEST(ret == -1, "Xu ly dau vao NULL an toan (tra ve -1)");
}

int main(void) {
    printf("==================================================\n");
    printf("     KIEM THU THU VIEN XU LY CHUOI STRUTILS      \n");
    printf("==================================================\n");

    test_str_reverse();
    test_str_trim();
    test_str_to_int();

    printf("\n--------------------------------------------------\n");
    printf("KET QUA: Tong so test: %d | [\033[32mPASS: %d\033[0m] | [\033[31mFAIL: %d\033[0m]\n",
           g_pass + g_fail, g_pass, g_fail);
    printf("--------------------------------------------------\n");

    return (g_fail == 0) ? 0 : 1;
}