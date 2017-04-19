#pragma once

#include "windows.h"
#include <vector>
#include <string>

//音色情報
struct VSTParameteres { //パラメーター値構造体
						//音色系
	bool make_auto; //自動で音色を生成するか
	bool use_rawwave; //生波形データの使用をするかどうか
	bool change_natural; //音程変化を自然にするか
	float overtones[512]; //倍音グラフor共鳴スペクトルグラフ
	int iovertones; //倍音の数
					//生波形データ派生
	float rawwave[4096]; //生波形の使用部分波形(ファイルマッピングにするかも(´・ω・｀))
	int nrawwave; //生波形のサンプル数
	float base_pitch; //基音位置(手動変更可)
					  //生成波形
	float outwave[4096]; //出力される波形
	int noutwave; //出力波形のサンプル数
				  //フェード系
	bool use_string_mode; //弦モードの使用をするかどうか
	bool use_fade_change; //なめらかな音程,音量の変化を使用するかどうか(2つ同時に音を出せない)
	float fadein_vol[6];
	float fadein_pitch[6];
	float fadeout_vol[6];
	float fadeout_pitch[6];
	float fadechange_vol[6];
	float fadechange_pitch[6];
	//波形の絶対値の上限
	float wave_limit;
	//基本波形の形
	char wave_type;
	//再生中変更できると便利なパラメーター
	float vol;
	float pitch; //MIDI値に加算
};

//共有メモリ構造体
struct ShareMemData {
	HWND Ready; //GUIクライアントが起動直後にTRUEにする(多重起動回避のため)
	HWND Host; //描画先ハンドル
	VSTParameteres para; //VSTのパラメーター群
};

struct Dimension {
	bool on_limit_min; //パラメータの可動域の最小値が有効かどうか
	bool on_limit_max; //パラメータの可動域の最大値が有効かどうか
	float limit_min; //パラメータの可動域の最小値
	float limit_max; //パラメータの可動域の最大値
	int min_index; //グラフの描画域の最小値パラメータのインデックス
	int max_index; //グラフの描画域の最大値パラメータのインデックス
	std::vector<float> val; //パラメータの値の配列
};

//ユーティリティクラス
class Utility {
public:
	//割合変換関数(戻り値:変換後,引数1~5:変換前の値,変換前の最小値,変換前の最大値,変換後の最小値,変換後の最大値)
	static double Proportion(double i, double i_mix, double i_max, double j_min, double j_max) {
		double j;
		j = j_min + (i - i_mix) * ((j_max - j_min) / (i_max - i_mix));
		return j;
	}
	static float Proportion(float i, float i_mix, float i_max, float j_min, float j_max) {
		float j;
		j = float(Proportion(double(i), double(i_mix), double(i_max), double(j_min), double(j_max)));
		return j;
	}
	static int Proportion(int i, int i_mix, int i_max, int j_min, int j_max) {
		int j;
		j = int(Proportion(double(i), double(i_mix), double(i_max), double(j_min), double(j_max)));
		return j;
	}
	//LPSTR->LPCTSTR(=LPCWSTR)
	static void LPtoLPCW(LPSTR str, wchar_t wlocal[300]) {
		MultiByteToWideChar(
			CP_ACP,
			MB_PRECOMPOSED,
			str,
			strlen(str),
			wlocal,
			strlen(str) + 1
		);
	}
};

//グラフ上の座標
struct GraphPos {
	int x;
	float y;
};

//ウィンドウ上の座標
struct WindowPoint {
	double x;
	double y;
};

//ウィンドウ上のサイズ
struct WindowRect {
	double left;
	double top;
	double right;
	double bottom;
};

//グラフのプロパティ
class graph {
public:
	float *samples; //波形本体
	int num_sample; //波形のサンプル数
	int start_index; //描画領域の始めの波形のサンプルのインデックス
	int end_index; //描画領域の終わりの波形のサンプルのインデックス
	float zero_index_val; //波形のサンプルが0の地点のグラフ上の単位のx座標
	float last_index_val; //波形のサンプルが最終地点のグラフ上の単位のx座標
	float val_min; //描画領域のサンプル値の最小値
	float val_max; //描画領域のサンプル値の最大値
	float val_lim_min; //描画領域のサンプル値の最小値の可動域の最小値
	float val_lim_max; //描画領域のサンプル値の最大値の可動域の最大値
	graph() {
		//変数初期化
		samples = nullptr; //波形本体
		num_sample = 0; //波形のサンプル数
		start_index = 0; //描画領域の始めの波形のサンプルのインデックス
		end_index = 0; //描画領域の終わりの波形のサンプルのインデックス
		zero_index_val = 0.0f; //波形のサンプルが0の地点のグラフ上の単位のx座標
		last_index_val = 1.0f; //波形のサンプルが最終地点のグラフ上の単位のx座標
		val_min = -1.0f; //描画領域のサンプル値の最小値
		val_max = 1.0f; //描画領域のサンプル値の最大値
		val_lim_min = -1.0f; //描画領域のサンプル値の最小値の可動域の最小値
		val_lim_max = 1.0f; //描画領域のサンプル値の最大値の可動域の最大値
	}
};

