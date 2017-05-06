#include "UILib.h"

int main(int argc, char *argv[])
{

///debug///
#include <math.h>
graph grp;
float wave[1024];
grp.start_index = 0;
grp.end_index = 1023;
grp.num_sample = 1024;
grp.val_min = 0.0;
grp.val_max = 2.0;
grp.samples = wave;
for (int i = 0; i < grp.num_sample; i++) {
	grp.samples[i] = 0.8*sin(0.02*(double)i) + 1.0;
}
///debug///

//コンストラクト
	//UIライブラリ
	UILib ui;

//変数宣言
	Frame *test[100];

//メインルーチン
	ui.init();

	std::cout << "OpenGL ver. " << glGetString(GL_VERSION) << std::endl;

	//フレームレート設定
	ui.win.fps.SetFPS(30);

	//フレーム追加
	test[0] = ui.window.add<Frame>();
	test[1] = ui.window.add<Graph>();
	((Graph*)test[1])->grp = grp;
	((Graph*)test[1])->fill_wave = 1;

	ui.window.orderliness();

	ui.loop();
	ui.exit();
	return 0;
}