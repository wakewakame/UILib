#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

//�C�x���g�����̊��N���X
class GET_EVENT {
public:
//�ϐ�������
	//GL�E�B���h�E�n���h��
	GLFWwindow *gl_hwnd;

//�֐�������
	//GL�E�B���h�E�n���h���ݒ�֐�
	virtual void SetGLhwnd(GLFWwindow *set_gl_hwnd);
};