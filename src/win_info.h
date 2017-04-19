#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <Windows.h>
#include "define.h"
#include "mouse.h"
#include "fps.h"

//ウィンドウ情報保持変数
class WINDOW_INFO {
public:
//コンストラクタ
	WINDOW_INFO();

//変数宣言
	POINT size; //ウィンドウサイズ
	POINT b_size; //前フレームのウィンドウサイズ
	HWND hwnd; //OpenGLの生成ウィンドウのハンドル
	GLFWwindow *gl_hwnd; //OpenGLの生成GLウィンドウのハンドル
	MOUSE mouse; //マウスイベント保持クラス
	FPS fps; //フレームレート管理クラス
	std::string title; //ウィンドウタイトル

//関数宣言
	//GLウィンドウハンドル設定関数
	void set_GLhwnd(GLFWwindow *set_gl_hwnd);

	//描画前ループ関数
	void b_loop();

	//描画後ループ関数
	void a_loop();
};