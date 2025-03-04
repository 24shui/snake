# Makefile格式
# 目标文件:依赖的文件
# Tab 命令1
# Tab 命令2

# 定义变量
ARCH ?= arm
TARGET = main

# 存放中间文件和目标文件的路径
BUILD_DIR = build_$(ARCH)

# 存放源文件的文件夹
SRC_DIR = ./sources

# 存放头文件的文件夹
INC_DIR = ./includes

# 库文件路径
LIB_PATH = -L./lib

# 库名称
LIB_NAMES = -lpthread -lm -lfont

# 源文件（.cpp）
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# 目标文件（*.o）
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))

# 头文件
DEPS = $(wildcard $(INC_DIR)/*.h) $(wildcard $(INC_DIR)/*.hpp)

# 指定头文件的路径
CFLAGS = -I$(INC_DIR) -std=c++11

# 根据输入的ARCH变量来选择编译器
# ARCH=arm，使用arm-linux-g++
ifeq ($(ARCH),arm)
  CC = arm-linux-g++
else
  $(error Unsupported ARCH: $(ARCH))
endif

# 目标文件
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIB_NAMES) $(LIB_PATH)

# *.o文件的生成规则
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	@mkdir -p $(BUILD_DIR)  # 创建编译目录，用于存放中间文件
	$(CC) -c -o $@ $< $(CFLAGS)

# 伪目标
.PHONY: clean cleanall

# 删除当前架构的编译文件
clean:
	rm -rf $(BUILD_DIR)

# 删除所有编译文件
cleanall:
	rm -rf build_*