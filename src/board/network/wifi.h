#pragma once

// 运行时可修改的 Wi‑Fi 凭据缓冲区声明
// 注意：定义在 C 源文件中，以便在 C/C++ 模块间共享且无符号修饰问题
#ifdef __cplusplus
extern "C" {
#endif

extern char wifi_ssid[33];
extern char wifi_password[65];

#ifdef __cplusplus
}
#endif