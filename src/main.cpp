#include "UILib.h"

int main(int argc, char *argv[])
{
//コンストラクト
	//UIライブラリ
	UILib ui;

//変数宣言

//メインルーチン
	ui.init();
	ui.loop();
	ui.exit();
	return 0;
}