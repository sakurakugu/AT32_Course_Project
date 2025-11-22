#ifndef MINECRAFT_H
#define MINECRAFT_H

#include "gui_guider.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// 游戏渲染尺寸 (120x76)，显示端使用4倍缩放
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 76
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

// 按键定义
#define MINECRAFT_KEY_UP     1  // 向前移动
#define MINECRAFT_KEY_DOWN   2  // 向后移动
#define MINECRAFT_KEY_LEFT   3  // 左转
#define MINECRAFT_KEY_RIGHT  4  // 右转
#define MINECRAFT_KEY_ACTION 5  // 攻击/交互
#define MINECRAFT_KEY_LOOK_UP    6  // 抬头
#define MINECRAFT_KEY_LOOK_DOWN  7  // 低头

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
} MinecraftState;

// 初始化游戏
void Minecraft_Init(void);

// 游戏主循环
void Minecraft_Loop(void);

// 处理按键输入
void Minecraft_HandleKey(uint8_t key);

// // 渲染到framebuffer
// void Minecraft_Render(void);

// 获取帧缓冲指针 (用于LVGL显示)
uint16_t* Minecraft_GetFramebuffer(void);

// 释放运行时缓冲
void Minecraft_Deinit(void);

// ===============================
// 我的世界游戏实现
// ===============================

extern lv_timer_t *minecraft_timer;
extern lv_obj_t *minecraft_img;

// 游戏循环定时器回调
extern void minecraft_timer_cb(lv_timer_t *timer);
extern void cleanup_scr_minecraft(lv_ui *ui);
extern void minecraft_app_screen_delete_event_handler(lv_event_t *e);

#ifdef __cplusplus
}
#endif

#endif // MINECRAFT_H

#ifndef MC_ENABLE_BADAPPLE
#define MC_ENABLE_BADAPPLE 1
#endif
#ifndef MC_ENABLE_JNTM
#define MC_ENABLE_JNTM 1
#endif
