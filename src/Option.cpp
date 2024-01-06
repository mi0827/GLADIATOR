#include "WinMain.h"
#include "Vector2.h"
#include "Option.h"

// サウンドの音の範囲
constexpr int Volume_MAX = 255; // 最大
constexpr int Volume_LEAST = 0; // 最小

constexpr int MENU_COUNT = 10; // メニューボタンが押されてから閉じるまでにかかる最低時間

constexpr int BOX_SIZE = 300;               // 四角の背景のサイズ
constexpr int BOX_SIZE_HARF = BOX_SIZE / 2; // 背景の半分のサイズ

constexpr int BAR_SIZE = 20;                // バーのX座標のサイズ
constexpr int BAR_SPACE_X= BOX_SIZE_HARF / 2;// 中心からどれくらい隙間を開けるかの値(X座標)
constexpr int BAR_Y = Volume_MAX / 2;// 中心からどれくらい隙間を開けるかの値(Y座標)



Option::Option()
{
	menu_count = 0; // ０からスタート

	// 座標設定
	option_box_pos.set(SCREEN_W / 2 - BOX_SIZE_HARF, SCREEN_H / 2 - BOX_SIZE_HARF); // 背景
	BGM_box_pos.set(SCREEN_W / 2 - BAR_SPACE_X, SCREEN_H / 2 + BAR_Y);
	option_flag = false; // 最初はオプションメニューは閉じている
	BGM_Volume = 255;
	SE_Volume = 255;
}

Option::~Option()
{
}

//----------------------------------------------
// 初期処理
//----------------------------------------------
void Option::Init()
{
	image_box = LoadGraph("Data/Option/OptionMenu.png");
}

//----------------------------------------------
// オプションの更新処理
//----------------------------------------------
void Option::Update()
{

	// オプションメニューを開くとき
    // ボタンを押されたら
	if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO1))
	{
		// オプションメニューを開く
		option_flag = true;
	}
	// オプションメニューが開いているとき
	if (option_flag) {
		menu_count++; // カウントを増やす

		if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1)) {
			BGM_Volume-= 10;
		}


		
	}

	// カウントが一定以上になったら
	if (menu_count >= MENU_COUNT) {
		// オプションメニューが開いていて
		// なおボタンが押されたら
		if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO1))
		{
			// オプションメニューを閉じる
			option_flag = false;
			// カウントをリセット
			menu_count = 0;
		}
	}
}

//----------------------------------------------
// オプションの描画処理
//----------------------------------------------
void Option::Draw()
{
	// オプションメニューが開いている時だけ
	// 描画する
	if (option_flag) {
		DrawExtendGraph(option_box_pos.x, option_box_pos.y, option_box_pos.x + BOX_SIZE, option_box_pos.y + BOX_SIZE, image_box, TRUE);
		DrawBox(BGM_box_pos.x, BGM_box_pos.y, BGM_box_pos.x + BAR_SIZE, BGM_box_pos.y - BGM_Volume, GetColor(255, 255, 255),true);
	
	}

}
