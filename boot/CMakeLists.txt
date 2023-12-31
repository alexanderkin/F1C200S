cmake_minimum_required(VERSION 3.26)

project(F1C100S_BOOT)

# 设置编译器标志
set(DRAM_SIZE              "64M")
set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} -Os -march=armv5te -mtune=arm926ej-s -mfloat-abi=soft -marm -mno-thumb-interwork -g -ggdb -Wall -fdata-sections -ffunction-sections -ffreestanding -std=gnu99 -fomit-frame-pointer -Wall -fverbose-asm")
set(CMAKE_ASM_FLAGS        "${CMAKE_C_FLAGS} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles -Xlinker --gc-sections -T${CMAKE_SOURCE_DIR}/f1c100s/f1c100s_sram.ld -Wl,--defsym=DRAM_SIZE=${DRAM_SIZE},-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch")

# 设置宏定义
add_definitions("-DEGON_HEADER -D__ARM32_ARCH__=5 -D__ARM926EJS__ -DPRINTF_SUPPORT_DECIMAL_SPECIFIERS=0 -DPRINTF_SUPPORT_EXPONENTIAL_SPECIFIERS=0 -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES=1 -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES_HARD=1")

# boot的汇编部分因为编译宏不同所以不能直接链接F1C100S_DRIVER，要重新编译
set(ASM_PATH ${CMAKE_SOURCE_DIR}/f1c100s/arm926/)
include_directories(${ASM_PATH}/inc)
file(GLOB_RECURSE ASM_SRC ${ASM_PATH}/src/*.S)

set(BOOT_PATH ${CMAKE_SOURCE_DIR}/boot)
include_directories(${BOOT_PATH})
aux_source_directory(${BOOT_PATH} PROJECT_SRC)

add_executable(${PROJECT_NAME} ${PROJECT_SRC} ${ASM_SRC})

target_link_libraries(${PROJECT_NAME} F1C100S_DRIVER F1C100S_LIB gcc m c_nano)

set(FIX_SRC "${CMAKE_SOURCE_DIR}/tools/mksunxi/mksunxi.c")
set(FIX_EXEC "${CMAKE_SOURCE_DIR}/tools/mksunxi/mksunxi.exe")

if(NOT EXISTS ${FIX_EXEC})
add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND gcc ${FIX_SRC} -o ${FIX_EXEC}
    COMMENT "create mksunxi.exe"
)
endif()

set(ELF_FILE "${CMAKE_SOURCE_DIR}/build/boot/${PROJECT_NAME}")
set(BIN_FILE "${CMAKE_SOURCE_DIR}/build/boot/${PROJECT_NAME}.bin")

add_custom_command(
    TARGET  ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} ${CMAKE_SOURCE_DIR}
    COMMAND ${FIX_EXEC} ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}.bin
    COMMENT "fix binary"
)