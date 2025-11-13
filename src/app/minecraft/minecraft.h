#ifndef MINECRAFT_H
#define MINECRAFT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// 游戏显示尺寸 (160x80 原始大小)
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 80
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

// 按键定义
#define MINECRAFT_KEY_UP     1  // 向前移动
#define MINECRAFT_KEY_DOWN   2  // 向后移动
#define MINECRAFT_KEY_LEFT   3  // 左转
#define MINECRAFT_KEY_RIGHT  4  // 右转
#define MINECRAFT_KEY_ACTION 5  // 攻击/交互

// 游戏状态
typedef struct {
    float posX, posY;         // 玩家位置
    float dirX, dirY;         // 玩家方向
    float planeX, planeY;     // 相机平面
    int8_t pitch;             // 视角俯仰
    uint8_t stepTemp;         // 步伐动画
    uint8_t attackTemp;       // 攻击动画
    float targetDistance;     // 目标距离
    int8_t targetMapX, targetMapY; // 目标方块坐标
    uint32_t oldFrame, nowFrame;   // 帧时间
    uint32_t t2, t3, t4, t5, t6;   // 计时器
    uint8_t jntmFrame;        // 动画帧
    uint8_t badappleFrame;    // 动画帧
    bool texcsh;              // 纹理缓存标志
    bool pitchBuffer;         // 俯仰缓冲
} MinecraftState;

// 初始化游戏
void minecraft_init(void);

// 游戏主循环
void minecraft_loop(void);

// 处理按键输入
void minecraft_handle_key(uint8_t key);

// 渲染到framebuffer
void minecraft_render(void);

// 获取帧缓冲指针 (用于LVGL显示)
uint16_t* minecraft_get_framebuffer(void);

// 释放运行时缓冲
void minecraft_deinit(void);

#ifdef __cplusplus
}
#endif

#endif // MINECRAFT_H
