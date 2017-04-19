#include "get_event.h"

void GET_EVENT::SetGLhwnd(GLFWwindow *set_gl_hwnd) {
	gl_hwnd = set_gl_hwnd;
}

GET_EVENT::GET_EVENT() {
	gl_hwnd = nullptr;
}