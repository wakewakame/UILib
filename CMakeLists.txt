cmake_minimum_required(VERSION 3.10)

# download glew
include(./3rdparty/DownloadProject/DownloadProject.cmake)
download_project(
	PROJ glew_src
	URL https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0.tgz
)

# create project
project(UILib)

# configuration
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add libraries subdirectory
set(LIBRARIES_PATH "${CMAKE_SOURCE_DIR}/3rdparty")
add_subdirectory(${glew_src_SOURCE_DIR}/build/cmake ${glew_src_BINARY_DIR} EXCLUDE_FROM_ALL)
add_subdirectory(${LIBRARIES_PATH}/glfw)
add_subdirectory(${LIBRARIES_PATH}/glm)

# add source files
file(GLOB_RECURSE ALL_CPP_FILES
	"${CMAKE_SOURCE_DIR}/src/Animation.cpp"
	"${CMAKE_SOURCE_DIR}/src/FBO.cpp"
	"${CMAKE_SOURCE_DIR}/src/fps.cpp"
	"${CMAKE_SOURCE_DIR}/src/Frame.cpp"
	"${CMAKE_SOURCE_DIR}/src/get_event.cpp"
	"${CMAKE_SOURCE_DIR}/src/GraphPara.cpp"
	"${CMAKE_SOURCE_DIR}/src/main.cpp"
	"${CMAKE_SOURCE_DIR}/src/mouse.cpp"
	"${CMAKE_SOURCE_DIR}/src/UI.cpp"
	"${CMAKE_SOURCE_DIR}/src/UILib.cpp"
	"${CMAKE_SOURCE_DIR}/src/win_info.cpp"
)
add_executable(UILib "${ALL_CPP_FILES}")

# set include directories
target_include_directories(UILib PRIVATE
	"${glew_src_SOURCE_DIR}/include"
)

# set link libraries
target_link_libraries(UILib
	glew
	glfw
	glm
)
