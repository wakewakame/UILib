/*
---参考サイト---
http://qiita.com/edo_m18/items/95483cabf50494f53bb5
http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20040914

---メモ---
点線で区切られた部分ごとにコピペしたものが分かれてる
どれが必要でどれがいらないものなのかわからない為、とっかえひっかえしたりして確かめる
*/

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "define.h"

class FBOtest {
public:
//変数宣言
	/*---------------------------------------------------------------------------------------------------*/
	GLuint color_render_buffer;
	GLuint depth_render_buffer;
	GLuint frame_buffer;
	/*---------------------------------------------------------------------------------------------------*/
	GLuint texture;
	/*---------------------------------------------------------------------------------------------------*/
	WindowPoint size;
	/*---------------------------------------------------------------------------------------------------*/

//関数宣言
	//初期化
	void init(WindowPoint set_size) {
		size = set_size;
		/*---------------------------------------------------------------------------------------------------*/
		// カラーバッファ用レンダーバッファを生成（Generate）
		glGenRenderbuffers(1, &color_render_buffer);
		glBindRenderbuffer(GL_RENDERBUFFER, color_render_buffer);

		// デプスバッファ用レンダーバッファを生成
		glGenRenderbuffers(1, &depth_render_buffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depth_render_buffer);

		// フレームバッファを生成
		glGenFramebuffers(1, &frame_buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

		// フレームバッファにレンダーバッファを、カラーバッファとしてアタッチ
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color_render_buffer);

		// フレームバッファにレンダーバッファを、デプスバッファとしてアタッチ
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_render_buffer);
		/*---------------------------------------------------------------------------------------------------*/
		/*
		// テクスチャを生成
		glGenTextures(GL_TEXTURE_2D, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// フレームバッファのカラーバッファとしてテクスチャを設定
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		*/
		/*---------------------------------------------------------------------------------------------------*/
		//ウィンドウ全体をビューポートにする
		glViewport(0, 0, size.x, size.y);

		//変換行列の初期化
		glLoadIdentity();

		//スクリーン上の表示領域をビューポートの大きさに比例させる
		glOrtho(0.0, (double)size.x, (double)size.y, 0.0, -1.0, 1.0);
		/*---------------------------------------------------------------------------------------------------*/
		//レンダー先をウィンドウに切り替え
		changeWindow();
		/*---------------------------------------------------------------------------------------------------*/
	}

	//レンダー先をフレームバッファに切り替え
	void changeFBO(){
		glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
	}

	//レンダー先をウィンドウに切り替え
	void changeWindow(){
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	//フレームバッファを描画
	void DrawFBO() {
		/* テクスチャマッピング開始 */
		glEnable(GL_TEXTURE_2D);

		/* １枚の４角形を描く */
		glNormal3d(0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3d(-1.0, -1.0, 0.0);
		glTexCoord2d(1.0, 1.0);
		glVertex3d(1.0, -1.0, 0.0);
		glTexCoord2d(1.0, 0.0);
		glVertex3d(1.0, 1.0, 0.0);
		glTexCoord2d(0.0, 0.0);
		glVertex3d(-1.0, 1.0, 0.0);
		glEnd();

		/* テクスチャマッピング終了 */
		glDisable(GL_TEXTURE_2D);
	}
};