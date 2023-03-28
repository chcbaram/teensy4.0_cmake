cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools")
include(toolchain)

set(PRJ_NAME teensy_fw)


project(${PRJ_NAME}
  LANGUAGES ASM C CXX
)


set(EXECUTABLE ${PRJ_NAME}.elf)


file(GLOB SRC_FILES CONFIGURE_DEPENDS
  src/*.c
)

file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
  src/ap/*.c
  src/bsp/*.c
  src/bsp/*.S
  src/common/*.c
  src/hw/*.c
  src/lib/sdk/drivers/*.c
  src/lib/config/board/*.c
)

add_executable(${EXECUTABLE} 
  ${SRC_FILES}
  ${SRC_FILES_RECURSE}
)

target_include_directories(${EXECUTABLE} PRIVATE 
  src  
  src/ap
  src/bsp
  src/bsp/device
  src/bsp/device/cmsis/Include
  src/bsp/device/xip_boot
  src/common 
  src/common/core
  src/common/hw/include 
  src/hw
  src/lib

  src/lib/sdk/drivers
  src/lib/config/board
)

target_compile_definitions(${EXECUTABLE} PRIVATE
  -DCPU_MIMXRT1062DVL6A
  -D__USE_CMSIS
  -DXIP_BOOT_HEADER_ENABLE=1
  -DXIP_EXTERNAL_FLASH=1
  )

target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-m7
  -mthumb
  -mfpu=fpv5-d16 
  -mfloat-abi=hard
  
  -fmessage-length=0 
  -fsigned-char

  -fdata-sections
  -ffunction-sections

  -Wunused -Wuninitialized

  -std=gnu99 -MMD -MP
  
  #-save-temps -fverbose-asm  # make asm file
  
  -Wall
  -g3
  -Og
  )

target_link_options(${EXECUTABLE} PRIVATE
  -T../src/bsp/ldscript/MIMXRT1062xxxxx_flexspi_nor.ld

  -mcpu=cortex-m7
  -mthumb
  -mfpu=fpv5-d16 
  -mfloat-abi=hard
  
  -fmessage-length=0 
  -fsigned-char

  -fdata-sections
  -ffunction-sections

  -Wunused -Wuninitialized
  
  --specs=nano.specs 
  --specs=nosys.specs
  
  -lc
  -lm
  -lstdc++
  -lsupc++
  
  -Wl,-Map=${PRJ_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker -print-memory-usage -Xlinker
  )

  add_custom_command(TARGET ${EXECUTABLE} 
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
    COMMENT "Invoking: Make Binary"
    )

  add_custom_command(TARGET ${EXECUTABLE} 
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
    COMMENT "Invoking: Make Hex"
    )  