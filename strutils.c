#include "strutils.h"
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

/* 1. Đảo ngược chuỗi tại chỗ (in-place) */
bool str_reverse(char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len <= 1) {
        return true; /* Chuỗi rỗng hoặc có 1 ký tự không cần đảo */
    }

    size_t left = 0;
    size_t right = len - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
    return true;
}

/* 2. Xóa khoảng trắng đầu và cuối chuỗi (in-place) */
bool str_trim(char *str) {
    if (str == NULL) {
        return false;
    }

    /* Tìm vị trí ký tự không phải khoảng trắng đầu tiên */
    char *start = str;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }

    /* Nếu chuỗi chỉ toàn khoảng trắng */
    if (*start == '\0') {
        str[0] = '\0';
        return true;
    }

    /* Tìm vị trí ký tự không phải khoảng trắng cuối cùng */
    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0'; /* Đặt ký tự kết thúc chuỗi */

    /* Dời chuỗi về đầu bộ nhớ nếu có khoảng trắng ở đầu */
    if (start != str) {
        memmove(str, start, (size_t)(end - start + 2));
    }

    return true;
}

/* 3. Chuyển chuỗi sang số nguyên an toàn */

int str_to_int(const char *str, int *out_val) {
    if (str == NULL || out_val == NULL) {
        return -1;
    }

    /* Bỏ qua khoảng trắng ở đầu */
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return -1; /* Chuỗi rỗng hoặc chỉ có khoảng trắng */
    }

    char *endptr = NULL;
    errno = 0;
    long val = strtol(str, &endptr, 10);

    /* Kiểm tra xem có ký tự lạ không chuyển đổi được không */
    if (endptr == str) {
        return -1; /* Không tìm thấy chữ số nào */
    }

    /* Kiểm tra phần đuôi: cho phép có khoảng trắng ở cuối */
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    if (*endptr != '\0') {
        return -1; /* Chứa ký tự không hợp lệ (ví dụ "123abc") */
    }

    /* Kiểm tra tràn số (Overflow/Underflow) */
    if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        return -2; /* Lỗi tràn số */
    }

    *out_val = (int)val;
    return 0; /* Thành công */
}