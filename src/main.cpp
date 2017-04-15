#include "UILib.h"

/*
void display(void)
{
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
}

void resize(int w, int h)
{
	//ウィンドウ全体をビューポートにする
	glViewport(0, 0, w, h);

	//変換行列の初期化
	glLoadIdentity();

	//スクリーン上の表示領域をビューポートの大きさに比例させる
	glOrtho(0.0, (double)w, (double)h, 0.0, -1.0, 1.0);
}

void idle(int value)
{
	const static double fps = 60.0;
	glutPostRedisplay();

	glutPostRedisplay();
	glutTimerFunc(int(1000.0 / fps), idle, 0);
}

void init(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
*/

int main(int argc, char *argv[])
{
//コンストラクト
	//UIライブラリ
	UILib ui;

//変数宣言

//メインルーチン
	ui.init(&argc, argv);
	ui.loop();
	ui.exit();
	return 0;
}