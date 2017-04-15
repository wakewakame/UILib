#include "UILib.h"

void UILib::init(int *argc, char *argv[]) {
	//変数初期化
	f_exit = 0;

	//GLFW初期化
	if (glfwInit() == GL_FALSE) {
		f_exit = 1;
		return;
	}
	
	// ウィンドウ生成
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
	if (win.hwnd == NULL)
	{
		f_exit = 1;
		return;
	}
	
	//生成したウィンドウをOpenGLの処理対象にする
	glfwMakeContextCurrent(GLhwnd);
	
	//ブレンドモード有効化
	glEnable(GL_BLEND); //ブレンドモード有効化
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //アルファブレンド適用

	//ウィンドウとビューポートの同期
	resize();
	return;
}

void UILib::resize() {
	if (f_exit) return;
	//ウィンドウ全体をビューポートにする
	glViewport(0, 0, win.size.x, win.size.y);

	//変換行列の初期化
	glLoadIdentity();

	//スクリーン上の表示領域をビューポートの大きさに比例させる
	glOrtho(0.0, (double)win.size.x, (double)win.size.y, 0.0, -1.0, 1.0);
}

void UILib::loop() {
	if (f_exit) return;
	//ウィンドウが開いている間繰り返す
	while (glfwWindowShouldClose(GLhwnd) == GL_FALSE)
	{
		//ウィンドウを消去する
		glClear(GL_COLOR_BUFFER_BIT);

		//ウィンドウの背景色設定

		///debug///
		glClearColor(1.0, 1.0, 1.0, 1.0);
		///debug///

		//描画処理
		
		///debug///
		static int a = 50;
		a = (a + 1) % 100;
		glClear(GL_COLOR_BUFFER_BIT);
		glColor4d(0.0, 1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glVertex2d(0.0, 0.0);
		glVertex2d(100.0, 0.0);
		glVertex2d(100.0, 100.0);
		glVertex2d(0.0, 100.0);
		glEnd();
		glColor4d(1.0, 0.0, 0.0, 0.5);
		glBegin(GL_QUADS);
		glVertex2d(10.0 + (double)a, 10.0);
		glVertex2d(90.0 + (double)a, 10.0);
		glVertex2d(90.0 + (double)a, 90.0);
		glVertex2d(10.0 + (double)a, 90.0);
		glEnd();
		glFlush();
		///debug///

		//カラーバッファを入れ替える
		glfwSwapBuffers(GLhwnd);

		//イベントが発生するまで待機
		glfwWaitEvents();
	}
}

void UILib::exit() {
	//GLFWの終了
	glfwTerminate();
}