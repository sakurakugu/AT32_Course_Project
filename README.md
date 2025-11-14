# 专业基础实践课期末大作业（AT32）

# 硬件
AT32F435VGT7 CPU（32位ARM Cortex-M4F 主频288MHz，1024k字节的Flash，默认384 K字节的内置SRAM，可设置最高达512 K字节）
MPU 6050 加速度计和陀螺仪
W5500 以太网控制器
OLED
LM75 I2C 温度传感器
I2C 储存器
无源蜂鸣器
按键x8 （4个正方形排列，4个菱形排列）
LCD-3.5 显示器
USB-A 接口
OTG 接口
BL3085 RS485-MODBUS 差分信号处理
ESP12 Wifi
ADC (连接PA0)
RGB 呼吸灯
SPI Flash （W25Q64JVSSIQ 支持双线、四线SPI接口的3V 64Mbit 串行闪存）
SD卡读卡器

# 实现功能

1. LCD
  1. 音乐播放
     - 支持MP3格式音乐播放
     - 支持本地SD卡音乐播放
     - 支持网络音乐播放（通过ESP12连接到WiFi）

  2. 智能家居
    - 支持控制LED灯
    - 支持控制RGB LED
    - 支持读取温度
    - 支持读取电压（ADC）

  3. 小游戏
    - 贪吃蛇
    - 连连看
    - 俄罗斯方块
    - 植物大战僵尸移植？

  4. 设置页面

  5. 时钟、日期、计时器、闹钟
    - 支持显示当前时间
    - 支持设置闹钟
    - 支持设置定时器
    - 支持设置闹钟和定时器的触发时间

  7. 天气
    - 支持显示当前天气
    - 支持显示未来天气

  8. Ai对话（打字）
    - 支持与Ai进行对话（如聊天、问题回答等）
    - 支持打字输入对话内容

2. 支持连接wifi，并进行网络操作
   - 支持连接到WiFi
   - 支持联网同步数据
   - 支持通过WiFi控制智能家居设备（如LED灯、RGB LED等）（Tlink?）

3. 支持在EEPROM中存储系统设置等
   - 支持将系统设置（如音乐播放列表、音量等）存储在EEPROM中
   - 支持从EEPROM中读取系统设置

4. 支持按键控制操作
   - 支持通过按键控制音乐播放（如播放/暂停、上一曲/下一曲等）
   - 支持通过按键调整音量

8. 支持陀螺仪数据读取
   - 支持读取MPU 6050 陀螺仪的原始数据（如角速度、加速度等）
   - 支持将陀螺仪数据用于智能家居控制（如根据角度调整LED灯的亮度）











# 其他
  this lvgl desktop demo is based on the at-surf board. 
  the  pin to pin with LCD and XMC(16 bits):          
  GPIO        LCD_RESET      NRST
  GPIO        LCD_BL         IO0_0
  XMC_A10     LCD_RS         PG0
  XMC_NE1     LCD_CS         PD7
  XMC_NWE     LCD_WR         PD5
  XMC_NWE     LCD_RD         PD4
  XMC_D0      DATA[0]        PD14
  XMC_D1      DATA[1]        PD15
  XMC_D2      DATA[2]        PD0
  XMC_D3      DATA[3]        PD1
  XMC_D4      DATA[4]        PE7
  XMC_D5      DATA[5]        PE8
  XMC_D6      DATA[6]        PE9
  XMC_D7      DATA[7]        PE10
  XMC_D8      DATA[8]        PE11
  XMC_D9      DATA[9]        PE12
  XMC_D10     DATA[10]       PE13
  XMC_D11     DATA[11]       PE14
  XMC_D12     DATA[12]       PE15
  XMC_D13     DATA[13]       PD8
  XMC_D14     DATA[14]       PD9
  XMC_D15     DATA[15]       PD10
  
  the  pin to pin with touch pad:
  I2C1 SCL      PB6  
  I2C1 SDA      PB7  
  TP INT        PE3  
  TP RS         PD11 





# 参考与引用
[音频播放](https://github.com/AmberHeart/STM32F407_Buzzer_Muisc_Player)
[天气API](https://www.seniverse.com/)
[时间同步](https://quan.suning.com/)
[我的世界游戏](https://github.com/zjsss900/ESPC32C3_ARDUINO_Raycasting_minecraft)
[Tlink物联网](https://tlink.io/)
[图标](https://www.iconfont.cn/)
[应用图标](https://www.bing.com/?mkt=zh-CN)
[物联网图标](https://www.doubao.com/chat/)
