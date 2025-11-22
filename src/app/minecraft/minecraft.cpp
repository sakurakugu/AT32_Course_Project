#include "minecraft.h"
#include "minecraft_textures.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>

#define CHUNK_W 32
#define CHUNK_H 32

// 获取当前时间(毫秒)
static inline uint32_t millis(void) {
    return xTaskGetTickCount();
}

// 世界地图
static uint8_t worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 4, 0, 0, 0, 0, 9, 10, 10, 10, 10, 10, 10, 10, 10, 7, 7, 0, 7, 7, 7, 7, 7},
    {4, 0, 5, 0, 0, 0, 0, 9, 0, 10, 0, 10, 0, 10, 0, 10, 7, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 6, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 7, 0, 0, 0, 0, 0, 0, 8},
    {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 8, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 7, 0, 0, 0, 0, 0, 0, 8},
    {4, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 7, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 9, 9, 7, 7, 7, 7, 7, 7, 7, 1},
    {6, 6, 6, 6, 6, 14, 13, 12, 11, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12},
    {6, 6, 6, 6, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 9, 9, 9, 9, 10, 10, 11, 11, 11, 11},
    {4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 1, 0, 0, 11, 9, 2, 2, 2, 2, 2, 3, 3, 3, 3},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 0, 11, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 9, 0, 0, 10, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
    {4, 0, 14, 0, 15, 0, 0, 0, 0, 4, 9, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
    {4, 0, 0, 15, 0, 0, 0, 0, 0, 4, 9, 0, 0, 10, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
    {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 9, 0, 0, 10, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 9, 0, 0, 10, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 10, 17, 16, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}
};

// 游戏状态
static MinecraftState g_state;

// 帧缓冲 (直接渲染到线性画布)
static uint16_t *lv_framebuffer = NULL;
// 移除mixTex，改为按需采样

// 攻击动画序列
static const uint8_t attackActionGroup[4] = {0, 1, 0, 2};

// 当前按键状态
static uint8_t currentKey = 0;

// 颜色转换 - 墙壁侧面变暗
static uint16_t CHANGE_SIDE_TEX_COLOR(uint16_t color) {
    uint16_t color_Red = (color & 0xF800) >> 11;
    uint16_t color_Green = (color & 0x07E0) >> 5;
    uint16_t color_Blue = color & 0x001F;
    uint16_t newColor = ((color_Red >> 1) << 11) | ((color_Green >> 1) << 5) | (color_Blue >> 1);
    return newColor;
}

// 将8位纹理转换为16位
static inline uint16_t READ16(const uint8_t* base, int idx) {
    return (uint16_t)(base[idx] << 8) | (uint16_t)(base[idx + 1]);
}

// 混合纹理
static inline uint16_t SAMPLE_WALL_COLOR(uint8_t texNum, int texX, int texY) {
    int idx = ((texHeight * texX + texY) << 1);
    if (texNum < 30) {
        if (texNum == 15 || texNum == 16) {
#if MC_ENABLE_BADAPPLE
            return READ16(badapple[g_state.badappleFrame], idx);
#else
            return READ16(texture[texNum], idx);
#endif
        }
        return READ16(texture[texNum], idx);
    }
    if (texNum == 90) {
#if MC_ENABLE_JNTM
        return READ16(jntm[g_state.jntmFrame], idx);
#else
        return READ16(texture[0], idx);
#endif
    }
    if (texNum >= 30 && texNum < 60) {
        uint16_t lw = READ16(liewen[0], idx);
        if (lw == 0) return 0;
        return READ16(texture[texNum - 30], idx);
    }
    if (texNum >= 60 && texNum < 90) {
        uint16_t lw = READ16(liewen[1], idx);
        if (lw == 0) return 0;
        return READ16(texture[texNum - 60], idx);
    }
    if (texNum > 90 && texNum < 120) {
        uint16_t lw = READ16(liewen[2], idx);
        if (lw == 0) return 0;
        return READ16(texture[texNum - 90], idx);
    }
    return READ16(texture[0], idx);
}

// 混合两个纹理
static inline void UPDATE_JNTM(void) {
#if MC_ENABLE_JNTM
    if (millis() >= g_state.t4 + 200) {
        g_state.t4 = millis();
        if (g_state.jntmFrame < 44) {
            g_state.jntmFrame++;
        } else {
            g_state.jntmFrame = 0;
        }
    }
#endif
}

// 播放JNTM动画
static inline void UPDATE_BADAPPLE(void) {
#if MC_ENABLE_BADAPPLE
    if (millis() >= g_state.t5 + 300) {
        g_state.t5 = millis();
        if (g_state.badappleFrame < 74) {
            g_state.badappleFrame++;
        } else {
            g_state.badappleFrame = 0;
        }
    }
#endif
}

// 检查是否在地图边界
static bool CHECK_MAP_SIDE(void) {
    if (g_state.targetMapX == 0 || g_state.targetMapY == 0 || 
        g_state.targetMapX == MAP_WIDTH - 1 || g_state.targetMapY == MAP_HEIGHT - 1) {
        return false;
    }
    return true;
}

// 攻击方块
static void WEAPONHIT(void) {
    if (g_state.targetDistance <= 1.5) {
        if (worldMap[g_state.targetMapX][g_state.targetMapY] < 90) {
            worldMap[g_state.targetMapX][g_state.targetMapY] += 30;
        } else {
            if (worldMap[g_state.targetMapX][g_state.targetMapY] != 91) {
                worldMap[g_state.targetMapX][g_state.targetMapY] = 0;
            }
        }
    }
}

// 绘制武器到屏幕
static void DRAW_WEAPONS_TO_SCREEN(int typeOfWeapon) {
    uint16_t wStart = 0, hStart = 0;
    int c = 0;
    uint16_t weaponsBuffer = 0;
    if (g_state.stepTemp == 0) {
        wStart = SCREEN_WIDTH - chutou1_texWidth;
        hStart = SCREEN_HEIGHT - chutou1_texHeight;
        for (uint16_t a = wStart; a < wStart + chutou1_texWidth; a++) {
            for (uint16_t b = hStart; b < hStart + chutou1_texHeight; b++) {
                weaponsBuffer = READ16(chutou1, c);
                c += 2;
                if (weaponsBuffer != 0) {
                    lv_framebuffer[b * SCREEN_WIDTH + a] = weaponsBuffer;
                }
            }
        }
    } else if (g_state.stepTemp == 1) {
        wStart = SCREEN_WIDTH - chutou2_texWidth;
        hStart = SCREEN_HEIGHT - chutou2_texHeight;
        for (uint16_t a = wStart; a < wStart + chutou2_texWidth; a++) {
            for (uint16_t b = hStart; b < hStart + chutou2_texHeight; b++) {
                weaponsBuffer = READ16(chutou2, c);
                c += 2;
                if (weaponsBuffer != 0) {
                    lv_framebuffer[b * SCREEN_WIDTH + a] = weaponsBuffer;
                }
            }
        }
    } else if (g_state.stepTemp == 2) {
        wStart = SCREEN_WIDTH - chutou3_texWidth - 40;
        hStart = SCREEN_HEIGHT - chutou3_texHeight;
        for (uint16_t a = wStart; a < wStart + chutou3_texWidth; a++) {
            for (uint16_t b = hStart; b < hStart + chutou3_texHeight; b++) {
                weaponsBuffer = READ16(chutou3, c);
                c += 2;
                if (weaponsBuffer != 0) {
                    lv_framebuffer[b * SCREEN_WIDTH + a] = weaponsBuffer;
                }
            }
        }
    }
}

// 绘制地面和天花板
static void DRAW_FLOOR_AND_CEILING_REGION(int xs, int ys, int xe, int ye) {
    uint16_t color;
    int8_t floorTexture = 3;
    int8_t ceilingTexture = 6;
    for (int y = ys; y < ye; y++) {
        uint16_t* fb_row = lv_framebuffer + y * SCREEN_WIDTH;
        float rayDirX0 = g_state.dirX - g_state.planeX;
        float rayDirY0 = g_state.dirY - g_state.planeY;
        float rayDirX1 = g_state.dirX + g_state.planeX;
        float rayDirY1 = g_state.dirY + g_state.planeY;
        int p = y - (SCREEN_HEIGHT / 2 + g_state.pitch);
        if (p == 0) continue;
        float posZ = 0.5f * SCREEN_HEIGHT;
        float rowDistance = posZ / p;
        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
        float floorX = g_state.posX + rowDistance * rayDirX0 + floorStepX * xs;
        float floorY = g_state.posY + rowDistance * rayDirY0 + floorStepY * xs;
        for (int x = xs; x < xe; ++x) {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);
            int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
            int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
            floorX += floorStepX;
            floorY += floorStepY;
            int idx = ((texWidth * ty + tx) << 1);
            if (y > SCREEN_HEIGHT / 2 + g_state.pitch) {
                color = READ16(texture[floorTexture], idx);
            } else {
                color = READ16(texture[ceilingTexture], idx);
            }
            color = CHANGE_SIDE_TEX_COLOR(color);
            fb_row[x] = color;
        }
    }
}

