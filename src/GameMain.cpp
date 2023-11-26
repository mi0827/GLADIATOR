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
	players[1] = new Player;
	// プレイヤー０にカメラ０をつける
	// プレイヤー１にカメラ１をつける
	camera[0] = new Camera;
	camera[1] = new Camera;
	// 各クラスの初期設定
	field.Init();
	field.Field_Init();
	players[0]->Init(0);
	players[1]->Init(1);
	// ゲームパッドの設定
	players[0]->SetPadNo(DX_INPUT_PAD1);
	players[1]->SetPadNo(DX_INPUT_PAD2);


	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->PlayField_Init();
	}
	// ゲームパッドの設定
	camera[0]->SetPadNo(DX_INPUT_PAD1);
	camera[1]->SetPadNo(DX_INPUT_PAD2);
}

// 更新処理
void GameUpdate()
{

	Move_Hit(); // キャラクターの移動時のあたり判定実行用


	// 各クラスの更新処理
	field.Update();
	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		camera[i]->Update(&players[i]->m_pos);
	}

	for (int i = 0; i < PLAYER_MAX; i++) {
		int player1 = i;
		int player2 = 0;
		if (player1 == 0) {
			player2 = 1;
		}
		else {
			player2 = 0;
		}


		if (players[player1]->block_flag && !players[player1]->attack_flag) {
			Block_Hit(player1, player2);
		}

		if (players[player1]->attack_flag && !players[player1]->block_flag) {  // 攻撃
			Attack_Hit(player1, player2); // 当たり判定を見る関数
		}

	}
}

// 描画処理
void GameDraw()
{
	// 各クラスの描画処理
	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->Draw_Set();       // カメラの描画前設定（ ※ 描画処理の一番最初にすること）
		field.Draw();

		// プレイヤ―を描画させるための配列
		for (int j = 0; j < PLAYER_MAX; j++) {
			players[j]->Draw();
		}
		players[i]->Draw_Status();
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
	for (int i = 0; i < PLAYER_MAX; i++) {
		delete players[i];
		players[i] = nullptr;
		delete camera[i];
		camera[i] = nullptr;
	}

}


//---------------------------------------------------------------------------
// キャラクターの移動あたり判定実行用関数
//---------------------------------------------------------------------------
void Move_Hit()
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
	if (CheckBoxHit3D(players[0]->m_pos, players[0]->m_move_hit_box_size, players[1]->m_pos, players[1]->m_move_hit_box_size))
	{
		players[0]->m_move_judge = true; // 移動に支障があるのTureを返す
		players[0]->Get_other(&players[1]->m_pos, &players[1]->m_move_hit_box_size); // Playerに当たった相手の情報を渡する
		players[0]->Move_Hit_Update(); // 壁擦り用の関数
	}
	else {
		players[0]->m_move_judge = false;
	}
	// プレイヤーとプレイヤーの移動あたり判定
	if (CheckBoxHit3D(players[1]->m_pos, players[1]->m_move_hit_box_size, players[0]->m_pos, players[0]->m_move_hit_box_size))
	{
		players[1]->m_move_judge = true; // 移動に支障があるのTureを返す
		players[1]->Get_other(&players[0]->m_pos, &players[0]->m_move_hit_box_size); // Playerに当たった相手の情報を渡する
		players[1]->Move_Hit_Update(); // 壁擦り用の関数
	}
	else {
		players[0]->m_move_judge = false;
	}

}

//---------------------------------------------------------------------------
// 攻撃のあたり判定をとる関数
//---------------------------------------------------------------------------
void Attack_Hit(int player1, int player2)
{
	// 当たり判定を取っていいときに当たっていたらダメージを入れる
	// (当たり判定と攻撃フラグがたっていたら)
	if (players[player1]->cd_hit_flag && players[player1]->attack_flag) {
		if (HitCheck_Capsule_Capsule(players[player1]->m_hit_cd_pos_top.VGet(), players[player1]->m_hit_cd_pos_under.VGet(), players[player1]->m_hit_cd_r,
			players[player2]->m_hit_body_pos_top.VGet(), players[player2]->m_hit_body_pos_under.VGet(), players[player2]->m_hit_body_r))
		{
			players[player2]->m_hp_count.x -= players[player1]->m_attack_damage[players[player1]->attack_anim_pick]; // ダメージを入れる
			players[player2]->damage_flag = true;

		}
	}
}

//---------------------------------------------------------------------------
// ガードのあたり判定をとる関数
//---------------------------------------------------------------------------
void Block_Hit(int player1, int player2)
{
	// 当たり判定を取っていいときに当たっていたらダメージを入れる
	// プレイヤー０の攻撃判定とプレイヤー1のガードの判定
	if (players[player1]->cd_hit_flag && players[player1]->block_flag) {
		if (HitCheck_Capsule_Capsule(players[player1]->m_block_top.VGet(), players[player1]->m_block_under.VGet(), players[player1]->m_block_r,
			players[player2]->m_hit_cd_pos_top.VGet(), players[player2]->m_hit_cd_pos_top.VGet(), players[player2]->m_hit_cd_r))
		{

		}
		// 当たり判定がガードのじゃなくボディーだった時 
		else if (HitCheck_Capsule_Capsule(players[player1]->m_hit_body_pos_top.VGet(), players[player1]->m_hit_body_pos_under.VGet(), players[player1]->m_hit_body_r,
			players[player2]->m_hit_cd_pos_top.VGet(), players[player2]->m_hit_cd_pos_top.VGet(), players[player2]->m_hit_cd_r))
		{
			players[player1]->m_hp_count.x -= players[player2]->m_attack_damage[players[player2]->attack_anim_pick]; // ダメージを入れる
			players[player1]->damage_flag = true;
		}
	}
}

//---------------------------------------------------------------------------
// キャラクターのステータス描画処理
//---------------------------------------------------------------------------
void Draw_Status()
{
	DrawBox(players[0]->m_hp_pos.x, players[0]->m_hp_pos.y, players[0]->m_hp_count.x, players[0]->m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(players[0]->m_hp_pos.x, players[0]->m_hp_pos.y, HP_MAX, players[0]->m_hp_count.y, GetColor(255, 255, 255));

	DrawBox(SCREEN_W / 2 + players[1]->m_hp_pos.x, players[1]->m_hp_pos.y, SCREEN_W / 2 + players[1]->m_hp_count.x, players[1]->m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(SCREEN_W / 2 + players[1]->m_hp_pos.x, players[1]->m_hp_pos.y, SCREEN_W / 2 + HP_MAX, players[1]->m_hp_count.y, GetColor(255, 255, 255));
}