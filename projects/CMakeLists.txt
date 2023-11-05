cmake_minimum_required(VERSION 3.26)

project(F1C100S_PRO)

# 设置编译器标志
set(DRAM_SIZE              "64M")
set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} -Os -march=armv5te -mtune=arm926ej-s -mfloat-abi=soft -marm -mno-thumb-interwork -g -ggdb -Wall -fdata-sections -ffunction-sections -ffreestanding -std=gnu99 -fomit-frame-pointer -Wall -fverbose-asm")
set(CMAKE_ASM_FLAGS        "${CMAKE_C_FLAGS} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles -Xlinker --gc-sections -T${CMAKE_SOURCE_DIR}/f1c100s/f1c100s_dram.ld -Wl,--defsym=DRAM_SIZE=${DRAM_SIZE},-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch")

# 设置宏定义
add_definitions("-DLOAD_HEADER -D__ARM32_ARCH__=5 -D__ARM926EJS__ -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES=1 -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES_HARD=1")

set(ASM_PATH ${CMAKE_SOURCE_DIR}/f1c100s/arm926/)
include_directories(${ASM_PATH}/inc)
file(GLOB_RECURSE ASM_SRC ${ASM_PATH}/src/*.S)

set(DRIVER_PATH ${CMAKE_SOURCE_DIR}/f1c100s/drivers/)
include_directories(${DRIVER_PATH}/inc)
aux_source_directory(${DRIVER_PATH}/src DRIVER_SRC)

set(DPGFX_PATH ${CMAKE_SOURCE_DIR}/lib/display_gfx)
include_directories(${DPGFX_PATH})
aux_source_directory(${DPGFX_PATH} DPGFX_SRC)

set(PRINTF_PATH ${CMAKE_SOURCE_DIR}/lib/printf)
include_directories(${PRINTF_PATH})
aux_source_directory(${PRINTF_PATH} PRINTF_SRC)

set(SYSCALLS_PATH ${CMAKE_SOURCE_DIR}/lib/syscalls)
include_directories(${SYSCALLS_PATH})
aux_source_directory(${SYSCALLS_PATH} SYSCALLS_SRC)

set(PROJECT_PATH ${CMAKE_SOURCE_DIR}/projects)
include_directories(${PROJECT_PATH})
aux_source_directory(${PROJECT_PATH} PROJECT_SRC)

add_executable(${PROJECT_NAME} ${PROJECT_SRC} ${ASM_SRC} ${DRIVER_SRC} ${DPGFX_SRC} ${PRINTF_SRC} ${SYSCALLS_SRC})

target_link_libraries(${PROJECT_NAME} FREERTOS gcc m c_nano)

set(ELF_FILE "${CMAKE_SOURCE_DIR}/build/projects/${PROJECT_NAME}")
set(BIN_FILE "${CMAKE_SOURCE_DIR}/build/projects/${PROJECT_NAME}.bin")

add_custom_command(
    TARGET  ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} ${CMAKE_SOURCE_DIR}
)