static void DRAW_FLOOR_AND_CEILING(void) {
    for (int y = 0; y < SCREEN_HEIGHT; y += CHUNK_H) {
        for (int x = 0; x < SCREEN_WIDTH; x += CHUNK_W) {
            int xe = x + CHUNK_W; if (xe > SCREEN_WIDTH) xe = SCREEN_WIDTH;
            int ye = y + CHUNK_H; if (ye > SCREEN_HEIGHT) ye = SCREEN_HEIGHT;
            DRAW_FLOOR_AND_CEILING_REGION(x, y, xe, ye);
        }
    }
}

// Raycasting主渲染函数
static void RAYCASTING_REGION(int xs, int xe, int ys, int ye) {
    const float invSW = 1.0f / (float)SCREEN_WIDTH;
    const float twoInvSW = 2.0f * invSW;
    const int centerY = SCREEN_HEIGHT / 2 + g_state.pitch;
    for (int x = xs; x < xe; x++) {
        float cameraX = twoInvSW * x - 1.0f;
        float rayDirX = g_state.dirX + g_state.planeX * cameraX;
        float rayDirY = g_state.dirY + g_state.planeY * cameraX;
        int mapX = (int)g_state.posX;
        int mapY = (int)g_state.posY;
        float sideDistX, sideDistY;
        float deltaDistX = (rayDirX == 0.0f) ? 1e30f : fabsf(1.0f / rayDirX);
        float deltaDistY = (rayDirY == 0.0f) ? 1e30f : fabsf(1.0f / rayDirY);
        float perpWallDist;
        int stepX, stepY;
        int hit = 0;
        int side;
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (g_state.posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - g_state.posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (g_state.posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - g_state.posY) * deltaDistY;
        }

        // DDA算法
        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (mapX < 0) { mapX = 0; hit = 1; break; }
            if (mapX >= MAP_WIDTH) { mapX = MAP_WIDTH - 1; hit = 1; break; }
            if (mapY < 0) { mapY = 0; hit = 1; break; }
            if (mapY >= MAP_HEIGHT) { mapY = MAP_HEIGHT - 1; hit = 1; break; }
            if (worldMap[mapX][mapY] > 0) {
                hit = 1;
            }
        }
        if (side == 0) {
            perpWallDist = (sideDistX - deltaDistX);
        } else {
            perpWallDist = (sideDistY - deltaDistY);
        }

        // 保存屏幕中心的目标信息
        if (x == SCREEN_WIDTH / 2) {
            g_state.targetDistance = perpWallDist;
            g_state.targetMapX = mapX;
            g_state.targetMapY = mapY;
        }
        int lineHeight = (int)((float)SCREEN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + centerY;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + centerY;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
        // 获取纹理
        uint16_t color;
        uint8_t texNum = 0;
        if (worldMap[mapX][mapY] > 0) {
            texNum = worldMap[mapX][mapY] - 1;
        }
        
        // 计算纹理坐标
        float wallX;
        if (side == 0) {
            wallX = g_state.posY + perpWallDist * rayDirY;
        } else {
            wallX = g_state.posX + perpWallDist * rayDirX;
        }
        wallX -= floor(wallX);
        int texX = (int)(wallX * (double)texWidth);
        if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0)) {
            texX = texWidth - texX - 1;
        }
        float oneStep = 1.0f * texHeight / (float)lineHeight;
        float texPos = (drawStart - centerY + lineHeight / 2) * oneStep;
        int y0 = drawStart; if (y0 < ys) { texPos += oneStep * (ys - y0); y0 = ys; }
        int y1 = drawEnd; if (y1 > ye) { y1 = ye; }
        uint16_t* p = lv_framebuffer + y0 * SCREEN_WIDTH + x;
        for (int y = y0; y < y1; y++) {
            int texY = (int)texPos & (texHeight - 1);
            texPos += oneStep;
            color = SAMPLE_WALL_COLOR(texNum, texX, texY);
            if (side == 1) {
                color = CHANGE_SIDE_TEX_COLOR(color);
            }
            *p = color;
            p += SCREEN_WIDTH;
        }
    }
}

