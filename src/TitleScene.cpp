#include "WinMain.h"
#include "Vector2.h"
#include "Scene_Base.h"
#include "TitleScene.h"

const int Title_Time_MAX = 5;  // タイトル描画時間(今だけ3秒)

//------------------------------------------
// 初期処理
//------------------------------------------
void TiteleScene::Init()
{
	background_image = LoadGraph("Data/Background/Title.jpg"); // 画像の用見込み
	image_pos.set(0.0f, 0.0f); // 描画座標の設定

	// カウント類は最初はマックススタート
	count_flame = FLAME_MAX;
	count_time = Title_Time_MAX;

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
void TiteleScene::Update()
{
	switch (title_scene)
	{
	case TITLE:

		// ゲームパッドの情報を丸ごと取得
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
			// Aボタンを押されたら次のシーンに移動
			start_flag = true;
		}
		else if (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A) {
			// Aボタンを押されたら次のシーンに移動
			start_flag = true;
		}
		else
		{
			// ボタンが押されていないときはフラグを下げる
			start_flag = false;
		}


		// スタートフラグがたっていたら次のシーンに進む
		if (start_flag) {
			scene_change_judge = true; // シーンの切り替えを許可する
		}
		else {
			// フラグが下がっていたら
			count_flame--; // フレームのカウントを減らす
			if (count_flame <= 0) { // フレームが設定された値以上になったら
				count_flame = FLAME_MAX; // フレームカウントをリセット
				count_time--;    // タイムカウントを進める
			}
			if (count_time <= 0) // タイトル画面で一定時間止まっていたら
			{
				title_scene = MOVIE; // 動画のシーンの切り替える
			}
		}

		break;

	case MOVIE:

		// ゲームパッドの情報を丸ごと取得
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
			// Aボタンを押されたらタイトル描画に戻る
			title_scene = TITLE;
		}
		// ゲームパッドの情報を丸ごと取得
		if (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A) {
			// Aボタンを押されたらタイトル描画に戻る
			title_scene = TITLE;
		}

		break;

	}
}

//------------------------------------------
// 描画処理
//------------------------------------------
void TiteleScene::Draw()
{

	// 背景画像の描画
	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	// ここでとってきた文字をセットしておく
	// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
	int original_font_size = GetFontSize();


	switch (title_scene)
	{
	case TITLE:
	{
		SetFontSize(120); // フォントサイズの変更
		const char* name = "GLADIATOR";
		// 描画幅の取得
		float w = GetDrawStringWidth(name, -1);
		// 文字列の高さ取得
		float h = GetFontSize();
		// 描画
		//DrawStringFToHandle(SCREEN_W / 2 - w -80, SCREEN_H / 2 +5, name, GetColor(128, 0, 0), GTA_font_data, TRUE); 
		//DrawStringFToHandle(SCREEN_W / 2 - w - 85, SCREEN_H / 2 , name, GetColor(255, 0, 0), GTA_font_data, TRUE); 
		int taile_h = -50;
		DrawString(SCREEN_W / 2 - w / 2 + 7, SCREEN_H / 2 + taile_h + 7, name, GetColor(128, 0, 0)); // 下
		DrawString(SCREEN_W / 2 - w / 2, SCREEN_H / 2 + taile_h, name, GetColor(255, 0, 0)); // 上
		

	}
	break;

	case MOVIE:

	{
		SetFontSize(120); // フォントサイズの変更
		const char* name = "ほんとは動6画を乗せる予定";
		// 描画幅の取得
		float w = GetDrawStringWidth(name, -1);
		// 文字列の高さ取得
		float h = GetFontSize();
		// 描画
		//DrawStringFToHandle(SCREEN_W / 2 - w -80, SCREEN_H / 2 +5, name, GetColor(128, 0, 0), GTA_font_data, TRUE); 
		//DrawStringFToHandle(SCREEN_W / 2 - w - 85, SCREEN_H / 2 , name, GetColor(255, 0, 0), GTA_font_data, TRUE); 
		int taile_h = -50;
		DrawString(SCREEN_W / 2 - w / 2 + 7, SCREEN_H / 2 + taile_h + 7, name, GetColor(128, 0, 0)); // 下
		DrawString(SCREEN_W / 2 - w / 2, SCREEN_H / 2 + taile_h, name, GetColor(255, 0, 0)); // 上
		

	}
	break;
	}


	SetFontSize(50); // フォントサイズの変更


	//DrawFormatString(16 + 7, 16 + 7, GetColor(0, 128, 128), "START:%02d", count_time); // 下
	//DrawFormatString(16, 16, GetColor(0, 255, 255), "START:%02d", count_time); // 上
	DrawString(16 + 5, 16 + 5, "START: A ", GetColor(0, 128, 128)); // 下
	DrawString(16, 16, "START: A ", GetColor(0, 255, 255)); // 上
	SetFontSize(original_font_size); // フォントサイズを

}



//------------------------------------------
// 終了処理
//------------------------------------------
void TiteleScene::Exit()
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
