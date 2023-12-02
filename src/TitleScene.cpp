#include "WinMain.h"

#include "TitleScene.h"

//------------------------------------------
// 初期処理
//------------------------------------------
void TiteleScene::Init()
{
	background_image = LoadGraph("Data/Baclground/Title.jpg"); // 画像の用見込み
	image_pos.set(0.0f, 0.0f); // 描画座標の設定

	// カウント類は最初は０スタート
	count_flame = 0;
	count_time = 0;

	scene_change_judge = false; // 最初はシーンの切り替えをしてはいけない
}

//------------------------------------------
// 更新処理
//------------------------------------------
void TiteleScene::Update()
{
	Flame_Time_Update(&count_flame, &count_time);
	if (count_time >= 10) // タイトル画面で10秒経ったら
	{
		scene_change_judge = true; // シーンの切り替えを許可する
	}
	
	
}

//------------------------------------------
// 描画処理
//------------------------------------------
void TiteleScene::Draw()
{
	// 背景画像の描画
	DrawGraph(image_pos.x, image_pos.y, background_image, TRUE);
	DrawFormatString(16, 16, GetColor(0, 0, 0), "time:%2d", count_time);
}

//------------------------------------------
// 終了処理
//------------------------------------------
void TiteleScene::Exit()
{
	DeleteGraph(background_image); // 画像データの解放
}