static void RAYCASTING(void) {
    for (int y = 0; y < SCREEN_HEIGHT; y += CHUNK_H) {
        for (int x = 0; x < SCREEN_WIDTH; x += CHUNK_W) {
            int xe = x + CHUNK_W; if (xe > SCREEN_WIDTH) xe = SCREEN_WIDTH;
            int ye = y + CHUNK_H; if (ye > SCREEN_HEIGHT) ye = SCREEN_HEIGHT;
            RAYCASTING_REGION(x, xe, y, ye);
        }
    }
}

// 处理移动和旋转
static void processMovement(void) {
    g_state.oldFrame = g_state.nowFrame;
    g_state.nowFrame = millis();
    float frameTime = (g_state.nowFrame - g_state.oldFrame) / 1000.0f;
    float moveSpeed = frameTime * 4.0f;
    float rotSpeed = frameTime * 2.0f;
    int pitchStep = (int)(frameTime * 60.0f);
    if (pitchStep < 1) pitchStep = 1;
    int maxPitch = SCREEN_HEIGHT / 3;
    
    uint8_t a = currentKey;
    
    // 步伐动画
    if (a != 0 && a != MINECRAFT_KEY_ACTION) {
        if (millis() >= g_state.t2 + 300) {
            g_state.t2 = millis();
            g_state.stepTemp = (g_state.stepTemp == 0) ? 1 : 0;
        }
    } else {
        if (g_state.stepTemp != 0 && a == 0) {
            g_state.stepTemp = 0;
        }
        // 攻击动画
        if (a == MINECRAFT_KEY_ACTION) {
            if (millis() >= g_state.t3 + 200) {
                g_state.t3 = millis();
                if (g_state.attackTemp < 4) {
                    g_state.stepTemp = attackActionGroup[g_state.attackTemp];
                    g_state.attackTemp++;
                } else {
                    g_state.attackTemp = 0;
                    g_state.stepTemp = 0;
                    if (CHECK_MAP_SIDE()) {
                        WEAPONHIT();
                    }
                }
            }
        }
    }
    
    // 处理按键
    switch (a) {
        case MINECRAFT_KEY_UP: // 前进
            if (worldMap[(int)(g_state.posX + g_state.dirX * moveSpeed)][(int)g_state.posY] == 0) {
                g_state.posX += g_state.dirX * moveSpeed;
            }
            if (worldMap[(int)g_state.posX][(int)(g_state.posY + g_state.dirY * moveSpeed)] == 0) {
                g_state.posY += g_state.dirY * moveSpeed;
            }
            break;

        case MINECRAFT_KEY_DOWN: // 后退
            if (worldMap[(int)(g_state.posX - g_state.dirX * moveSpeed)][(int)g_state.posY] == 0) {
                g_state.posX -= g_state.dirX * moveSpeed;
            }
            if (worldMap[(int)g_state.posX][(int)(g_state.posY - g_state.dirY * moveSpeed)] == 0) {
                g_state.posY -= g_state.dirY * moveSpeed;
            }
            break;
            
        case  MINECRAFT_KEY_LEFT: // 左转
        {
            float cs = cosf(rotSpeed);
            float sn = sinf(rotSpeed);
            float oldDirX = g_state.dirX;
            g_state.dirX = g_state.dirX * cs - g_state.dirY * sn;
            g_state.dirY = oldDirX * sn + g_state.dirY * cs;
            float oldPlaneX = g_state.planeX;
            g_state.planeX = g_state.planeX * cs - g_state.planeY * sn;
            g_state.planeY = oldPlaneX * sn + g_state.planeY * cs;
        }
        break;

        case MINECRAFT_KEY_RIGHT: // 右转
        {
            float cs = cosf(rotSpeed);
            float sn = sinf(rotSpeed);
            sn = -sn;
            float oldDirX = g_state.dirX;
            g_state.dirX = g_state.dirX * cs - g_state.dirY * sn;
            g_state.dirY = oldDirX * sn + g_state.dirY * cs;
            float oldPlaneX = g_state.planeX;
            g_state.planeX = g_state.planeX * cs - g_state.planeY * sn;
            g_state.planeY = oldPlaneX * sn + g_state.planeY * cs;
        }
        break;
        case MINECRAFT_KEY_LOOK_UP:
            g_state.pitch -= pitchStep;
            if (g_state.pitch < -maxPitch) g_state.pitch = -maxPitch;
            break;
        case MINECRAFT_KEY_LOOK_DOWN:
            g_state.pitch += pitchStep;
            if (g_state.pitch > maxPitch) g_state.pitch = maxPitch;
            break;
        
    }
}

