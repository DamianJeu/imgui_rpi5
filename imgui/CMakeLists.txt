cmake_minimum_required(VERSION 3.10)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(IMGUI_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(IMGUI_BACKEND_DIR ${CMAKE_CURRENT_SOURCE_DIR}/backends)


set(IMGUI_SOURCES
	${IMGUI_SRC_DIR}/imgui.cpp
	${IMGUI_SRC_DIR}/imgui_draw.cpp
	${IMGUI_SRC_DIR}/imgui_tables.cpp
	${IMGUI_SRC_DIR}/imgui_widgets.cpp
	${IMGUI_BACKEND_DIR}/imgui_impl_glfw.cpp
	${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC 
	${IMGUI_INCLUDE_DIR}
	${IMGUI_BACKEND_DIR}
)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
