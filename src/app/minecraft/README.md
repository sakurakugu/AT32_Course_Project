# Minecraft Raycasting 游戏移植

## 概述
将ESP32C3的Minecraft Raycasting游戏移植到AT32平台,使用LVGL进行显示。

## 游戏参数
- **显示尺寸**: 160x80 (保持原始大小)
- **帧率**: 约30 FPS
- **地图大小**: 24x24

## 按键映射
游戏使用task_key.cpp中的按键系统:

- **KEY2**: 前进 (MINECRAFT_KEY_LEFT)
- **KEY4**: 后退 (MINECRAFT_KEY_RIGHT)
- **KEY6**: 左转 (MINECRAFT_KEY_DOWN)
- **KEY8**: 右转 (MINECRAFT_KEY_UP)
- **KEY5**: 攻击/交互 (MINECRAFT_KEY_ACTION)

## 文件结构
```
src/app/minecraft/
├── minecraft.h           # 游戏头文件
├── minecraft.cpp         # 游戏核心逻辑
├── minecraft_textures.h  # 纹理定义
└── texture/              # 纹理数据
    ├── mapTextures.c     # 方块纹理
    ├── liewen.c          # 裂纹纹理
    ├── chutou.c          # 武器纹理
    ├── jntm.c            # 动画纹理1
    └── badapple.c        # 动画纹理2
```

## 集成说明

### 1. LVGL界面
在`setup_scr_game_minecraft.c`中:
- 创建160x80的画布用于显示游戏画面
- 使用定时器(33ms, 约30 FPS)运行游戏循环
- 画布位于屏幕中心位置(160, 120)

### 2. 按键处理
在`task_key.cpp`中:
- 检测当前屏幕是否为Minecraft游戏界面
- 将硬件按键映射到游戏控制
- 按键按下/释放都会传递给游戏逻辑

### 3. 游戏逻辑
- **Raycasting渲染**: DDA算法进行光线投射
- **纹理映射**: 支持32x32纹理
- **地面/天花板**: 带纹理的地面和天花板渲染
- **武器系统**: 支持攻击动画和方块破坏
- **动画纹理**: JNTM和BadApple动画支持

## 使用方法

1. **初始化**: 进入game_minecraft界面时自动调用`minecraft_init()`
2. **游戏循环**: 定时器每33ms调用一次`minecraft_loop()`
3. **渲染**: 游戏画面通过`minecraft_get_framebuffer()`获取并更新到画布
4. **清理**: 离开界面时调用`cleanup_scr_game_minecraft()`释放资源

## 性能优化
- 使用预计算的纹理缓存
- DDA算法优化墙壁检测
- 帧缓冲直接写入减少拷贝开销

## 注意事项
1. 确保纹理文件已正确复制到texture目录
2. 游戏需要足够的堆内存(约160x80x2 = 25.6KB用于画布)
3. 定时器回调在LVGL任务中执行,注意线程安全

## 调试
- 可以调整定时器周期来改变帧率
- 可以修改画布位置来调整显示位置
- 按键映射可以在task_key.cpp中自定义
