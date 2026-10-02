#ifndef STRUTILS_H
#define STRUTILS_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Đảo ngược chuỗi tại chỗ (in-place).
 * @param str Chuỗi cần đảo ngược (sẽ bị thay đổi trực tiếp).
 * @return true nếu thành công, false nếu str là NULL.
 */
bool str_reverse(char *str);

/**
 * @brief Xóa các ký tự khoảng trắng (' ', '\t', '\n', '\r') ở đầu và cuối chuỗi tại chỗ.
 * @param str Chuỗi cần cắt khoảng trắng.
 * @return true nếu thành công, false nếu str là NULL.
 */
bool str_trim(char *str);

/**
 * @brief Chuyển đổi an toàn chuỗi sang số nguyên (int).
 * @param str Chuỗi biểu diễn số (vd: "123", "-456", "+789").
 * @param out_val Con trỏ lưu giá trị số nguyên sau khi chuyển đổi.
 * @return 0 nếu thành công;
 *        -1 nếu đầu vào không hợp lệ (NULL, chuỗi rỗng, chứa ký tự lạ);
 *        -2 nếu tràn số (Overflow/Underflow ngoài khoảng INT_MIN .. INT_MAX).
 */
int str_to_int(const char *str, int *out_val);

#ifdef __cplusplus
}
#endif

#endif /* STRUTILS_H */