cmake_minimum_required(VERSION 3.8)

project ("christmas-contest" LANGUAGES C CXX)

# Include paths ############################################

add_subdirectory ("engine")

set (ENGINE_INCLUDES
	engine
	#${ENGINE_INCLUDES}
)

add_subdirectory ("game")

set (GAME_INCLUDES
	game
	#${GAME_INCLUDES}
)

set (INCLUDES
	include
	${ENGINE_INCLUDES}
	${GAME_INCLUDES}
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/include/zlib ZLIB)


set (SRCS
	${ZLIB}
	${ENGINE_SRCS}
	${GAME_SRCS}
	main.cpp
)

add_executable (${PROJECT_NAME} ${SRCS})

target_include_directories (${PROJECT_NAME} PRIVATE ${INCLUDES})

target_link_libraries (${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}/lib/freeglut.lib
	#/lib/x64/freeglut.lib
	winmm
	opengl32
	glu32
	gdi32
)


set (CMAKE_C_FLAGS
	${CMAKE_C_FLAGS}
	"-O2 -std=c99 -fno-omit-frame-pointer -fno-common -fdata-sections"
)

set (CMAKE_CXX_FLAGS
	${CMAKE_CXX_FLAGS}
	"-O2 -std=c++14 -fno-omit-frame-pointer -fno-common -fdata-sections"
)

set (CMAKE_EXE_LINKER_FLAGS
	${CMAKE_EXE_LINKER_FLAGS}
	"-Wall -static-libstdc++ -static-libgcc"
)