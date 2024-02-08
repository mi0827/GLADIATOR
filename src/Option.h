#pragma once

class Option
{
public:
	// コンストラクタ
	Option();
	// デストラクタ
	~Option();
	// 初期処理
	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

public:
	int BGM_Volume = 0; // BGMの音量
	int SE_Volume = 0;  // SEの音量
	bool option_flag = false;    // オプションメニューを開くためのもの

private:
	Vector2 option_box_pos = { 0.0f,0.0f }; // オプションメニュー画面の四角座標
	Vector2 BGM_box_pos = { 0.0f,0.0f };    // BGMバーの座標
	Vector2 SE_box_pos = { 0.0f,0.0f };     // SEバーの座標

	int image_box = 0; // 背景画像用の入れ物
	int menu_count = 0; // メニューボタンが押されてから閉じるまでにかかる最低時間をカウントするための物
	int select = 0; // SEかBGMを洗濯するためのもの
};