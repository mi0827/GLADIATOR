#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/Base.h"
#include "src/Character/Base/Character_Base.h"
#include "Ninja.h"

#define PANEL_SIZE	5.0f              // パネルの大きさ
#define PANEL_HALF	(PANEL_SIZE/2.0f) // パネルの半分の大きさ


// コンストラクタ（初期化）
Ninja::Ninja()
{
	m_pos.set(0.0f, 0.0f, 0.0f);             // 初期座標の設定
	m_rot.set(0.0f, 0.0f, 0.0f);             // 向きの設定
	m_before_mov.set(m_pos);                       // 最初は最初の座標を入れとく

	m_anim_num = 0;                                     // 最初は０ばんのアニメーションをする
	m_action_mode = 0;                                  // 最初は普通アニメーションモードにしておく
	m_attack_anim_pick = -1;                            // 最初はなんのアニメーションも入っていない
	m_check_move = false;                             // 最初は走っていいない

	//------------------------------
	// 当たり判定用変数

	//=============
	// カプセル
	m_hit_body_pos_top.clear();                       // 上側
	m_hit_body_pos_under.clear();                     // 下側
	m_hit_body_r = 2.0f;                              // 半径
	//======================
	// 移動用のボックス                                                   
	m_move_hit_box_size.set(PANEL_HALF - 0.1f, PANEL_HALF - 0.1f, PANEL_HALF - 0.1f);    // パネルの大きさ

	// 判断用、フラグ変数
	m_move_judge = false;     // 最初は動いてはいけない
	m_bead_hit_judg = false;    // なににもあたってない
	m_attack_flag = false;  // 攻撃していない
	m_damage_flag = false;  // 今ダメージを受けているのか
	m_block_flag = false;   // 今ガード中なのか


	m_hp_pos.set(10, 32);         // HPバーの描画位置初期化
	m_hp_count.set(HP_MAX, 32 + 30);   // HPの計算用の初期化
}

// 初期処理
void Ninja::Init(int player_num)
{
	m_model = MV1LoadModel("Data/Model/Ninja/Ninja.mv1");   // プレイヤーモデルの読み込み
	Animation_Init(); //< アニメーションの設定

	//pad_input = GetJoypadInputState(DX_INPUT_PAD3);  // ゲームパッドの読み込み

	if (player_num == 0) 
	{
		m_pos.set(0.0f, 0.0f, -50.0f);           // 初期座標の設定
		m_rot.set(0.0f, 0.0f, 0.0f);             // 向きの設定
	}
	else 
	{
		m_pos.set(0.0f, 0.0f, 500.0f);            // 初期座標の設定
		m_rot.set(0.0f, 180.0f, 0.0f);			  // 向きの設定
	}

	//// 仮
	//SetPadNo(DX_INPUT_PAD1);
}

//---------------------------------------------------------------------------
// アニメーション用の初期処理
//---------------------------------------------------------------------------
void Ninja::Animation_Init()
{
	// 普通アニメーションの初期化
	// アニメーションの読み込み
	CharacterBase::Nomal_Anim_New(ANIM_MAX);  // 普通アニメーションに必要な変数の配列を作る
	m_anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Ninja/Animation/Idle.mv1"); // アイドル
	m_anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Ninja/Animation/Run.mv1");   // 走る
	CharacterBase::Nomal_Anim_Init(ANIM_IDLE, ANIM_MAX, 0); // 普通アニメーションの初期設定

	// 攻撃アニメーションの初期化
	// アニメーションの読み込み
	CharacterBase::Attack_Anim_New(ATTACK_ANIM_MAX); // 攻撃アニメーションに必要な変数の配列を作る
	m_attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Ninja/Animation/Attack/long_normal_attack.mv1");       // 遠距離普通攻撃
	m_attack_anim_model[ATTACK_SHORT_NORMAL_1_ANIM] = MV1LoadModel("Data/Model/Ninja/Animation/Attack/Punch.mv1"); // 近距離攻撃１
	m_attack_anim_model[ATTACK_SLIDE_ANIM] = MV1LoadModel("Data/Model/Ninja/Animation/Attack/slide.mv1");                          // スライディング
	m_attack_anim_model[ATTACK_SPECIAL_ANIM] = MV1LoadModel("Data/Model/Ninja/Animation/Attack/special_attack.mv1");               // 必殺技
	CharacterBase::Attack_Anim_Init(ATTACK_ANIM_MAX, 0); // 攻撃アニメーションの初期設定
}