// 转换framebuffer为显示缓冲
// 已不再需要翻转缓冲

// 初始化游戏
void Minecraft_Init(void) {
    memset(&g_state, 0, sizeof(g_state));
    // 初始位置和方向
    g_state.posX = 22.0f;
    g_state.posY = 12.0f;
    g_state.dirX = -1.0f;
    g_state.dirY = 0.0f;
    g_state.planeX = 0.0f;
    g_state.planeY = 1.0f;
    g_state.pitch = 0;
    // 初始化时间
    g_state.nowFrame = millis();
    g_state.oldFrame = g_state.nowFrame;
    g_state.t2 = g_state.t3 = g_state.t4 = g_state.t5 = g_state.t6 = g_state.nowFrame;
    if (!lv_framebuffer) {
        lv_framebuffer = (uint16_t *)pvPortMalloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint16_t));
    }
    currentKey = 0;
}

// 游戏主循环
void Minecraft_Loop(void) { 
    UPDATE_JNTM();
    UPDATE_BADAPPLE();
    DRAW_FLOOR_AND_CEILING();
    RAYCASTING();
    processMovement();
    DRAW_WEAPONS_TO_SCREEN(1);
}

// 处理按键输入
void Minecraft_HandleKey(uint8_t key) {
    currentKey = key;
}

