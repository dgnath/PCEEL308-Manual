# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyEmbeddedProject)

# Compiler options
# Specify the cross-compiler for ARM architecture
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

# Set microcontroller model details
# Define the target microcontroller model for compiler optimizations
set(MCU_MODEL STM32F103C8)

# Compiler and linker flags for the microcontroller
# Customize compiler flags for specific microcontroller model
set(MCU_OPTIONS
    -mcpu=${MCU_MODEL}
    -mthumb
    -mfloat-abi=soft
    -mno-thumb-interwork
)

# Set build type
# Choose between Debug and Release builds
set(CMAKE_BUILD_TYPE Debug)

# Global compiler options
# Apply compiler options globally for all targets
add_compile_options(
    ${MCU_OPTIONS}
    -Wall
    -Wextra
    -Werror
)

# Include directories
# Specify the directories to search for header files
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Source directories
# Add subdirectories for source code, libraries, tests, and tools
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(tools)

# Generate binary
# Create a custom target to generate binary file from the executable
add_custom_target(${PROJECT_NAME}.bin ALL
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
    DEPENDS ${PROJECT_NAME}
    COMMENT "Generating binary file"
)

# Linker options
# Customize linker options for microcontroller-specific settings
add_link_options(
    ${MCU_OPTIONS}
    -specs=nosys.specs
    -T${CMAKE_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld
)