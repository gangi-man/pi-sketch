cmake_minimum_required(VERSION 3.13)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pi_sketch C CXX ASM)
pico_sdk_init()

set(DVI_DEFAULT_SERIAL_CONFIG "pico_sock_cfg" CACHE STRING
	"Select a default pin configuration from common_dvi_pin_configs.h")

include(../PicoDVI/software/libdvi/CMakeLists.txt)

add_compile_options(-Wall)

include_directories(
	../PicoDVI/software/include
	)

add_executable( ${PROJECT_NAME}
	main.cpp
	rotary_encoder.cpp
	button.cpp
	sketchpad.cpp
	)

target_link_libraries( ${PROJECT_NAME}
       	pico_stdlib
	pico_multicore
	pico_util
	libdvi
	)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})


add_custom_target(upload
	COMMAND sudo ${OPENOCD}
	-f interface/cmsis-dap.cfg
	-f target/rp2040.cfg
	-c \"adapter speed 5000\; program ${PROJECT_NAME}.elf verify\; reset\; exit\"
	)