// 获取帧缓冲指针
uint16_t* Minecraft_GetFramebuffer(void) {
    return lv_framebuffer;
}

// 释放运行时缓冲
void Minecraft_Deinit(void) {
    if (lv_framebuffer) {
        vPortFree(lv_framebuffer);
        lv_framebuffer = NULL;
    }
}

// ===============================
// 我的世界游戏实现
// ===============================

lv_timer_t *minecraft_timer = NULL;
lv_obj_t *minecraft_img = NULL;

// 游戏循环定时器回调
void minecraft_timer_cb(lv_timer_t *timer) {
    (void)timer;

    Minecraft_Loop();
    if (lv_obj_is_valid(minecraft_img)) {
        lv_obj_invalidate(minecraft_img);
    }
}

void cleanup_scr_minecraft(lv_ui *ui) {
    // 停止定时器
    if (minecraft_timer) {
        lv_timer_del(minecraft_timer);
        minecraft_timer = NULL;
    }
    if (lv_obj_is_valid(minecraft_img)) {
        lv_obj_del(minecraft_img);
        minecraft_img = NULL;
    }
    Minecraft_Deinit();
    (void)ui;
}

void minecraft_app_screen_delete_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_DELETE: {
        cleanup_scr_minecraft(&guider_ui);
        break;
    }
    default:
        break;
    }
}

