#include "minecraft.h"
#include "minecraft_textures.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>

// 获取当前时间(毫秒)
static inline uint32_t millis(void) {
    return xTaskGetTickCount();
}

// 世界地图
static int8_t worldMap[MAP_WIDTH][MAP_HEIGHT] = {
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

// 帧缓冲 (c要用)
static uint16_t (*frameImage)[SCREEN_HEIGHT] = NULL;
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
    uint16_t newColor = ((color_Red / 2) << 11) | ((color_Green / 2) << 5) | (color_Blue / 2);
    return newColor;
}

// 将8位纹理转换为16位
static inline uint16_t READ16(const unsigned char* base, int idx) {
    return (uint16_t)(base[idx] << 8) | (uint16_t)(base[idx + 1]);
}

// 混合纹理
static inline uint16_t SAMPLE_WALL_COLOR(int8_t texNum, int texX, int texY) {
    int idx = ((texHeight * texX + texY) << 1);
    if (texNum < 30) {
        if (texNum == 15 || texNum == 16) {
            return READ16(badapple[g_state.badappleFrame], idx);
        }
        return READ16(texture[texNum], idx);
    }
    if (texNum == 90) {
        return READ16(jntm[g_state.jntmFrame], idx);
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
    if (millis() >= g_state.t4 + 200) {
        g_state.t4 = millis();
        if (g_state.jntmFrame < 44) {
            g_state.jntmFrame++;
        } else {
            g_state.jntmFrame = 0;
        }
    }
}

// 播放JNTM动画
static inline void UPDATE_BADAPPLE(void) {
    if (millis() >= g_state.t5 + 300) {
        g_state.t5 = millis();
        if (g_state.badappleFrame < 74) {
            g_state.badappleFrame++;
        } else {
            g_state.badappleFrame = 0;
        }
    }
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
    uint8_t wStart = 0, hStart = 0;
    int c = 0;
    uint16_t weaponsBuffer = 0;
    
    if (g_state.stepTemp == 0) {
        wStart = SCREEN_WIDTH - chutou1_texWidth;
        hStart = SCREEN_HEIGHT - chutou1_texHeight;
        for (uint8_t a = wStart; a < wStart + chutou1_texWidth; a++) {
            for (uint8_t b = hStart; b < hStart + chutou1_texHeight; b++) {
                weaponsBuffer = chutou1[c] << 8 | chutou1[c + 1];
                c += 2;
                if (weaponsBuffer != 0) {
                    frameImage[a][b] = weaponsBuffer;
                }
            }
        }
    } else if (g_state.stepTemp == 1) {
        wStart = SCREEN_WIDTH - chutou2_texWidth;
        hStart = SCREEN_HEIGHT - chutou2_texHeight;
        for (uint8_t a = wStart; a < wStart + chutou2_texWidth; a++) {
            for (uint8_t b = hStart; b < hStart + chutou2_texHeight; b++) {
                weaponsBuffer = chutou2[c] << 8 | chutou2[c + 1];
                c += 2;
                if (weaponsBuffer != 0) {
                    frameImage[a][b] = weaponsBuffer;
                }
            }
        }
    } else if (g_state.stepTemp == 2) {
        wStart = SCREEN_WIDTH - chutou3_texWidth - 40;
        hStart = SCREEN_HEIGHT - chutou3_texHeight;
        for (uint8_t a = wStart; a < wStart + chutou3_texWidth; a++) {
            for (uint8_t b = hStart; b < hStart + chutou3_texHeight; b++) {
                weaponsBuffer = chutou3[c] << 8 | chutou3[c + 1];
                c += 2;
                if (weaponsBuffer != 0) {
                    frameImage[a][b] = weaponsBuffer;
                }
            }
        }
    }
}

// 绘制地面和天花板
static void DRAW_FLOOR_AND_CEILING(void) {
    uint16_t color;
    int8_t floorTexture = 3;
    int8_t ceilingTexture = 6;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
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
        float floorX = g_state.posX + rowDistance * rayDirX0;
        float floorY = g_state.posY + rowDistance * rayDirY0;

        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);
            int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
            int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
            floorX += floorStepX;
            floorY += floorStepY;

            int idx = ((texWidth * ty + tx) << 1);
            if (y > SCREEN_HEIGHT / 2 + g_state.pitch) {
                color = (texture[floorTexture][idx] << 8) | texture[floorTexture][idx + 1];
            } else {
                color = (texture[ceilingTexture][idx] << 8) | texture[ceilingTexture][idx + 1];
            }
            color = CHANGE_SIDE_TEX_COLOR(color);
            frameImage[x][y] = color;
        }
    }
}