// 更新処理
void Ninja::Update(Vector3* camera_rot, int SE_Volume/*, bool status_flag*/)
{
	m_before_mov = m_pos; // 移動される前に入れ替えとく

	// アクションモードの判断してそれに合った操作をするようにする
	switch (m_action_mode)
	{
	case NORMAL_ACTION:        // 普通アクション 
		m_check_move = false;  // 常にリセット

		// 移動中はダッシュする
		// ゲームパッドの入力状態をとる
		//	ゲームパッドの左スティックの値を使って座標（ m_pos ）の値を変更
		// 左ステックでプレイヤーの向きや座標の更新
		// ゲームパッドの情報を取得（XINPUT の情報）
		XINPUT_STATE input;
		// ゲームパッドの情報を丸ごと取得
		//GetJoypadXInputState(DX_INPUT_PAD2, &input);
		GetJoypadXInputState((int)m_pad_no, &input);


		// 左スティックの値を設定
		m_mov.x = input.ThumbLX;
		m_mov.z = input.ThumbLY;
		// -32768 ～ 32767 を-1.0f　～　1.0fにします
		m_mov /= 32768.0f;
		// この移動用ベクトルの大きさがある程度大きい時だけ移動させようと思います
		if (m_mov.GetLength() > 0.5f) {
			CharacterBase::Move_GamePad(&m_check_move, &m_mov, camera_rot, &MOVE_SPEED);
		}

		// 移動をいまはやめておく
		// 移動処理
		CharacterBase::Move_Player(&m_check_move, camera_rot, &m_rot, &MOVE_SPEED);


		// 移動中ならアニメーションの変更と当たり判定の移動
		if (m_check_move) 
		{

			m_anim_num = ANIM_RUN;  // 移動中なので走るアニメーションに
			{                     // プレイヤー座標に当たり判定用のカプセルの位置を合わせる
				m_hit_body_pos_top = m_pos;
				m_hit_body_pos_top.y += 17.0f; // 高さを出す
				m_hit_body_pos_under = m_pos;
				m_hit_body_pos_under.y += 3.0f;
			}
		}
		else 
		{                           // どの移動キーも押されてなかったら
			m_anim_num = ANIM_IDLE;        // アイドル状態にする
			{                            // プレイヤー座標に当たり判定用のカプセルの位置を合わせる
				m_hit_body_pos_top = m_pos;
				m_hit_body_pos_top.y += 17.0f; // 高さを出す
				m_hit_body_pos_under = m_pos;
				m_hit_body_pos_under.y += 3.0f;

			}
		}

		//=================================
		// 近距離攻撃
		//=================================
		// マウスの左クリックまたはAボタンで近距離攻撃
		if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no)) 
		{
			m_action_mode = ATTACK_ACTION;                    // モデルのアクションを攻撃に変更
			m_attack_anim_pick = ATTACK_SHORT_NORMAL_1_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(0);                 // 行いたい攻撃アニメーションをセット

			break;
		}

		//=================================
		// 遠距離攻撃
		//=================================
		// マウスの右クリック、または、Yボタンで遠距離攻撃
		if (PushMouseInput(MOUSE_INPUT_RIGHT) || IsPadOn(PAD_ID::PAD_Y, m_pad_no))
		{
			m_action_mode = ATTACK_ACTION;                 // モデルのアクションを攻撃に変更
			m_attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(0);              // 行いたい攻撃アニメーションをセット
			break;
		}

		//=================================
		// スライディング
		//=================================
		// スペースキークリック、または、Bボタンで遠距離攻撃
		if (PushHitKey(KEY_INPUT_SPACE) || IsPadOn(PAD_ID::PAD_B, m_pad_no)) 
		{
			m_action_mode = ATTACK_ACTION;           // モデルのアクションを攻撃に変更
			m_attack_anim_pick = ATTACK_SLIDE_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(0);        // 行いたい攻撃アニメーションをセット
			break;
		}


		//=================================
		// 必殺技
		//=================================
		// 『 Eキー ＋ Qキー 』クリック、または、『 Rボタン + Lボタン 』で必殺技攻撃
		if (PushHitKey(KEY_INPUT_E) && PushHitKey(KEY_INPUT_Q) || IsPadOn(PAD_ID::PAD_L, m_pad_no) && IsPadOn(PAD_ID::PAD_R, m_pad_no)) 
		{
			m_action_mode = ATTACK_ACTION;             // モデルのアクションを攻撃に変更
			m_attack_anim_pick = ATTACK_SPECIAL_ANIM;  // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(0);          // 行いたい攻撃アニメーションをセット
			break;
		}

		// アニメーション用のフレームカウントを進める
		for (int i = 0; i < ANIM_MAX; ++i) 
		{
			m_anim_frame[i] += 1.0f;
			if (m_anim_frame[i] >= m_anim_total[i])
			{
				m_anim_frame[i] = 0.0f;
			}
			// アニメーションの再生
			// 使いたくないアニメーション
			if (i != m_anim_num)
			{

				m_anim_rate[i] -= 0.1f; // 割合を減らす
			}
			else {// 使いたいアニメーション		
				m_anim_rate[i] += 0.1f; // 割合を増やす
			}

			m_anim_rate[i] = max(0.0f, min(m_anim_rate[i], 1.0f));                                    // 割合を0.0f ～ 1.0fにする（これをしないと踊り狂う） 
			MV1SetAttachAnimTime(m_model, m_anim_attach[i], m_anim_frame[i]);  // そのフレームのアニメーションにする
			MV1SetAttachAnimBlendRate(m_model, m_anim_attach[i], m_anim_rate[i]);   // それぞれにアニメーションの割合分再生します
		}
		break;

	case ATTACK_ACTION: // 攻撃アクション
		// アニメーションの再生
		// 攻撃アニメーション用のフレームカウントを進める
		m_attack_anim_frame[m_attack_anim_pick]++;
		if (m_attack_anim_frame[m_attack_anim_pick] >= m_attack_anim_total[m_attack_anim_pick]) { // アニメーションが一周したら
			m_attack_anim_frame[m_attack_anim_pick] = 0.0f;
			m_attack_anim_attach[m_attack_anim_pick] = MV1DetachAnim(m_model, m_attack_anim_attach[m_attack_anim_pick]);  // 攻撃アニメーションをディタッチしておく
			m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 0, m_anim_model[m_anim_num]);                   // モデルに元のアニメーションをアタッチしなおす（直近のアニメーション）
			m_action_mode = NORMAL_ACTION; 	// アニメーションが１ループしたかrATTACK_ACTIONから出る
			// 攻撃が終わったのでこうげきしていないようにする
			// attack_hlag = false;
		}
		MV1SetAttachAnimTime(m_model, m_attack_anim_attach[m_attack_anim_pick], m_attack_anim_frame[m_attack_anim_pick]); // アニメーションの再生
		break;
	}


	if (m_attack_flag) 
	{

		// 弾用の変数
		if (m_lifespan_count >= 120.0f) 
		{
			m_bead_pos = new Vector3;
			*m_bead_pos = m_pos; // 一旦プレイヤーの位置にしておく（本来プレイヤーの手の位置に合わせる）
			m_bead_pos->y += 10.0f; // y座標をずらして空中に浮かべる
		}
		// 一旦前に飛ばす
		m_bead_pos->x += 3 * sinf(TO_RADIAN(m_rot.y));
		m_bead_pos->z += 3 * cosf(TO_RADIAN(m_rot.y));
		m_lifespan_count--; // 弾が消えるまでのカウントを進める

		// カウントが一定にまで減るか、当たり判定があったら
		if (m_lifespan_count <= 0 || m_bead_hit_judg)
		{
			delete m_bead_pos; // 弾の解放
			m_bead_pos = NULL;
			m_lifespan_count = 120.0f; // カウントのリセット
			m_attack_flag = false; // 攻撃を終わらせておく
		}
	}
	// ステータスの更新処理
	CharacterBase::Update_Status();
}

