#pragma once

class Color_Led {
  public:
    static Color_Led &GetInstance() {
        static Color_Led instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Color_Led(const Color_Led &) = delete;
    Color_Led &operator=(const Color_Led &) = delete;

    void Init(); // 初始化颜色LED

  private:
    Color_Led() = default;
    ~Color_Led() = default;
};