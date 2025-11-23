#include "calculator.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CALC_EXPR_MAX_LEN 127

static lv_obj_t *s_display = NULL;
static char s_expr[CALC_EXPR_MAX_LEN + 1] = {0};

/**
 * @brief 设置计算器显示的文本
 * @param text 要显示的文本，若为 NULL 则显示空字符串
 */
static void set_display_text(const char *text) {
    if (!s_display)
        return;
    if (!text)
        text = "";
    lv_label_set_text(s_display, text);
}

/**
 * @brief 刷新显示，将当前表达式显示在计算器上
 */
static void refresh_display_with_expr(void) {
    set_display_text(s_expr);
}

/**
 * @brief 清除当前表达式
 */
static void clear_expr(void) {
    s_expr[0] = '\0';
    refresh_display_with_expr();
}

/**
 * @brief 删除表达式中的最后一个字符
 */
static void backspace_expr(void) {
    size_t n = strlen(s_expr);
    if (n > 0) {
        s_expr[n - 1] = '\0';
    }
    refresh_display_with_expr();
}

/**
 * @brief 判断字符是否为数字
 * @param c 要判断的字符
 * @return true 若为数字字符（'0'..'9'）
 */
static bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

/**
 * @brief 判断字符是否为运算符
 * @param c 要判断的字符
 * @return true 若为运算符字符（'+', '-', '*', '/', '%', '(', ')'）
 */
static bool is_operator_char(char c) {
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '(':
    case ')':
        return true;
    default:
        return false;
    }
}

/**
 * @brief 将字符追加到表达式末尾
 * @param c 要追加的字符，若不是数字或运算符则忽略
 */
static void append_char_to_expr(char c) {
    if (!(is_digit(c) || is_operator_char(c)))
        return;
    size_t n = strlen(s_expr);
    if (n >= CALC_EXPR_MAX_LEN)
        return;
    s_expr[n] = c;
    s_expr[n + 1] = '\0';
    refresh_display_with_expr();
}

// ======== 递归下降解析器 ========
typedef struct {
    const char *s;
    size_t i;
    bool err;
    bool divzero;
} Parser;

/**
 * @brief 从解析器当前位置获取下一个字符
 * @param p 解析器实例指针
 * @return char 下一个字符
 */
static char peek(Parser *p) {
    return p->s[p->i];
}

/**
 * @brief 尝试匹配当前字符并前进解析器位置
 * @param p 解析器实例指针
 * @param c 要匹配的字符
 * @return true 若匹配成功
 */
static bool match(Parser *p, char c) {
    if (peek(p) == c) {
        p->i++;
        return true;
    }
    return false;
}

static int64_t parse_expression(Parser *p);
static int64_t parse_term(Parser *p);
static int64_t parse_factor(Parser *p);

static int64_t parse_number(Parser *p) {
    if (!is_digit(peek(p))) {
        p->err = true;
        return 0;
    }
    int64_t val = 0;
    while (is_digit(peek(p))) {
        val = val * 10 + (peek(p) - '0');
        p->i++;
    }
    return val;
}

static int64_t parse_factor(Parser *p) {
    // 一元正负号
    if (match(p, '+')) {
        // 一元正号，对值无影响
        return parse_factor(p);
    }
    // 一元负号
    if (match(p, '-')) {
        int64_t v = parse_factor(p);
        return -v;
    }

    if (match(p, '(')) {
        int64_t v = parse_expression(p);
        if (!match(p, ')')) {
            p->err = true;
        }
        return v;
    }

    // 数字
    return parse_number(p);
}

static int64_t parse_term(Parser *p) {
    int64_t v = parse_factor(p);
    while (true) {
        char c = peek(p);
        if (c == '*' || c == '/' || c == '%') {
            p->i++;
            int64_t rhs = parse_factor(p);
            if (c == '*') {
                v = v * rhs;
            } else if (c == '/') {
                if (rhs == 0) {
                    p->divzero = true;
                    rhs = 1; // 防止除零崩溃，错误标志由上层处理
                }
                v = v / rhs;
            } else { // '%'
                if (rhs == 0) {
                    p->divzero = true;
                    rhs = 1;
                }
                v = v % rhs;
            }
        } else {
            break;
        }
    }
    return v;
}

/**
 * @brief 解析表达式，支持 +, -, *, /, % 运算符
 * @param p 解析器实例指针
 * @return int64_t 解析出的表达式值
 */
static int64_t parse_expression(Parser *p) {
    int64_t v = parse_term(p);
    while (true) {
        char c = peek(p);
        if (c == '+' || c == '-') { // 加法减法
            p->i++;
            int64_t rhs = parse_term(p);
            if (c == '+')
                v = v + rhs;
            else
                v = v - rhs;
        } else {
            break;
        }
    }
    return v;
}

/**
 * @brief 评估表达式字符串，支持 +, -, *, /, % 运算符
 * @param s 表达式字符串
 * @param out 若成功计算，存储结果的指针（可设为 NULL 忽略）
 * @param errmsg 若发生错误，存储错误信息的指针（可设为 NULL 忽略）
 * @return true 若表达式语法正确且无除零错误
 */
static bool eval_expr(const char *s, int64_t *out, const char **errmsg) {
    Parser p = {s, 0, false, false};
    int64_t v = parse_expression(&p);
    // 若未到字符串末尾但当前字符存在且不是右括号，视为语法错误
    if (p.s[p.i] != '\0') {
        // 容许尾部的空白字符（虽然我们没有空白）
        // 但如果不是结束且不是')'刚好由上层消费，统一视为语法错
        p.err = true;
    }
    if (p.err) {
        // if (errmsg) *errmsg = "Syntax Error";
        if (errmsg)
            *errmsg = "语法错误";
        return false;
    }
    if (p.divzero) {
        // if (errmsg) *errmsg = "Divide By Zero";
        if (errmsg)
            *errmsg = "除零错误";
        return false;
    }
    if (out)
        *out = v;
    return true;
}

void Calculator_Init(lv_obj_t *display_label) {
    s_display = display_label; // 保存显示标签指针
    clear_expr();              // 初始化表达式为空
}

void Calculator_InputKey(const char *key) {
    if (!key || !*key)
        return;
    // 特殊键
    if (strcmp(key, "C") == 0) {
        clear_expr();
        return;
    }
    if (strcmp(key, "⬅") == 0) {
        backspace_expr();
        return;
    }
    if (strcmp(key, "=") == 0) {
        if (s_expr[0] == '\0') {
            // 空表达式，忽略
            return;
        }
        int64_t result = 0;
        const char *errmsg = NULL;
        if (eval_expr(s_expr, &result, &errmsg)) {
            char buf[48];
            snprintf(buf, sizeof(buf), "%lld", (long long)result);
            set_display_text(buf);
            // 将结果作为新的表达式，便于继续计算
            strncpy(s_expr, buf, sizeof(s_expr) - 1);
            s_expr[sizeof(s_expr) - 1] = '\0';
        } else {
            set_display_text(errmsg ? errmsg : "Error");
        }
        return;
    }

    // 普通字符：数字和操作符
    char c = key[0];
    // 映射 UI 中的特殊符号（已经在ui中处理了）
    // if (c == 'x') c = '*';
    // if (c == '÷') c = '/';

    // 若 key 是多字符（理论上不会），只取第一个
    append_char_to_expr(c);
}

// 统一的按键事件处理器：从 user_data 读取按键字符串并转交给计算器
void calc_key_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        const char *key = (const char *)lv_event_get_user_data(e);
        Calculator_InputKey(key);
    }
}