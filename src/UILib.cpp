#include "UILib.h"

void UILib::viewport_resize() {
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

	//OpenGL Version 4.3を指定
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//ウィンドウ生成
	win.set_GLhwnd(
		glfwCreateWindow
			(
				win.size.x,
				win.size.y,
				win.title.c_str(),
				NULL,
				NULL
			)
	);
	
	//ウィンドウが生成されていなければ終了
	if (error(win.hwnd == NULL)) return;
	
	//生成したウィンドウをOpenGLの処理対象にする
	glfwMakeContextCurrent(win.gl_hwnd);

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

	//ウィンドウとビューポートの座標単位同期
	viewport_resize();

	//垂直同期のタイミングを待つ
	glfwSwapInterval(1);

	//フレームレート設定
	win.fps.SetFPS(30);

	//windowフレーム初期化
	window.win = &win;
	window_resize(1);

	return;
}

void UILib::loop() {
	//エラー確認
	if (f_exit) return;

	//ウィンドウが開いている間繰り返す
	while (glfwWindowShouldClose(win.gl_hwnd) == GL_FALSE)
	{
		//イベントが発生するまで待機
		glfwPollEvents();

		//イベント処理等
		win.loop();

		//画面初期化
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//描画
		render();

		//リサイズ処理
		window_resize();

		//バッファに描画
		glFlush();

		//カラーバッファを入れ替える
		glfwSwapBuffers(win.gl_hwnd);
	}

}

void UILib::render() {
	window.draw();
	return;
}

void UILib::window_resize(bool init) {
	if(win.resize_flag || init){
		//windowフレームサイズ同期
		window.resize({ 0.0, 0.0, (double)win.size.x, (double)win.size.y });
		//ウィンドウとビューポートの座標単位同期
		viewport_resize();
	}
}

void UILib::exit() {
	if (f_exit) return;
	//GLFWの終了
	glfwTerminate();

	return;
}