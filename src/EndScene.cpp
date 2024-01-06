#include "WinMain.h"
#include "Vector2.h"
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
	// 背景画像の描画
	SetFontSize(40); // フォントサイズの変更
	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	DrawFormatString(16, 16, GetColor(0, 0, 0), "リスタートスタート:%2d", count_time);
	SetFontSize(18); // フォントサイズを戻す


	// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
	const char* name = "GLADIATOR";
	// 描画幅の取得
	float w = GetDrawStringWidth(name, -1);
	// 文字列の高さ取得
	float h = GetFontSize();
	SetFontSize(80); // フォントサイズの変更
	// 描画
	DrawStringF(SCREEN_W / 2 - w - 85, SCREEN_H / 2, name, GetColor(0, 0, 0), TRUE);
	SetFontSize(18); // フォントサイズを戻す
}

//------------------------------------------
// 終了処理
//------------------------------------------
void EndScene::Exit()
{
	DeleteGraph(background_image); // 画像データの解放
}
