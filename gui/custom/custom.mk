
GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/custom/*.c))

# 这些仅用于在gui guider中成功编译，keil中不需要编写这些
# 导入 calculator app 源文件
GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/../src/app/calculator/*.c))
# 导入 drawing_board app 源文件
GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/../src/app/drawing_board/*.c))

# 导入 wifi 源文件
GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/../src/board/network/*.c))

DEPPATH += --dep-path $(PRJ_DIR)/custom
VPATH += :$(PRJ_DIR)/custom
CFLAGS += "-I$(PRJ_DIR)/custom"

# 导入 calculator app 头文件
DEPPATH += --dep-path $(PRJ_DIR)/../src/app/calculator
VPATH += :$(PRJ_DIR)/../src/app/calculator
CFLAGS += "-I$(PRJ_DIR)/../src/app/calculator"

# 导入 drawing_board app 头文件
DEPPATH += --dep-path $(PRJ_DIR)/../src/app/drawing_board
VPATH += :$(PRJ_DIR)/../src/app/drawing_board
CFLAGS += "-I$(PRJ_DIR)/../src/app/drawing_board"

# 导入 wifi 头文件
DEPPATH += --dep-path $(PRJ_DIR)/../src/board/network
VPATH += :$(PRJ_DIR)/../src/board/network
CFLAGS += "-I$(PRJ_DIR)/../src/board/network"

# 导入 music 头文件
DEPPATH += --dep-path $(PRJ_DIR)/../src/app/music
VPATH += :$(PRJ_DIR)/../src/app/music
CFLAGS += "-I$(PRJ_DIR)/../src/app/music"
