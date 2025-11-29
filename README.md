# 专业基础实践课期末大作业（AT32）

一个基于 AT32F435 的综合实践项目，集成 FreeRTOS、LVGL 图形界面、以太网 lwIP、ESP12 Wi‑Fi（AT 指令）、I2C/SPI/QSPI 等外设，涵盖时间同步、天气查询、小游戏与多种板载传感器/外设演示。
- 主仓库：[github.com](https://github.com/sakurakugu/AT32_Course_Project.git)
- 镜像仓库：[gitee.com](https://gitee.com/sakurakugu/AT32_Course_Project.git)
- 镜像仓库：[gitcode.com](https://gitcode.com/sakurakugu/AT32_Course_Project.git)

**主工程**：`homework.uvprojx`

## 硬件
- AT32F435VGT7（Cortex‑M4F 288MHz，Flash 1024KB，SRAM 默认 384KB 可设最高 512KB）
- MPU‑6050 加速度计/陀螺仪
- 片上 EMAC 以太网 + RJ45（lwIP 栈）
- OLED、LCD‑3.5 显示屏
- LM75 I2C 温度传感器、I2C EEPROM
- 无源蜂鸣器
- 按键 x8（4 个正方形排列 + 4 个菱形排列）
- USB‑A、OTG 接口
- BL3085 RS485‑MODBUS 差分接口
- ESP12 Wi‑Fi 模块（UART AT）
- ADC（PA0）、RGB 呼吸灯
- SPI Flash（W25Q64JVSSIQ，支持双/四线 SPI）、SD 卡读卡器

## 软件栈与架构
- RTOS：FreeRTOS v11.1.0（`src\config\FreeRTOSConfig.h`）
- GUI：LVGL v8.3.11 + GUI Guider 生成物（`gui\generated\`，移植层在 `src\config\lvgl\porting\`）
- 网络：lwIP 2.1.2（以太网 EMAC 驱动在 `lib\middlewares\3rd_party\lwip_2.1.2\port\ethernetif.c`），Wi‑Fi 通过 ESP12 AT（`src\board\network\wifi.cpp`）
- 存储：I2C EEPROM（`src\board\eeprom\`），SPI/QSPI Flash（驱动与算法）
- 外设：UART、ADC、LCD、按键、蜂鸣器等板载驱动封装于 `src\board\` 下

## 目录结构（节选）
- `homework.uvprojx`：Keil MDK5 主工程文件
- `src\application.cpp`：应用启动与任务创建，LVGL 初始化、Wi‑Fi 初始化等
- `src\app\`：应用逻辑（如天气、时间同步、小游戏等）
- `src\board\`：板级驱动（UART/LCD/EEPROM/Wi‑Fi/ADC/LED 等）
- `src\config\`：工程配置（`FreeRTOSConfig.h`、`lv_conf.h`、编译宏等）
- `lib\`：第三方库（FreeRTOS、lwIP、驱动与 CMSIS 等）
- `gui\generated\`：GUI Guider 生成的 LVGL UI 代码与资源
- `tools\`：工具与算法文件（含 QSPI 下载算法压缩包）

## 快速上手
- 安装 Keil MDK v5（推荐 ARM Compiler 6），去官网下载，然后安装 AT32F435/437 设备包
- 准备调试器（ST‑Link/J‑Link/AT‑Link，按你的板卡与布线）
- 将 QSPI 下载算法拷贝到 `Keil_v5/ARM/Flash`（压缩包在本仓库 `tools` 目录）
- GUI Guider 版本请使用 ≥ 1.10；仅用于“生成代码”，不要直接运行生成后的工程（有些代码过于耦合，但已经到提交时间了就没有改）
- 打开 `homework.uvprojx`，选择正确目标，编译并下载到板卡

## 运行配置
- 天气接口密钥：在 `src\config\api_key.h` 设置 `API_KEY_WEATHER`（请使用你自己的密钥并避免泄露，我这个密钥已经删除了）
- Wi‑Fi/网络：ESP12 串口为 `USART3`（PC10/PC11，详见 `src\board\uart\uart.h` 与 `src\board\network\wifi.cpp`）；
  - 支持设置工作模式/多连接（`SetWiFiMode`/`EnableCIPMUX`）（不推荐使用多连接）
  - 可通过 AT 指令创建/连接 TCP/UDP、查询本地 IP、配置 AP SSID/密码
  - 部分凭据可存取于 I2C EEPROM（`src\board\eeprom\eeprom.cpp`）
- 以太网（lwIP）：驱动在 `ethernetif.c`，典型序列为 `lwip_init()` → `netif_add()` → `netif_set_default()` → `netif_set_up()`（实际调用位于应用层）
- LVGL：显示/输入移植在 `src\config\lvgl\porting\lv_port_disp.c` 与 `lv_port_indev.c`；`src\board\lcd\lcd.h` 提供底层接口

## 主要任务（FreeRTOS）
- `TaskLVGL`：周期调用 `lv_task_handler()`，刷新与事件处理（`src\application.cpp`）
- `TaskHeartbeat`：心跳与状态指示
- `TaskADC`/`TaskLED`：采样与外设控制
- `TaskWiFi`：ESP12 通信与网络服务（创建/连接/发送/接收）

## 常见问题
- GUI Guider 只能“生成代码”，不要直接运行生成工程（涉及硬件宏与板级适配）
- 若 Keil 无法下载：请确认已将 QSPI 算法添加到 `Keil_v5/ARM/Flash`（压缩包在 `tools`）
- 天气/时间接口访问失败：检查 `API_KEY_WEATHER`、网络连通（以太网/ESP12）、以及目标接口可达性
- Wi‑Fi 不工作：核对 ESP12 供电与串口引脚（PC10/PC11，`USART3`），确认波特率与 AT 指令响应
- 该README.md有部分由AI生成，我只粗略看了看，有错误请到github告知我
- 如果镜像仓库不存在就是我删了或者压根没传

## 构建与调试建议
- 在Keil中开启 `KEIL_COMPILE` 宏以屏蔽仅桌面/模拟环境的代码片段
- 合理设置 FreeRTOS 堆与任务栈（`FreeRTOSConfig.h` 与各任务 `stack size`）
- lwIP 使用 DHCP 时，请确保物理链路与 MAC/MTU 配置正确；必要时打印 netif 状态
- 串口助手推荐使用支持utf-8编码的，如纸飞机串口助手、网页版的串口助手

## 参考与引用
- [音频播放](https://github.com/AmberHeart/STM32F407_Buzzer_Muisc_Player)
- [心知天气 API](https://www.seniverse.com/)
- [时间同步](https://quan.suning.com/)
- [我的世界游戏](https://github.com/zjsss900/ESPC32C3_ARDUINO_Raycasting_minecraft)
- [Tlink 物联网](https://tlink.io/)
- [图标](https://www.iconfont.cn/)
- [应用图标](https://www.bing.com/?mkt=zh-CN)
- [物联网图标](https://www.doubao.com/chat/)
- [cJSON v1.7.19](https://github.com/DaveGamble/cJSON)
- [LVGL v8.3.11](https://lvgl.io/)
- [FreeRTOS v11.1.0](https://www.freertos.org/)

> 其他库来自前辈传承或 AT32 官方案例移植，部分来源不详，特此致谢。
