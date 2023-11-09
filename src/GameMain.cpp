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

CharacterBase* player_objec[2];

Player player;
Player2 player2;
Field field;
Camera camera;
Camera camera_2;

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
	field.Field_Init();
	player.Init();
	player2.Init();

	camera.PlayField_Init();
	camera_2.PlayField_Init();



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
	// 立方体とプレイヤーのあたり判定
	if (CheckBoxHit3D(player.m_pos, player.m_move_hit_box_size, object[0]->m_cube_hit_pos, object[0]->m_cube_size_half))
	{
		player.m_move_judge = true; // 移動に支障があるのでtrueを返す
		player.Get_other(&object[0]->m_cube_hit_pos, &object[0]->m_cube_size_half); // Playerに当たった相手の情報を渡する
		player.Move_Hit_Update(); // 壁擦り用の関数
	}
	else {
		player.m_move_judge = false;
	}
	

	// 各クラスの更新処理
	player2.Update(&camera.m_rot);
	field.Update();
	camera.Update(&player.m_pos);
	camera_2.Update(&player2.m_pos);
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Update();
	}
}

// 描画処理
void GameDraw()
{
	// 各クラスの描画処理
	camera.Draw_Set(); // カメラの描画前設定（ ※ 描画処理の一番最初にすること）
	field.Draw();
	player.Draw();
	player2.Draw();
	
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Draw();
	}
	camera.Draw(0); // カメラの描画処理（ ※ 描画処理の一番最後にすること）


	camera_2.Draw_Set();
	field.Draw();
	player.Draw();
	player2.Draw();
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Draw();
	}

	camera_2.Draw(1);
}

// 終了処理
void GameExit()
{
	// 各クラスの終了処理
	player.Exit();
	player2.Exit();
	field.Exit();
	camera.Exit();

	

	// 初期処理で new したので
	// ここで解放しておく
	for (int i = 0; i < OBJECT_MAX; ++i) {
		delete object[i];
	}
}
