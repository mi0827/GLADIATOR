#include "WinMain.h"
#include "Vector2.h"
#include "BGM.h"
#include "SE.h"
#include "Scene_Base.h"
#include "EndScene.h"


const int End_Time_MAX = 3;  // エンド描画時間(今だけ3秒)
//------------------------------------------
// 初期処理
//------------------------------------------
void EndScene::Init()
{
	background_image = LoadGraph("Data/background/End.jpg"); // 背景画像の読み込み
	image_pos.set(0.0f, 0.0f); // 描画座標の設定

	// カウント類は最初はマックススタート
	count_flame = FLAME_MAX;
	count_time = End_Time_MAX;

	scene_change_judge = false; // 最初はシーンの切り替えをしてはいけない

	// フォントデータの読み込み
	//GTA_font_data = LoadFontDataToHandle("Data/Font/Gta/GTA.dft", 1.0f);
	GTA_font_path = "Data/Font/Gta/pricedown bl.ttf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(GTA_font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	ChangeFont("Pricedown Bl", DX_CHARSET_DEFAULT);
}

//------------------------------------------
// 更新処理
//------------------------------------------
void EndScene::Update(int bgm_volume, int se_volume)
{
	count_flame--; // フレームのカウントを減らす
	if (count_flame <= 0) { // フレームが設定された値以上になったら
		count_flame = FLAME_MAX; // フレームカウントをリセット
		count_time--;    // タイムカウントを進める
	}
	//Flame_Time_Update(&count_flame, &count_time);
	if (count_time <= 0) // タイトル画面で10秒経ったら
	{
		scene_change_judge = true; // シーンの切り替えを許可する
	}
}

//------------------------------------------
// 描画処理
//------------------------------------------
void EndScene::Draw()
{
	// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
	int original_font_size = GetFontSize();
	// 背景画像の描画

	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	SetFontSize(45); // フォントサイズの変更
	DrawFormatString(16, 16, GetColor(0, 0, 0), "RESTART:%2d", count_time);
	SetFontSize(40); // フォントサイズの変更
	//DrawFormatString(16, 16, GetColor(255, 255, 255), "RESTART:%2d", count_time);
	

	SetFontSize(80); // フォントサイズの変更
	// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
	const char* name = "GLADIATOR";
	// 描画幅の取得
	float w = GetDrawStringWidth(name, -1);
	// 文字列の高さ取得
	float h = GetFontSize();
	// 描画
	DrawStringF(SCREEN_W / 2 - w / 2  - 3, SCREEN_H / 2- 3, name, GetColor(255, 255, 255), TRUE);
	DrawStringF(SCREEN_W / 2 - w / 2, SCREEN_H / 2, name, GetColor(0, 0, 0), TRUE);
	SetFontSize(original_font_size); // フォントサイズを戻す
}

//------------------------------------------
// 終了処理
//------------------------------------------
void EndScene::Exit()
{
	DeleteGraph(background_image); // 画像データの解放
	// ********** フォントのアンロード **********
	if (RemoveFontResourceEx(GTA_font_path, FR_PRIVATE, NULL)) {
	}
	else {
		MessageBox(NULL, "remove failure", "", MB_OK);
	}
	ChangeFont("ＭＳ 明朝", DX_CHARSET_DEFAULT);
}
