#include "WinMain.h"
#include "Vector2.h"
#include "Option.h"

// サウンドの音の範囲
constexpr int Volume_MAX = 255; // 最大
constexpr int Volume_LEAST = 0; // 最小

constexpr int MENU_COUNT = 10; // メニューボタンが押されてから閉じるまでにかかる最低時間

constexpr int BOX_SIZE_X = 280;               // 四角の背景X方向のサイズ
constexpr int BOX_SIZE_Y = 350;               // 四角の背景Y方向のサイズ
constexpr int BOX_SIZE_HARF_X = BOX_SIZE_X / 2; // 背景X方向の半分のサイズ
constexpr int BOX_SIZE_HARF_Y = BOX_SIZE_Y / 2; // 背景Y方向の半分のサイズ

constexpr int BAR_SIZE = 30;                // バーのX座標のサイズ
constexpr int BAR_SPACE_X = BOX_SIZE_HARF_X / 2;// 中心からどれくらい隙間を開けるかの値(X座標)
constexpr int BAR_Y = Volume_MAX / 2;// 中心からどれくらい隙間を開けるかの値(Y座標)



Option::Option()
{
	menu_count = 0; // ０からスタート

	// 座標設定
	option_box_pos.set(SCREEN_W / 2 - BOX_SIZE_HARF_X, SCREEN_H / 2 - BOX_SIZE_HARF_Y); // 背景
	BGM_box_pos.set(SCREEN_W / 2 - BAR_SPACE_X, SCREEN_H / 2 + BAR_Y);
	SE_box_pos.set(SCREEN_W / 2 + BAR_SPACE_X - BAR_SIZE, SCREEN_H / 2 + BAR_Y);
	option_flag = false; // 最初はオプションメニューは閉じている
	BGM_Volume = 100;
	SE_Volume = 255;
	select = 0; // BGMからスタート
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
	if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO2))
	{
		// オプションメニューを開く
		option_flag = true;
	}
	// オプションメニューが開いているとき
	if (option_flag) {
		menu_count++; // カウントを増やす
		// 左右のボタンで変更したい方を選択
		// ０：BGM
		// １：SE
		// 左ボタン
		if (IsPadOn(PAD_ID::PAD_D_DOWN, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_DOWN, PAD_NO::PAD_NO2)) {
			select -= 1;
			if (select < 0) {
				select = 1;
			}
		}
		// 右ボタン
		if (IsPadOn(PAD_ID::PAD_D_RIGHT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_RIGHT, PAD_NO::PAD_NO2)) {
			select += 1;
			if (select >= 2) {
				select = 0;
			}
		}
		if (select == 0) {
			// BGMの音量を下げる
			// 下ボタン
			if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO2)) {
				BGM_Volume -= 10;
			}
			// BGMの音量を上げる
			// 上ボタン
			if (IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO2)) {
				BGM_Volume += 10;
			}
		}
		else {
			// SEの音量を下げる
			// 下ボタン
			if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO2)) {
				SE_Volume -= 10;
			}
			// SEの音量を上げる
			// 上ボタン
			if (IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO2)) {
				SE_Volume += 10;
			}
		}
	}
	// BGMの最低の値で止める
	if (BGM_Volume <= Volume_LEAST) { BGM_Volume = Volume_LEAST; }
	// BGMの最大値で止める
	if (BGM_Volume >= Volume_MAX) { BGM_Volume = Volume_MAX; }
	// SEの最低の値で止める
	if (SE_Volume <= Volume_LEAST) { SE_Volume = Volume_LEAST; }
	// SEの最大値で止める
	if (SE_Volume >= Volume_MAX) { SE_Volume = Volume_MAX; }

	// カウントが一定以上になったら
	if (menu_count >= MENU_COUNT) {
		// オプションメニューが開いていて
		// なおボタンが押されたら
		if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO2))
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
	// ChangeFont("ＭＳ 明朝");
	// オプションメニューが開いている時だけ
	// 描画する
	if (option_flag) {
		DrawExtendGraph(option_box_pos.x, option_box_pos.y, option_box_pos.x + BOX_SIZE_X, option_box_pos.y + BOX_SIZE_Y, image_box, TRUE);  // オプションメニューの背景
		// BGMバーの描画
		DrawBox(BGM_box_pos.x, BGM_box_pos.y, BGM_box_pos.x + BAR_SIZE, BGM_box_pos.y - BGM_Volume, GetColor(0, 0, 0), true);
		DrawLineBox(BGM_box_pos.x, BGM_box_pos.y, BGM_box_pos.x + BAR_SIZE, BGM_box_pos.y - BGM_Volume, GetColor(255, 255, 255));
		int original_font_size = GetFontSize();
		SetFontSize(28); // フォントサイズの変更
		const char* bgm = "BGM";
		Vector2 bgm_pos; // 文字列の座標
		bgm_pos.x = GetDrawStringWidth(bgm, -1);
		bgm_pos.y = GetFontSize();
		DrawFormatStringF(BGM_box_pos.x + BAR_SIZE / 2 - bgm_pos.x / 2, BGM_box_pos.y, GetColor(0, 0, 0), bgm);// 文字列の描画

		// SEバーの描画
		DrawBox(SE_box_pos.x, SE_box_pos.y, SE_box_pos.x + BAR_SIZE, SE_box_pos.y - SE_Volume, GetColor(0, 0, 0), true);
		DrawLineBox(SE_box_pos.x, SE_box_pos.y, SE_box_pos.x + BAR_SIZE, SE_box_pos.y - SE_Volume, GetColor(255, 255, 255));
		const char* se = "SE";
		Vector2 se_pos; // 文字列の座標
		se_pos.x = GetDrawStringWidth(se, -1);
		se_pos.y = GetFontSize();
		DrawFormatStringF(SE_box_pos.x + BAR_SIZE / 2 - se_pos.x / 2, SE_box_pos.y, GetColor(0, 0, 0), se); // 文字列の描画
	
	
		// どちらのバーを選んでいるかわかりやすくするためのもの
		if (select == 0) {
			// BGM側
			DrawLineBox(BGM_box_pos.x, BGM_box_pos.y, BGM_box_pos.x + BAR_SIZE, BGM_box_pos.y - BGM_Volume, GetColor(255, 255, 0));
			DrawFormatStringF(BGM_box_pos.x + BAR_SIZE / 2 - bgm_pos.x / 2 - 2, BGM_box_pos.y - 2, GetColor(255, 255, 0), bgm);
		}
		else {
			// SE側
			DrawLineBox(SE_box_pos.x, SE_box_pos.y, SE_box_pos.x + BAR_SIZE, SE_box_pos.y - SE_Volume, GetColor(225, 255, 0));
			DrawFormatStringF(SE_box_pos.x + BAR_SIZE / 2 - se_pos.x / 2 -2, SE_box_pos.y-2, GetColor(255, 255, 0), se);
		}
		SetFontSize(original_font_size); // フォントサイズを戻す
	}

}
