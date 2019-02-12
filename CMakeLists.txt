cmake_minimum_required(VERSION 3.12)
project(ATAR_Central)

#===================================================================================================

set(FILES main.cpp)

set(DEVICE atmega2560)
set(FREQ 16000000)

if (APPLE)
    set(AVRBIN /usr/local/CrossPack-AVR/bin)
elseif(WIN32)
    set(AVRBIN /usr/local/CrossPack-AVR/bin)
endif()
set(AVROBJCOPY avr-objcopy)
set(AVRSIZE avr-size)
set(AVRDUDE avrdude)

set(PROGRAMMER wiring)
set(PORT /dev/cu.usbmodem14101)
set(BAUD 115200)

set(EEPROM NO)
set(FLASH YES)

#===================================================================================================

set(CMAKE_C_COMPILER ${AVRBIN}/avr-gcc)
set(CMAKE_CXX_COMPILER ${AVRBIN}/avr-g++)

set(CMAKE_C_FLAGS  "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -std=gnu99 -Wl,--gc-sections")
set(CMAKE_CXX_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -Wl,--gc-sections")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
if (APPLE)
    set(CMAKE_PREFIX_PATH /usr/local/CrossPack-AVR/)
elseif(WIN32)
    set(CMAKE_PREFIX_PATH /usr/local/CrossPack-AVR/)
endif()
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

if (APPLE)
    include_directories(/usr/local/CrossPack-AVR/include)
elseif(WIN32)
    include_directories(/usr/local/CrossPack-AVR/include)
endif()

set(SOURCE_FILES ${FILES})

#===================================================================================================

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${AVRBIN}/${AVROBJCOPY} -O ihex -R .eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.hex)

if(EEPROM)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${AVRBIN}/${AVROBJCOPY} -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.eep)
endif(EEPROM)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${AVRBIN}/${AVRSIZE} --target=ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.hex)

if(FLASH)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${AVRBIN}/${AVRDUDE} -p${DEVICE} -c${PROGRAMMER} -P${PORT} -b${BAUD} -D -U flash:w:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.hex)
endif(FLASH)
