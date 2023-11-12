#include "WinMain.h"
#include "GameMain.h"
#include "Vector3.h"
#include "Hit.h" // あたり判定

// キャラクター.h
#include "Player.h"
#include "Ninja.h"
// フィールド.h
#include "Field.h"

// カメラ.h
#include "Camera.h"

// オブジェクトクラス
#include "Object.h"

constexpr int PLAYER_MAX = 2; // プレイヤーの数、カメラの数も一緒

// 各クラスのオブジェクト

CharacterBase* players[2]; // キャラクターの二人呼ぶ用の配列 
Camera* camera[2];         // キャラクタと同じ数

Field field;

// 初期処理(各クラスのコンストラクタできないもの)
void GameInit()
{
	players[0] = new Player;
	players[1] = new Ninja;
	camera[0] = new Camera;
	camera[1] = new Camera;
	// 各クラスの初期設定
	field.Init();
	field.Field_Init();
	players[0]->Init(0);
	players[1]->Init(1);

	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->PlayField_Init();
	}

}

// 更新処理
void GameUpdate()
{
	// キャラクターの移動（壁擦り）処理
	for (int player = 0; player < PLAYER_MAX; player++) {
		players[player]->Update(&camera[player]->m_rot);
		// 立方体とプレイヤーのあたり判定
		for (int i = 0; i < field.obj_max; i++) {
			if (CheckBoxHit3D(players[player]->m_pos, players[player]->m_move_hit_box_size, field.objects[i]->m_cube_hit_pos, field.objects[i]->m_cube_size_half))
			{
				players[player]->m_move_judge = true; // 移動に支障があるのTureを返す
				players[player]->Get_other(&field.objects[i]->m_cube_hit_pos, &field.objects[i]->m_cube_size_half); // Playerに当たった相手の情報を渡する
				players[player]->Move_Hit_Update(); // 壁擦り用の関数
			}
			else {
				players[player]->m_move_judge = false;
			}
		}
	}
	// プレイヤーとプレイヤーの移動あたり判定
	for (int i = 0; i < field.obj_max; i++) {
		if (CheckBoxHit3D(players[0]->m_pos, players[0]->m_move_hit_box_size, players[1]->m_pos, players[1]->m_move_hit_box_size))
		{
			players[0]->m_move_judge = true; // 移動に支障があるのTureを返す
			players[0]->Get_other(&players[1]->m_pos, &players[1]->m_move_hit_box_size); // Playerに当たった相手の情報を渡する
			players[0]->Move_Hit_Update(); // 壁擦り用の関数
		}
		else {
			players[0]->m_move_judge = false;
		}
	}

	// 各クラスの更新処理
	field.Update();	
	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		camera[i]->Update(&players[i]->m_pos);
	}
}

// 描画処理
void GameDraw()
{
	// 各クラスの描画処理
	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->Draw_Set();       // カメラの描画前設定（ ※ 描画処理の一番最初にすること）
		field.Draw();
		// プレイヤ―を用がさせるための配列
		for (int j = 0; j < PLAYER_MAX; j++) {
			players[j]->Draw();
		}
		camera[i]->Draw(i); // カメラの描画処理（ ※ 描画処理の一番最後にすること）
	}
}

// 終了処理
void GameExit()
{
	// 各クラスの終了処理
	for (int i = 0; i < PLAYER_MAX; i++) {
		players[i]->Exit();
		camera[i]->Exit();
	}
	field.Exit();
	// newしていたクラスの解放
	delete[] players;
	delete[] camera;
}
