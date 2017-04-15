#pragma once
#pragma comment(lib, "opengl32.lib")

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "win_info.h"

class UILib {
public:
//変数宣言
	//ウィンドウ情報保持変数初期化
	WINDOW_INFO win;
	//GLFWのハンドル
	GLFWwindow *GLhwnd;

//関数宣言
	//初期化関数
	bool init(int *argc, char *argv[]);
	//ウィンドウとビューポートを同期
	void resize();
	//ループ関数
	void loop();
	//終了時処理
	void exit();
};