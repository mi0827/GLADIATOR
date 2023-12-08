#include "WinMain.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Hit.h" // あたり判定
#include "Base.h"
// キャラクター.h
#include "Character_Base.h"
#include "Player.h"
#include "Ninja.h"
// オブジェクトクラス
#include "Object.h"
// フィールド.h
#include "Field.h"
// カメラ.h
#include "Camera.h"

#include "Scene_Base.h"
#include "GameScene.h"
constexpr int PLAYER_MAX = 2; // プレイヤーの数、カメラの数も一緒

// 各クラスのオブジェクト

CharacterBase* players[2]; // キャラクターの二人呼ぶ用の配列 
Camera* camera[2];         // キャラクタと同じ数

Field field;


constexpr int TIME_MAX = 90;  // 制限時間 (今だけ10秒)
constexpr int END_TIME_MAX = 3; // エンドの時間制限


//------------------------------------------
// ゲーム開始の最初の設定
//------------------------------------------
GameScene::GameScene()
{	

}

//------------------------------------------------
// 初期処理(各クラスのコンストラクタできないもの)
//------------------------------------------------
void GameScene::Init()
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
	players[0]->SetPadNo(PAD_NO::PAD_NO1);//DX_INPUT_PAD1);
	players[1]->SetPadNo(PAD_NO::PAD_NO2);//DX_INPUT_PAD2);

	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->PlayField_Init();
	}
	// ゲームパッドの設定
	camera[0]->SetPadNo(DX_INPUT_PAD1);
	camera[1]->SetPadNo(DX_INPUT_PAD2);

	// 最初はマックス値から始める
	time_count = TIME_MAX;      // タイマーの設定
	flame_count = FLAME_MAX;    // フレームカウントの設定
	end_count = END_TIME_MAX;   // エンドに行くまでのカウントダウン
	scene_change_judge = false; // 最初はシーンの切り替えをしてはいけない
	status_flag = false;        // 最初はステータス更新をしてほしくない
	play_scene = Play_Tutorial; // 最初はチュートリアルシーン

}

//----------------------------------------
// 更新処理
//----------------------------------------
void GameScene::Update()
{

	Character_Update(); // キャラクターたちの更新処理

	// 各クラスの更新処理
	field.Update();
	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		camera[i]->Update(&players[i]->m_pos);
	}

	switch (play_scene)
	{
	case Play_Tutorial:
		status_flag = false;        // ステータス更新をしてほしくない
		Tutorial_Update();
		break;
	case Play_Main:
		status_flag = true;         // ステータス更新をしてほしくない
		PlayMain_Update();
		break;
	case Play_End:
		status_flag = false;        // 最初はステータス更新をしてほしくない
		PlayEnd_Update();
		break;
	};
}

//-------------------------------------
// 描画処理
//-------------------------------------
void GameScene::Draw()
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

	switch (play_scene)
	{
	case Play_Tutorial:
		Tutorial_Draw();          
		break;
	case Play_Main:
		Time_Draw();               // タイマーを描画するのはプレイ中だけ
		break;
	case Play_End:
		End_Draw();
		break;
	};
	
}

//------------------------------------
// 描画処理
//------------------------------------
void GameScene::Exit()
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

//------------------------------------
// チュートリアルの更新処理
//------------------------------------
void GameScene::Tutorial_Update()
{
	// スペースキーを押されたら
	if (CheckHitKey(KEY_INPUT_SPACE)) 
	{
		for (int i = 0; i < PLAYER_MAX; i++) 
		{
			players[i]->Reset_Status(); // ステータスをリセットしておく
		}

		play_scene = Play_Main; // プレイメインに移動
	}
}

//------------------------------------
// メインプレイシーンの更新処理
//------------------------------------
void GameScene::PlayMain_Update()
{
	int player1 = 0;
	int player2 = 1;
	bool is_both_no_guard =	// 両方とも攻撃中
		(
			players[player1]->block_flag == false &&
			players[player2]->block_flag == false
			);
	bool is_player1_guard =	// プレイヤー1がガード中
		(
			players[player1]->block_flag == true &&
			players[player2]->attack_flag == true
			);
	bool is_player2_guard =	// プレイヤー2がガード中
		(
			players[player1]->attack_flag == true &&
			players[player2]->block_flag == true
			);

	// プレイヤー1の攻撃とプレイヤー2の攻撃
	if (is_both_no_guard == true)
	{
		// 通常の当たり判定を行う
		Attack_Hit(player1, player2);
		Attack_Hit(player2, player1);
	}
	// プレイヤー1のガードとプレイヤー2の攻撃
	else if (is_player1_guard == true)
	{
		Block_Hit(player1, player2);
	}
	// プレイヤー1の攻撃とプレイヤー2のガード
	else if (is_player2_guard)
	{
		Block_Hit(player2, player1);
	}

	Time_Update(time_count); // タイマーの更新
	// タイマーが０になったら
	if (time_count == 0) {
		play_scene = Play_End; // プレイエンドに進む
	}
}

