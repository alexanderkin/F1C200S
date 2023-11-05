cmake_minimum_required(VERSION 3.26)

project(F1C100S_DRIVER)

# 设置编译器标志
set(DRAM_SIZE              "64M")
set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} -Os -march=armv5te -mtune=arm926ej-s -mfloat-abi=soft -marm -mno-thumb-interwork -g -ggdb -Wall -fdata-sections -ffunction-sections -ffreestanding -std=gnu99 -fomit-frame-pointer -Wall -fverbose-asm")
set(CMAKE_ASM_FLAGS        "${CMAKE_C_FLAGS} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles -Xlinker --gc-sections -T${CMAKE_SOURCE_DIR}/f1c100s/f1c100s_dram.ld -Wl,--defsym=DRAM_SIZE=${DRAM_SIZE},-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch")

# 设置宏定义
add_definitions("-DLOAD_HEADER -D__ARM32_ARCH__=5 -D__ARM926EJS__ -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES=1 -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES_HARD=1")

set(ASM_PATH ${CMAKE_CURRENT_LIST_DIR}/arm926/)
include_directories(${ASM_PATH}/inc)
file(GLOB_RECURSE ASM_SRC ${ASM_PATH}/src/*.S)

set(DRIVER_PATH ${CMAKE_CURRENT_LIST_DIR}/drivers/)
include_directories(${DRIVER_PATH}/inc)
aux_source_directory(${DRIVER_PATH}/src DRIVER_SRC)

add_library(${PROJECT_NAME} ${ASM_SRC} ${DRIVER_SRC})

target_link_libraries(${PROJECT_NAME} gcc m c_nano)
