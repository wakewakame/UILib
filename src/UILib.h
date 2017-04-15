#pragma once
#pragma comment(lib, "opengl32.lib")

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <Windows.h>
#include "win_info.h"

class UILib {
private:
//変数宣言
	//ウィンドウ情報保持変数初期化
	WINDOW_INFO win;
	//GLFWのハンドル
	GLFWwindow *GLhwnd;
	//フラグ
		//終了フラグ
		bool f_exit;

//関数宣言
	//ウィンドウとビューポートを同期
	void resize();
	//エラー発生時処理関数
	bool error(bool val);

public:
//関数宣言
	//初期化関数
	void init();
	//ループ関数
	void loop();
	//描画関数
	void render();
	//終了時処理
	void exit();
};