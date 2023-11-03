cmake_minimum_required(VERSION 3.26)

# 设置目标处理器为arm
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 是否打印gcc编译输出
# set(CMAKE_VERBOSE_MAKEFILE ON)

# 设置交叉编译工具链
set(CROSS_COMPILER     "arm-none-eabi-")
set(CMAKE_C_COMPILER   "${CROSS_COMPILER}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_COMPILER}g++")
set(CMAKE_ASM_COMPILER "${CROSS_COMPILER}gcc")
set(CMAKE_OBJCOPY      "${CROSS_COMPILER}objcopy")
set(CMAKE_OBJDUMP      "${CROSS_COMPILER}objdump")
set(CMAKE_SIZE         "${CROSS_COMPILER}size")

# pc编译报错处理
set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} --specs=nosys.specs")
set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} --specs=nosys.specs")
set(CMAKE_ASM_FLAGS    "${CMAKE_C_FLAGS} --specs=nosys.specs")

# 开启汇编支持
ENABLE_LANGUAGE(ASM)

project(F1C100S)

add_subdirectory(boot)
add_subdirectory(FreeRTOS)
add_subdirectory(projects)