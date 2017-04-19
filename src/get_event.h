#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

//イベント処理の基底クラス
class GET_EVENT {
public:
//変数初期化
	//GLウィンドウハンドル
	GLFWwindow *gl_hwnd;

//関数初期化
	//GLウィンドウハンドル設定関数
	virtual void SetGLhwnd(GLFWwindow *set_gl_hwnd);

	//コンストラクタ
	GET_EVENT();
};