// Raycasting主渲染函数
static void RAYCASTING(void) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float cameraX = 2.0f * x / (float)SCREEN_WIDTH - 1.0f;
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
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2 + g_state.pitch;
        if (drawStart < 0) drawStart = 0;

        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2 + g_state.pitch;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
        
        // 获取纹理
        uint16_t color;
        int8_t texNum = 0;
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
        float texPos = (drawStart - g_state.pitch - SCREEN_HEIGHT / 2 + lineHeight / 2) * oneStep;
        
        for (int y = drawStart; y < drawEnd; y++) {
            int texY = (int)texPos & (texHeight - 1);
            texPos += oneStep;
            color = SAMPLE_WALL_COLOR(texNum, texX, texY);
            if (side == 1) {
                color = CHANGE_SIDE_TEX_COLOR(color);
            }
            frameImage[x][y] = color;
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
            float oldDirX = g_state.dirX;
            g_state.dirX = g_state.dirX * cosf(rotSpeed) - g_state.dirY * sinf(rotSpeed);
            g_state.dirY = oldDirX * sinf(rotSpeed) + g_state.dirY * cosf(rotSpeed);
            float oldPlaneX = g_state.planeX;
            g_state.planeX = g_state.planeX * cosf(rotSpeed) - g_state.planeY * sinf(rotSpeed);
            g_state.planeY = oldPlaneX * sinf(rotSpeed) + g_state.planeY * cosf(rotSpeed);
        }
        break;

        case MINECRAFT_KEY_RIGHT: // 右转
        {
            float oldDirX = g_state.dirX;
            g_state.dirX = g_state.dirX * cosf(-rotSpeed) - g_state.dirY * sinf(-rotSpeed);
            g_state.dirY = oldDirX * sinf(-rotSpeed) + g_state.dirY * cosf(-rotSpeed);
            float oldPlaneX = g_state.planeX;
            g_state.planeX = g_state.planeX * cosf(-rotSpeed) - g_state.planeY * sinf(-rotSpeed);
            g_state.planeY = oldPlaneX * sinf(-rotSpeed) + g_state.planeY * cosf(-rotSpeed);
        }
        break;
            
    }
}

// 转换framebuffer为显示缓冲
static void wddd(void) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH / 2; x++) {
            uint16_t tmp = frameImage[x][y];
            frameImage[x][y] = frameImage[(SCREEN_WIDTH - 1) - x][y];
            frameImage[(SCREEN_WIDTH - 1) - x][y] = tmp;
        }
    }
}

// 初始化游戏
void minecraft_init(void) {
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
    if (!frameImage) {
        frameImage = (uint16_t (*)[SCREEN_HEIGHT])pvPortMalloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint16_t));
    }
    if (!lv_framebuffer) {
        lv_framebuffer = (uint16_t *)pvPortMalloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint16_t));
    }
    currentKey = 0;
}

// 游戏主循环
void minecraft_loop(void) {
    UPDATE_JNTM();
    UPDATE_BADAPPLE();
    DRAW_FLOOR_AND_CEILING();
    RAYCASTING();
    processMovement();
    DRAW_WEAPONS_TO_SCREEN(1);
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            lv_framebuffer[y * SCREEN_WIDTH + x] = frameImage[x][y];
        }
    }
}

// 处理按键输入
void minecraft_handle_key(uint8_t key) {
    currentKey = key;
}

// 获取帧缓冲指针
uint16_t* minecraft_get_framebuffer(void) {
    return lv_framebuffer;
}

void minecraft_deinit(void) {
    if (frameImage) {
        vPortFree(frameImage);
        frameImage = NULL;
    }
    if (lv_framebuffer) {
        vPortFree(lv_framebuffer);
        lv_framebuffer = NULL;
    }
}
