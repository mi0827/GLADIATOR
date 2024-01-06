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
	int BGM_Volume; // BGMの音量
	int SE_Volume;  // SEの音量
	bool option_flag;    // オプションメニューを開くためのもの

private:
	Vector2 option_box_pos; // オプションメニュー画面の四角座標
	Vector2 BGM_box_pos;    // BGMバーの座標
	Vector2 SE_box_pos;     // SEバーの座標

	int image_box; // 背景画像用の入れ物
	int menu_count; // メニューボタンが押されてから閉じるまでにかかる最低時間をカウントするための物

};