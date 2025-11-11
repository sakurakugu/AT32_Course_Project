// #pragma once
// #include <stdio.h>

// enum class LogLevel {
//     Null = 0, // 不打印任何日志
//     Debug,    // 调试日志
//     Info,     // 信息日志
//     Warn,     // 警告日志
//     Error     // 错误日志
// };

// constexpr LogLevel kLogLevel = LogLevel::Debug;

// template <LogLevel L> inline void Log(const char *file, int line, const char *fmt, ...) {
//     if constexpr (L >= kLogLevel) {
//         printf("[%s:%d] ", file, line);
//         va_list args;
//         va_start(args, fmt);
//         vprintf(fmt, args);
//         va_end(args);
//         printf("\n");
//     }
// }

#pragma once

#ifndef LOGGING_ENABLED
#define LOGGING_ENABLED 1
#endif

// 等级：调试（Debug）1、信息（Info）2、警告（Warning）3、错误（Error）4
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARN 3
#define LOG_LEVEL_ERROR 4

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#if LOGGING_ENABLED

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOGD(fmt, ...) printf("[调试][%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGD(fmt, ...) ((void)0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOGI(fmt, ...) printf("[信息][%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGI(fmt, ...) ((void)0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LOGW(fmt, ...) printf("[警告][%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGW(fmt, ...) ((void)0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOGE(fmt, ...) printf("[错误][%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGE(fmt, ...) ((void)0)
#endif

#else
#define LOGD(fmt, ...) ((void)0)
#define LOGI(fmt, ...) ((void)0)
#define LOGW(fmt, ...) ((void)0)
#define LOGE(fmt, ...) ((void)0)
#endif

// #define LOGD(fmt, ...) Log<LogLevel::Debug>(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
// #define LOGI(fmt, ...) Log<LogLevel::Info>(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
// #define LOGW(fmt, ...) Log<LogLevel::Warn>(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
// #define LOGE(fmt, ...) Log<LogLevel::Error>(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
