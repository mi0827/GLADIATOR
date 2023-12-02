#include "EndScene.h"
#include "WinMain.h"


//------------------------------------------
// 初期処理
//------------------------------------------
void EndScene::Init()
{
	background_image = LoadGraph("Data/baclground/End.jpg"); // 背景画像の読み込み
	image_pos.set(0.0f, 0.0f); // 描画座標の設定

	// カウント類は最初は０スタート
	count_flame = 0;
	count_time = 0;

	scene_change_judge = false; // 最初はシーンの切り替えをしてはいけない
}

//------------------------------------------
// 更新処理
//------------------------------------------
void EndScene::Update()
{
	count_flame++; // フレームのカウントを進める
	if (count_flame >= Flame_MAX) { // フレームが設定された値以上になったら
		count_flame = 0; // フレームカウントをリセット
		count_time++;    // タイムカウントを進める
	}
	//Flame_Time_Update(&count_flame, &count_time);
	if (count_time >= 10) // タイトル画面で10秒経ったら
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
	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	DrawFormatString(16, 16, GetColor(0, 0, 0), "time:%2d", count_time);
}

//------------------------------------------
// 終了処理
//------------------------------------------
void EndScene::Exit()
{
	DeleteGraph(background_image); // 画像データの解放
}
