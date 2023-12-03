#pragma once
#include "Scene_Base.h"
#include "Vector2.h"
// タイトルシーンのクラス
class TiteleScene : public Scene_Base 
{
public:
	// 初期処理
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;

	// 終了処理
	void Exit()override;

public:
	int background_image; // 背景画像用の
	Vector2 image_pos;    // 画像用の描画座標
	int count_flame; // フレームカウント用の変数 
	int count_time;  // フレームから実際の割り出して入れる用の時間

};