//---------------------------------------------------------------------------
// プレイヤーの移動用当たり判定（壁擦り）
//---------------------------------------------------------------------------
void  Ninja::Move_Hit_Update()
{
	CharacterBase::Move_Hit(&m_before_mov, &m_move_hit_box_size, &m_hit_other_pos, &m_hit_other_size);
}

void Ninja::Attack_PressButton_Update(Vector3* camera_rot)
{
}

void Ninja::Attack_Update()
{
}

void Ninja::Damage_Update(int* m_attack_damage)
{
}

void Ninja::Block_Update()
{
}

//---------------------------------------------------------------------------
// ステータス描画処理
//---------------------------------------------------------------------------
// CharacterBase::Draw_Status();

//---------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------
void Ninja::Draw()
{
	// 玉を描画する(今だけ)
	if (m_bead_pos != NULL) 
	{
		DrawSphere3D(m_bead_pos->VGet(), 2.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	// 当たり判定を見えるようにする物
	Vector3 draw_box_pos;
	draw_box_pos = m_pos + m_move_hit_box_pos;
	Vector3 draw_box_size;
	draw_box_size = m_pos + m_move_hit_box_pos + m_move_hit_box_size;
	DrawCube3D(draw_box_pos.VGet(), draw_box_size.VGet(), GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);

	// プレイヤーの描画設定
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));                                             // 描画するプレイヤーモデルの座標の設定
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y + 180), TO_RADIAN(m_rot.z)));   // モデルの回転
	MV1SetScale(m_model, VGet(0.1f, 0.1f, 0.1f));                                                         // モデルの大きさ(10分の１のサイズ)
	MV1DrawModel(m_model);
}

//---------------------------------------------------------------------------
// 終了処理
//---------------------------------------------------------------------------
void Ninja::Exit()
{
	MV1DeleteModel(m_model);       // モデルの削除
	for (int i = 0; i < ANIM_MAX; i++) 
	{  // アニメーションの削除
		MV1DeleteModel(m_anim_model[i]);
	}

	// 攻撃アニメーションの削除
	for (int i = 0; i < ATTACK_ANIM_MAX; i++)
	{
		MV1DeleteModel(m_attack_anim_model[i]);
	}

	// 弾が解放されていなかったら解放する
	if (m_bead_pos != NULL)
	{
		delete m_bead_pos;
	}

	// アニメーション用変数たちのdelete
	CharacterBase::Anim_Delete();
}

//---------------------------------------------------------------------------
// SEの初期化
//---------------------------------------------------------------------------
void Ninja::SE_Init()
{
}
