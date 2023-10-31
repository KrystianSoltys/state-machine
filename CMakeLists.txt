cmake_minimum_required(VERSION 3.11)

#IMPORTANT!!!!
#ADD -DCMAKE_SYSTEM_NAME=Generic TO RUN THIS SCRIPT!

project("state-machine")

set(PRODUCT_NAME state-machine)

# CPU Name
set(MCU atmega48pa)

# CPU Freq
set(F_CPU 1000000UL)


# Programmer Name
set(PROG_TYPE usbasp)

# AVR GCC Toolchain
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)


# Compiler Defines
add_definitions(
        -DF_CPU=${F_CPU}
        -DBAUD=${BAUD}
)
# Linker Setup
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

add_compile_options(
        -mmcu=${MCU} # MCU
        -std=c11
        -Os
        -Wall
)
file(GLOB SRC_FILES "*.c") # Load all files in src folder

# Create one target
add_executable(${PRODUCT_NAME} ${SRC_FILES})

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)

# Upload the firmware with avrdude
add_custom_target(upload avrdude  -c ${PROG_TYPE} -p ${MCU} -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex)

# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PRODUCT_NAME}.hex;${PRODUCT_NAME}.eeprom;${PRODUCT_NAME}.lst")