//------------------------------------
// プレイエンドの更新処理
//------------------------------------
void GameScene::PlayEnd_Update()
{
	Time_Update(end_count);

	Play_Victory(players[0],players[1]);

	if (end_count <= 0) 
	{
		end_count = 0;
		// タイマーが終わったら
		scene_change_judge = true; // シーンの切り替えを許可する
	}
}

//---------------------------------------------------------------------------
// 勝者を決める関数
//---------------------------------------------------------------------------
void GameScene::Play_Victory(CharacterBase* character1, CharacterBase* character2)
{
	// hpをわかりやすいようにする
	float hp1 = character1->m_now_hp;
	float hp2 = character2->m_now_hp;

	if (hp1 == hp2) {
		// 残りhpが同じなら
	}
	if (hp1 > hp2)
	{
		// hp1のほうが残りhpが多いい場合
	}
	if(hp2 > hp1)
	{
		// hp2のほうが残りhpが多いい場合
	}
}

//---------------------------------------------------------------------------
// キャラクターの更新処理（移動時のお互いのあたり判定）
//---------------------------------------------------------------------------
void GameScene::Character_Update()
{
	// キャラクターの移動（壁擦り）処理
	for (int player = 0; player < PLAYER_MAX; player++) {
		players[player]->Update(&camera[player]->m_rot/*, status_flag*/);
		// 立方体とプレイヤーのあたり判定
		for (int i = 0; i < field.obj_max; i++) {
			if (CheckBoxHit3D(players[player]->m_pos, players[player]->m_move_hit_box_size, field.objects[i]->m_cube_hit_pos, field.objects[i]->m_cube_size_half))
			{
				players[player]->m_move_judge = true; // 移動に支障があるのTureを返す
				players[player]->Get_other(&field.objects[i]->m_cube_hit_pos, &field.objects[i]->m_cube_size_half); // Playerに当たった相手の情報を渡する
				players[player]->Move_Hit_Update();   // 壁擦り用の関数
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
		players[0]->Move_Hit_Update();   // 壁擦り用の関数
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
		players[1]->m_move_judge = false;
	}
}

//---------------------------------------------------------------------------
// タイマーの更新処理
//---------------------------------------------------------------------------
void GameScene::Time_Update(int& time_count)
{
	flame_count--;               // フレームカウントを減らす
	if (flame_count < 0) {       // フレームカウントが０になったら
		time_count--;            // タイマーを減らす
		flame_count = FLAME_MAX; // フレームカウントを設定しなおす
	}

	// タイマーがゼロになったら
	if (time_count <= 0) {
		time_count = 0; // ゼロで止める
	}
}

//---------------------------------------------------------------------------
// タイマーの描画処理
//---------------------------------------------------------------------------
void GameScene::Time_Draw()
{
	// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
	const char* name = "[%2d]";
	// 描画幅の取得
	float w = GetDrawStringWidth(name, -1);
	// 文字列の高さ取得
	float h = GetFontSize();

	SetFontSize(28); // フォントサイズの変更
	// 描画
	DrawFormatStringF(SCREEN_W / 2 + 16 - w, h - 16, GetColor(255, 255, 0), name, time_count);
	SetFontSize(18); // フォントサイズを戻す
}

//---------------------------------------------------------------------------
// チュートリアルでの描画処理
//---------------------------------------------------------------------------
void GameScene::Tutorial_Draw()
{
	// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
	const char* name = "チュートリアル";
	// 描画幅の取得
	float w = GetDrawStringWidth(name, -1);
	// 文字列の高さ取得
	float h = GetFontSize();

	SetFontSize(28); // フォントサイズの変更
	// 描画
	DrawFormatStringF(SCREEN_W / 2 + 16 - w, h - 16, GetColor(255, 255, 0), name, time_count);
	SetFontSize(18); // フォントサイズを戻す
}

//---------------------------------------------------------------------------
// エンドでの描画処理
//---------------------------------------------------------------------------
void GameScene::End_Draw()
{
	// 文字列の描画と描画幅の取得で2回使うのでここで定義しときます
	const char* name = "end";
	// 描画幅の取得
	float w = GetDrawStringWidth(name, -1);
	// 文字列の高さ取得
	float h = GetFontSize();
	
	SetFontSize(28); // フォントサイズの変更
	// 描画
	DrawFormatStringF(SCREEN_W / 2 + 16 - w, h - 16, GetColor(255, 255, 0), name, time_count);
	SetFontSize(18); // フォントサイズを戻す
}


//---------------------------------------------------------------------------
// 攻撃のあたり判定をとる関数
//---------------------------------------------------------------------------
void GameScene::Attack_Hit(int player1, int player2)
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


// 当たり判定用の構造体（わかりやすいように）
struct Capsule
{
	VECTOR top_pos;
	VECTOR bottom_pos;
	float   r;
};

// カプセル同志のあたり判定を使いやすくしたもの
bool HitCheck_Capsule_Capsule(const Capsule& cp1, const Capsule& cp2)
{
	//float angle = atan2f(cp2.bottom_pos.y - cp1.bottom_pos.y, cp2.bottom_pos.x - cp1.bottom_pos.x);
	//float dgree = TO_DEGREE(angle);
	return HitCheck_Capsule_Capsule(cp1.top_pos,
		cp1.bottom_pos,
		cp1.r,
		cp2.top_pos,
		cp2.bottom_pos,
		cp2.r) == 1;
}

//---------------------------------------------------------------------------
// ガードのあたり判定をとる関数
//---------------------------------------------------------------------------
void GameScene::Block_Hit(int player1, int player2)
{
	//　プレイヤー１方向ベクトル(殴る方)
	Vector3 vec1 = players[0]->m_rot - players[1]->m_pos;
	// プレイヤー２の方向ベクトル（殴られる方）
	Vector3 vec2 = players[1]->m_rot;
	// これでうまくいっているはず
	float vec = GetVector3Dot(vec1, vec2);
	
	// 今現在 前から殴ると整数値　後ろから殴るをマイナス値が返ってくる
	// 横から殴るるとへん

	// 当たり判定を取っていいときに当たっていたらダメージを入れる
	// プレイヤー０の攻撃判定とプレイヤー1のガードの判定
	

	// 攻撃用カプセル
	Capsule player2_hit_cp =
	{
		players[player2]->m_hit_cd_pos_top.VGet(),
		players[player2]->m_hit_cd_pos_under.VGet(),
		players[player2]->m_hit_cd_r
	};
	// ガードしているとき
	Capsule player1_cp =
	{
		players[player1]->m_block_top.VGet(),
		players[player1]->m_block_under.VGet(),
		players[player1]->m_block_r
	};
	// ガードしていないとき
	Capsule player1_no_cp =
	{
		players[player1]->m_hit_body_pos_top.VGet(),
		players[player1]->m_hit_body_pos_under.VGet(),
		players[player1]->m_hit_body_r
	};

	// ------------------------------------------------
	//	ガードしている人に対しての当たり判定を行うかどうか
	// ------------------------------------------------
	// 当たり判定をしていいかどうか
	bool can_check_hit = players[player1]->cd_hit_flag && players[player1]->block_flag;

	if (can_check_hit)
	{

		// どの方向からガードカプセルに攻撃が当たったのかを調べる
		// その方向がガードカプセル側であれば、”何もしない”
		// そうじゃなければ、”ダメージ処理”


		if (HitCheck_Capsule_Capsule(player1_cp, player2_hit_cp))
		{
			// player1のガード用カプセルとplayer2の攻撃用カプセルが当たったとき

		}
		else if (HitCheck_Capsule_Capsule(player1_no_cp, player2_hit_cp))
		{
			// player1の本体用のカプセルとplayer2の攻撃用カプセルが当たったとき
			players[player1]->m_hp_count.x -= players[player2]->m_attack_damage[players[player2]->attack_anim_pick]; // ダメージを入れる
			players[player1]->damage_flag = true;
		}
	}


	// パッドの長押し
	if (IsPadRepeat(PAD_ID::PAD_A, players[0]->GetPadNo()))
	{

	}
}

//---------------------------------------------------------------------------
// キャラクターのステータス描画処理
//---------------------------------------------------------------------------
void GameScene::Draw_Status()
{
	DrawBox(players[0]->m_hp_pos.x, players[0]->m_hp_pos.y, players[0]->m_hp_count.x, players[0]->m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(players[0]->m_hp_pos.x, players[0]->m_hp_pos.y, HP_MAX, players[0]->m_hp_count.y, GetColor(255, 255, 255));

	DrawBox(SCREEN_W / 2 + players[1]->m_hp_pos.x, players[1]->m_hp_pos.y, SCREEN_W / 2 + players[1]->m_hp_count.x, players[1]->m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(SCREEN_W / 2 + players[1]->m_hp_pos.x, players[1]->m_hp_pos.y, SCREEN_W / 2 + HP_MAX, players[1]->m_hp_count.y, GetColor(255, 255, 255));
}
