cmake_minimum_required(VERSION 3.15)

# User is responsible to set two mandatory options:
# FREERTOS_CONFIG_FILE_DIRECTORY
# FREERTOS_PORT
#
# User can choose which heap implementation to use (either the implementations
# included with FreeRTOS [1..5] or a custom implementation ) by providing the
# option FREERTOS_HEAP. If the option is not set, the cmake will default to
# using heap_4.c.

# Absolute path to FreeRTOS config file directory
set(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_SOURCE_DIR}/FreeRTOS" CACHE STRING "Absolute path to the directory with FreeRTOSConfig.h")

if(NOT FREERTOS_CONFIG_FILE_DIRECTORY)
    message(FATAL_ERROR " FreeRTOSConfig.h file directory not specified. Please specify absolute path to it from top-level CMake file:\n"
        "  set(FREERTOS_CONFIG_FILE_DIRECTORY <absolute path to FreeRTOSConfig.h directory> CACHE STRING \"\")\n"
        " or from CMake command line option:\n"
        "  -DFREERTOS_CONFIG_FILE_DIRECTORY='/absolute_path/to/FreeRTOSConfig.h/directory'")
elseif(NOT EXISTS ${FREERTOS_CONFIG_FILE_DIRECTORY}/FreeRTOSConfig.h)
    message(FATAL_ERROR " FreeRTOSConfig.h file not found in the directory specified (${FREERTOS_CONFIG_FILE_DIRECTORY})\n"
        " Please specify absolute path to it from top-level CMake file:\n"
        "  set(FREERTOS_CONFIG_FILE_DIRECTORY <absolute path to FreeRTOSConfig.h directory> CACHE STRING \"\")\n"
        " or from CMake command line option:\n"
        "  -DFREERTOS_CONFIG_FILE_DIRECTORY='/absolute_path/to/FreeRTOSConfig.h/directory'")
endif()

# Heap number or absolute path to custom heap implementation provided by user
set(FREERTOS_HEAP "4" CACHE STRING "FreeRTOS heap model number. 1 .. 5. Or absolute path to custom heap source file")

# FreeRTOS port option
set(FREERTOS_PORT "GCC_ARM9_F1C200S" CACHE STRING "FreeRTOS port name")

add_subdirectory(portable)

add_library(freertos_kernel STATIC
    croutine.c
    event_groups.c
    list.c
    queue.c
    stream_buffer.c
    tasks.c
    timers.c

    # If FREERTOS_HEAP is digit between 1 .. 5 - it is heap number, otherwise - it is path to custom heap source file
    $<IF:$<BOOL:$<FILTER:${FREERTOS_HEAP},EXCLUDE,^[1-5]$>>,${FREERTOS_HEAP},portable/MemMang/heap_${FREERTOS_HEAP}.c>
)

target_include_directories(freertos_kernel
    PUBLIC
        include
        ${FREERTOS_CONFIG_FILE_DIRECTORY}
)

target_link_libraries(freertos_kernel freertos_kernel_port)
