#pragma once

class Setting {
  public:
    static Setting &GetInstance() {
        static Setting instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Setting(const Setting &) = delete;
    Setting &operator=(const Setting &) = delete;

  private:
    Setting() = default;
    ~Setting() = default;
};