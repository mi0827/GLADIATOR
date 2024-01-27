#pragma once
#include "Scene_Base.h"
#include "Vector2.h"
// タイトルシーンのクラス
class TiteleScene : public Scene_Base
{
	//int effeckt_h;
public:
	// 初期処理
	void Init()override;

	// 更新処理
	void Update(int bgm_volume, int se_volume)override;

	// 描画処理
	void Draw()override;

	// 終了処理
	void Exit()override;

public:
	int background_image; // 背景画像用の
	Vector2 image_pos;    // 画像用の描画座標
	int count_flame; // フレームカウント用の変数 
	int count_time;  // フレームから実際の割り出して入れる用の時間
	int movie;       // 動画用のへんすう

	// フォントデータ用
	int GTA_font_data; // GTAのフォントデータ用の変数
	LPCSTR GTA_font_path;

	enum Title_se
	{
		DECISION, // タイトル画面で指定のボタンを押された時

		SE_MAX,   // SEの最大数
	};

	enum BGM
	{
		TITLE_BGM,  // タイトル画面で流すBGM

		BGM_MAX // BGMの最大数
	};

private:

	// タイトル画面での切り替え用
	enum Title_SCENES
	{
		TITLE, // タイトル画面
		MOVIE, // 動画画面
	};

	// 画面切り替え用の変数
	int title_scene = 0;

	bool start_flag = false; // タイトル画面でボタンが押されたかどうかのフラグ

};
