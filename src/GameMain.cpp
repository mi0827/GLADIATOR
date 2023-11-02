#include "WinMain.h"
#include "GameMain.h"
#include "Vector3.h"
#include "Hit.h" // あたり判定

// キャラクター.h
#include "Player.h"
#include "Player2.h"
// フィールド.h
#include "Field.h"

// カメラ.h
#include "Camera.h"

// オブジェクトクラス
#include "Object.h"

// 各クラスのオブジェクト
Player player;
Player2 player2;
Field field;
Camera camera;

// オブジェクトの数
const int OBJECT_MAX = 1;

// オブジェクトクラス型のポインタはいてる　
Object* object[OBJECT_MAX];

// オブジェクトの描画位置を微妙にずらすための配列変数
float z_pos[OBJECT_MAX];



// 初期処理(各クラスのコンストラクタできないもの)
void GameInit()
{
	// 各クラスの初期設定
	field.Init();
	player.Init();
	player2.Init();

	// どれだけずらすかの設定
	for (int i = 0; i < OBJECT_MAX; ++i) {
		z_pos[i] = i * 20.0f;
	}

	// オブジェクトの初期化
	for (int i = 0; i < OBJECT_MAX; ++i) {
		// ここでNEWする
		object[i] = new Object;
		// さっき作った z_pos 分ずれるように引数にアドレスを渡す
		object[i]->Init(&z_pos[i]);
	}
}

// 更新処理
void GameUpdate()
{
	player.Update(&camera.m_rot);
	if (CheckBoxHit3D(player.m_pos, player.m_move_hit_box_size, object[0]->m_cube_hit_pos, object[0]->m_cube_size_half))
	{
		player.m_move_judge = true; // 移動に支障があるのでtrueを返す
		player.Get_other(&object[0]->m_cube_hit_pos, &object[0]->m_cube_size_half); // Playerに当たった相手の情報を渡する
	}
	else {
		player.m_move_judge = false;
	}

	// 各クラスの更新処理
	player.move2(&camera.m_rot);
	player2.Update(&camera.m_rot);
	field.Update();
	camera.Update(&player.m_pos);
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Update();
	}

	// ここであたり判定をする

	// 立方体同士の当たり判定( TRUE:当たっている FALSE:当たっていない )

	

	

	// 弾とカプセルの当たり判定(今はカプセルがない)
	//if (player.bead_pos != NULL) {
	//	if (HitCheck_Sphere_Capsule(player.bead_pos->VGet(), 2, VGet(50.0f, 10.0f, 0.0f), VGet(50.0f, 100.0f, 0.0f), 40.0f)) {
	//		player.bead_hit_judg = true; // 当たった
	//	}
	//	else {
	//		player.bead_hit_judg = false; // 当たってない
	//	}
	//}
}

// 描画処理
void GameDraw()
{
	// 各クラスの描画処理
	field.Draw();
	player.Draw();
	player2.Draw();
	camera.Draw();
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Draw();
	}
}

// 終了処理
void GameExit()
{
	// 各クラスの終了処理
	player.Exit();
	player2.Exit();
	field.Exit();
	camera.Exit();

	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Exit();
	}

	// 初期処理で new したので
	// ここで解放しておく
	for (int i = 0; i < OBJECT_MAX; ++i) {
		delete object[i];
	}
}
