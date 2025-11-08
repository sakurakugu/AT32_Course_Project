
GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/custom/*.c))

# 导入 calculator app 源文件
GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/../src/app/calculator/*.c))

DEPPATH += --dep-path $(PRJ_DIR)/custom
VPATH += :$(PRJ_DIR)/custom

CFLAGS += "-I$(PRJ_DIR)/custom"

# 导入 calculator app 头文件
DEPPATH += --dep-path $(PRJ_DIR)/../src/app/calculator
VPATH += :$(PRJ_DIR)/../src/app/calculator
CFLAGS += "-I$(PRJ_DIR)/../src/app/calculator"
