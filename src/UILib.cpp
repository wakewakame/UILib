#include "UILib.h"

void UILib::resize() {
	if (f_exit) return;
	//ウィンドウ全体をビューポートにする
	glViewport(0, 0, win.size.x, win.size.y);

	//変換行列の初期化
	glLoadIdentity();

	//スクリーン上の表示領域をビューポートの大きさに比例させる
	glOrtho(0.0, (double)win.size.x, (double)win.size.y, 0.0, -1.0, 1.0);
}

bool UILib::error(bool val) {
	if (val) {
		exit();
		f_exit = 1;
	}
	return val;
}

void UILib::init() {
	//変数初期化
	f_exit = 0;

	//GLFW初期化
	if (error(glfwInit() == GL_FALSE)) return;

	//OpenGL Version 3.2 Core Profile を選択する
	//glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//ウィンドウ生成
	GLhwnd = glfwCreateWindow
	(
		win.size.x,
		win.size.y,
		win.title.c_str(),
		NULL,
		NULL
	);
	
	//ウィンドウハンドル取得
	win.hwnd = (HWND)GLhwnd;
	
	//ウィンドウが生成されていなければ終了
	if (error(win.hwnd == NULL)) return;
	
	//生成したウィンドウをOpenGLの処理対象にする
	glfwMakeContextCurrent(GLhwnd);

	//GLEW初期化
	glewExperimental = GL_TRUE;
	if (error(glewInit() != GLEW_OK)) return;
	
	//デフォルトでブレンドモード有効化
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //アルファブレンド適用

	//デフォルトでアンチエイリアス適応
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); //点のアンチエイリアス精度最大化
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); //線のアンチエイリアス精度最大化
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST); //面のアンチエイリアス精度最大化
	glEnable(GL_POINT_SMOOTH); //点
	glEnable(GL_LINE_SMOOTH); //線
	glEnable(GL_POLYGON_SMOOTH); //面

	//ウィンドウとビューポートの同期
	resize();

	//垂直同期のタイミングを待つ
	glfwSwapInterval(1);

	return;
}

void UILib::loop() {
	if (f_exit) return;
	//ウィンドウが開いている間繰り返す
	while (glfwWindowShouldClose(GLhwnd) == GL_FALSE)
	{
		//イベントが発生するまで待機
		glfwPollEvents();

		//画面初期化
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//描画
		render();

		//カラーバッファを入れ替える
		glfwSwapBuffers(GLhwnd);
	}
}

void UILib::render() {
	static int a = 50;
	a = (a + 1) % 100;

	glLineWidth(10);
	glColor4d(0.0, 1.0, 1.0, 1.0);
	glDisable(GL_POLYGON_SMOOTH);
	glBegin(GL_QUADS);
	glVertex2d(0.0, 0.0);
	glVertex2d(100.0, 0.0);
	glVertex2d(100.0, 100.0);
	glVertex2d(0.0, 70.0);
	glEnd();
	glEnable(GL_POLYGON_SMOOTH);
	glColor4d(1.0, 0.0, 0.0, 0.5);
	glBegin(GL_LINES);
	glVertex2d(10.0 + (double)a, 10.0);
	glVertex2d(90.0 + (double)a, 10.0);
	glVertex2d(90.0 + (double)a, 90.0);
	glVertex2d(10.0 + (double)a, 20.0);
	glEnd();
	glFlush();

	return;
}

void UILib::exit() {
	if (f_exit) return;
	//GLFWの終了
	glfwTerminate();

	return;
}