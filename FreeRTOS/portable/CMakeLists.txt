# FreeRTOS internal cmake file. Do not use it in user top-level project

add_library(freertos_kernel_port STATIC
    $<$<STREQUAL:${FREERTOS_PORT},GCC_ARM9_F1C200S>:
        GCC/ARM9_F1C200S/port.c
        GCC/ARM9_F1C200S/portISR.c>
)

target_include_directories(freertos_kernel_port PUBLIC
    $<$<STREQUAL:${FREERTOS_PORT},GCC_ARM9_F1C200S>:${CMAKE_CURRENT_LIST_DIR}/GCC/ARM9_F1C200S>
)

target_link_libraries(freertos_kernel_port PRIVATE freertos_kernel)
