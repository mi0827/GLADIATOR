#include "WinMain.h"
#include "Vector2.h"
#include "BGM.h"
#include "SE.h"
#include "Scene_Base.h"
#include "TitleScene.h"

const int Title_Time_MAX = 5;  // タイトル描画時間(今だけ3秒)
BGM title_bgm; // BGMクラスのオブジェクト
SE title_se; // SEクラスのオブジェクト

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

	// BGMの配列の確保
	title_bgm.BGM_ContainerNew(BGM_MAX);
	// BGMの読み込み
	title_bgm.Load_BGM("Data/BGM/Title/Title.mp3", TITLE_BGM);
	// BGMの再生
	title_bgm.Play_BGM(DX_PLAYTYPE_BACK, true, TITLE_BGM);
	// SE用の配列の用意
	title_se.SE_ContainerNew(SE_MAX);
	// SEの読み込み
	title_se.Load_SE("Data/SE/Title/Title_start.mp3", DECISION);

}

//------------------------------------------
// 更新処理
//------------------------------------------
void TiteleScene::Update(int bgm_volume, int se_volume)
{

	title_bgm.BGM_ChangeVolume(bgm_volume, BGM_MAX); // BGMのボリューム変更処理
	title_se.SE_ChangeVolume(se_volume, SE_MAX);     // SEのボリューム変更処理
	switch (title_scene)
	{
	case TITLE:

		// BGMが終わったら
		if (!title_bgm.Playing_BGM(TITLE_BGM)) {
			// BGMの再生
			title_bgm.Play_BGM(DX_PLAYTYPE_LOOP, true, TITLE_BGM);
		}

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

		// キーボードの場合
		if (PushHitKey(KEY_INPUT_A))
		{
			// Aボタンを押されたら次のシーンに移動
			start_flag = true;
		}


		// スタートフラグがたっていたらSEの再生
		if (start_flag) {
			title_se.Play_SE(DECISION, DX_PLAYTYPE_BACK, TRUE);
		}
		// スタートフラグがたっていたら次のシーンに進む
		if (start_flag && title_se.Playing_SE(DECISION)) {
			scene_change_judge = true; // シーンの切り替えを許可する
			title_bgm.Stop_BGM(TITLE_BGM); // BGMを止める
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

		title_bgm.Stop_BGM(TITLE_BGM); // BGMを止める

		// プレイ動画の再生
		movie = PlayMovie("Data/Movie/02.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		GetMovieStateToGraph(movie);
		// ゲームパッドの情報を丸ごと取得
		if (GetMovieStateToGraph(movie)) {
			// Aボタンを押されたらタイトル描画に戻る
			title_scene = TITLE;
			count_time = Title_Time_MAX;
			PauseMovieToGraph(movie);
		}
		// ゲームパッドの情報を丸ごと取得
		//if (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A) {
		//	// Aボタンを押されたらタイトル描画に戻る
		//	title_scene = TITLE;
		//}

		break;

	}

}

//------------------------------------------
// 描画処理
//------------------------------------------
void TiteleScene::Draw()
{

	// 背景画像の描画
	DrawExtendGraph(image_pos.x, image_pos.y, SCREEN_W, SCREEN_H, background_image, TRUE);
	// ここでとってきた文字をセットしておく
	// 文字の最初の大きさをとっておく
	int original_font_size = GetFontSize();


	

		SetFontSize(200); // フォントサイズの変更
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

	

	SetFontSize(100); // フォントサイズの変更
	//DrawFormatString(16 + 7, 16 + 7, GetColor(0, 128, 128), "START:%02d", count_time); // 下
	//DrawFormatString(16, 16, GetColor(0, 255, 255), "START:%02d", count_time); // 上
	DrawString(16 + 5, 16 + 5, "START: A ", GetColor(0, 128, 128)); // 下
	DrawString(16, 16, "START: A ", GetColor(0, 255, 255)); // 上

	ChangeFont("ＭＳ 明朝", DX_CHARSET_DEFAULT);
	// ゲームパッドの数を調べて足りないかずを描画する

	SetFontSize(50); // フォントサイズの変更
	int joypapd_num = GetJoypadNum();
	DrawFormatString(600, SCREEN_H / 2 + 150, GetColor(255, 0, 0), "ゲームパッドの接続数:%d / 2", joypapd_num);

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
