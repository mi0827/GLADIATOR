#pragma once

class EndScene : public Scene_Base
{
public:
	// 初期処理
	void Init()override;

	// 更新処理
	void Update(int bgm_volume, int se_volume)override;

	// 描画処理
	void Draw()override;

	// 終了処理
	void Exit()override;

	// BGMの初期処理
	void BGM_Init();

public:
	int background_image; // 背景画像用の
	Vector2 image_pos;    // 画像用の描画座標

	int count_flame; // フレームカウント用の変数 
	int count_time;  // フレームから実際の割り出して入れる用の時間

	// フォントデータ用
	int GTA_font_data; // GTAのフォントデータ用の変数
	LPCSTR GTA_font_path;


	enum BGM
	{

		BGM_1, // 一つ目のbgm

		BGM_MAX // bgmの最大数
	};
};