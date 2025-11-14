#ifndef MINECRAFT_TEXTURES_H
#define MINECRAFT_TEXTURES_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

// 纹理尺寸定义
#define texWidth  32
#define texHeight 32
#define textureData (texWidth * texHeight * 2)

// 主纹理数据
extern const uint8_t texture[30][textureData];

// 裂纹纹理
extern const uint8_t liewen[3][textureData];

// 武器纹理定义
#define chutou1_texWidth  40
#define chutou1_texHeight  46
#define chutou2_texWidth  40
#define chutou2_texHeight  49
#define chutou3_texWidth  40
#define chutou3_texHeight  66

extern const uint8_t chutou1[3680];
extern const uint8_t chutou2[3920];
extern const uint8_t chutou3[5280];

// JNTM动画纹理
#if MC_ENABLE_JNTM
extern const uint8_t jntm[45][textureData];
#endif

// BadApple动画纹理
#if MC_ENABLE_BADAPPLE
extern const uint8_t badapple[75][textureData];
#endif

#ifdef __cplusplus
}
#endif

#endif // MINECRAFT_TEXTURES_H
#ifndef MC_ENABLE_BADAPPLE
#define MC_ENABLE_BADAPPLE 1
#endif
#ifndef MC_ENABLE_JNTM
#define MC_ENABLE_JNTM 1
#endif
