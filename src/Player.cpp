#include "WinMain.h"
#include "GameMain.h"
#include "Vector3.h"
#include "Vector2.h"
#include "SE.h"
#include "Base.h"
#include "InputPad.h"
#include "Character_Base.h"
#include "Effect.h"
#include "Player.h"
#define PANEL_SIZE	5.0f              // パネルの大きさ
#define PANEL_HALF	(PANEL_SIZE/2.0f) // パネルの半分の大きさ
#define ATTACK_ANIM_SPEED 1.4f

// SEクラスのオブジェクト
SE player_se;
//---------------------------------------------------------------------------
// コンストラクタ（初期化）
//---------------------------------------------------------------------------

Player::Player()
{
	m_pos.set(0.0f, 0.0f, 0.0f);             // 初期座標の設定
	m_rot.set(0.0f, 0.0f, 0.0f);             // 向きの設定
	m_before_mov.set(m_pos);                       // 最初は最初の座標を入れとく

	m_anim_num = 0;                                    // 最初は０ばんのアニメーションをする
	m_action_mode = 0;                                 // 最初は普通アニメーションモードにしておく
	m_attack_anim_pick = -1;                           // 最初はなんのアニメーションも入っていない
	m_check_move = false;                            // 最初は走っていいない

	//------------------------------
	// 当たり判定用変数
	//=============
	// 本体の当たり判定
	// カプセル
	m_hit_body_pos_top.clear();                       // 上側
	m_hit_body_pos_under.clear();                     // 下側
	m_hit_body_r = HIT_BODY_R;                        // 半径

	// あたり判定用
	m_hit_cd_pos_top.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 13, m_pos.z + 8 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_cd_pos_under.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + (float)12.7, m_pos.z + 6 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_cd_r = 1.0f;
	//======================
	// 移動用のボックス                                                   
	m_move_hit_box_size.set(PANEL_HALF - (float)0.1, PANEL_HALF - (float)0.1, PANEL_HALF - (float)0.1);    // パネルの大きさ

	// 判断用、フラグ変数
	m_move_judge = false;                              // 最初は動いてはいけない
	m_attack_flag = false;                               // 攻撃していない
	m_bead_hit_flag = false;                             // なににもあたってない
	m_lifespan_count = NULL;


	m_combo_flag = false; // 攻撃を何もしていないのでフラグをげる
	m_now_hit_area = 0;
	m_player_num = 0;
	for (int i = 0; i < 2; i++)
	{
		m_color[i] = { 0,0,0,0 }; // このキャラの色
	}
}

//---------------------------------------------------------------------------
// 初期処理
//---------------------------------------------------------------------------
void Player::Init(int player_num)
{
	m_player_num = player_num; // 1pか2pかを入れる
	m_model = MV1LoadModel("Data/Model/Player/Player.mv1");   // プレイヤーモデルの読み込み
	// このキャラのモデルのマテリアルの色を取得
	m_color[0] = MV1GetMaterialDifColor(m_model, 0);
	m_color[1] = MV1GetMaterialDifColor(m_model, 1);

	Animation_Init(); //< アニメーションの設定

	//Effect_New(EFFECT_MAX, m_effect_container_ptr, m_effect_handle);
	//m_effect_container_ptr = new int[EFFECT_MAX + 2];
	m_effect_container = EffectContainerNew(EFFECT_MAX);
	m_effect_handle = EffectContainerNew(EFFECT_MAX);
	// エフェクトの読み込み
	m_effect_container[THROW_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/Aura01.efkefc", 1.0);   // 投げものエフェクト
	m_effect_container[PUNCH_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/Punch0.efkefc", 0.5f);  // パンチエフェクト
	m_effect_container[PUNCH2_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/Punch1.efkefc", 0.3f);  // パンチ２エフェクト
	m_effect_container[GUARD_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/guard.efkefc", 3.0f);  // ガード用
	m_effect_container[SPECIAL_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/special.efkefc", 3.0f);  // 必殺技１
	m_effect_container[SPECIAL2_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/special2.efkefc", 13.0f);  // 必殺技２
	m_effect_container[WARP_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/warp.efkefc", 1.0f);  // ワープエフェクト
	// pad_input = GetJoypadInputState(DX_INPUT_PAD3);  // ゲームパッドの読み込み


	if (player_num == 0)
	{
		m_pos.set(350.0f, 0.0f, 150.0f);           // 初期座標の設定
		m_rot.set(0.0f, 0.0f, 0.0f);             // 向きの設定
	}
	else
	{
		m_pos.set(350.0f, 0.0f, 450.0f);            // 初期座標の設定
		m_rot.set(0.0f, 180.0f, 0.0f);			  // 向きの設定
	}

	// 攻撃力の設定
	CharacterBase::Set_Attack_Damage(ATTACK_ANIM_MAX, m_damage);

	SE_Init(); // SEの初期化
}

//---------------------------------------------------------------------------
// アニメーション用の初期処理
//---------------------------------------------------------------------------
void Player::Animation_Init()
{
	// 普通アニメーションの初期化
	CharacterBase::Nomal_Anim_New(ANIM_MAX);  // 普通アニメーションに必要な変数の配列を作る
	m_anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Player/Animation/Idle.mv1"); // アイドル
	m_anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Player/Animation/Player_Run.mv1");   // 走る
	CharacterBase::Nomal_Anim_Init(ANIM_IDLE, ANIM_MAX, 1); // 普通アニメーションの初期設定

	// 攻撃アニメーションの初期化
	CharacterBase::Attack_Anim_New(ATTACK_ANIM_MAX); //< 攻撃アニメーションに必要な変数の配列を作る
	m_attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/long_normal_attack.mv1");       // 遠距離普通攻撃
	m_attack_anim_model[ATTACK_PUNCH_1_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch.mv1");                        // パンチ１
	m_attack_anim_model[ATTACK_PUNCH_2_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch2.mv1");                       // パンチ２
	m_attack_anim_model[ATTACK_PUNCH_3_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch3.mv1");                       // パンチ３
	m_attack_anim_model[ATTACK_PUNCH_4_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch_Kick.mv1");                   // コンボ攻撃の最後の攻撃（キックになってる）
	m_attack_anim_model[ATTACK_WARP_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/slide.mv1");                          // スライディング
	m_attack_anim_model[ATTACK_SPECIAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/special_attack.mv1");               // 必殺技
	CharacterBase::Attack_Anim_Init(ATTACK_ANIM_MAX, 1); //< 攻撃アニメーションの初期設定

	// ダメージアニメーションの初期化
	CharacterBase::Damage_Anim_New(DAMAGE_ANIM_MAX); //< ダメージアニメーションに必要な変数の配列を作る
	m_damage_anim_model[DAMAGE_ANIM] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/damage1.mv1");     //< ダメージ食らった時
	m_damage_anim_model[DAMAGE_ANIM_1] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/damage2.mv1");   //< ダメージ食らった時２
	m_damage_anim_model[DAMAGE_ANIM_2] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/SweepFall.mv1"); //< 吹き飛ぶアニメーション
	m_damage_anim_model[DAMAGE_ANIM_3] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/GettingUp.mv1"); //< 起き上がるアニメーション
	m_damage_anim_model[DAMAGE_ANIM_END] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/die.mv1");
	CharacterBase::Damage_Anim_Init(DAMAGE_ANIM_MAX, 1); //< ダメージアニメーションの初期化

	// ガードアニメーションの設定
	CharacterBase::Block_Anim_New(BLOCK_ANIM_MAX);
	m_block_anim_model[BLOCK_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Block/block.mv1");

	CharacterBase::Block_Anim_Init(BLOCK_ANIM_MAX, 1);
}

//---------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------
void Player::Update(Vector3* camera_rot, int SE_Volume/*, bool status_flag*/)
{
	
	// SEのボリューム調整
	player_se.SE_ChangeVolume(SE_Volume, SE_MAX);

	m_before_mov = m_pos; // 移動される前に入れ替えとく
	m_action_flag = false; // アクションフラグを下す
	m_cd_hit_flag = false;
	// アクションモードの判断してそれに合った操作をするようにする
	switch (m_action_mode)
	{
	case NORMAL_ACTION:        // 普通アクション 
		m_check_move = false;  // 常にリセット

		//=================================
		// アクションに関するボタン押し用の関数（見やすくするための関数）
		//=================================
		Attack_PressButton_Update(camera_rot);
		if (m_action_flag)
		{ // アクションフラグが上がっていたら
			//// アニメーションの再生
			//// 使いたくないアニメーション
			//if (anim_num == 0) {

			//	anim_rate[0] =1.0f; // 割合を減らす
			//	anim_rate[1] = 0.0f;
			//}
			//else {// 使いたいアニメーション		
			//	anim_rate[0] = 0.0f; // 割合を減らす
			//	anim_rate[1] = 1.0f;
			//}
			
			break;         // 後の処理を飛ばす
		}


		//=================================
		// ダメージのを食らったら
		//=================================
		if (m_damage_flag) 
		{
			m_action_mode = DAMAGE_ACTION;            // モデルのアクションをダメージに変更
			if (m_now_hp == 0) {                    // 体力がなくなった
				m_damage_anim_pick = DAMAGE_ANIM_END; // 死ぬアニメーションにする
			}
			CharacterBase::Damage_Action(1);  // 行いたいダメージアニメーションをセット
			break;
		}
		// 移動処理
		CharacterBase::Move_Player(&m_check_move, camera_rot, &m_rot, &MOVE_SPEED);
		// 体の当たり判定の場所の設定
		m_hit_body_pos_top = m_pos;
		m_hit_body_pos_top.y += 17.0f; // 高さを出す
		m_hit_body_pos_under = m_pos;
		m_hit_body_pos_under.y += 3.0f;
		// 移動中ならアニメーションの変更と当たり判定の移動
		if (m_check_move) 
		{
			m_anim_num = ANIM_RUN;  // 移動中なので走るアニメーションに

		}
		else 
		{                           // どの移動キーも押されてなかったら
			m_anim_num = ANIM_IDLE;   // アイドル状態にする

		}
		// アニメーション用のフレームカウントを進める
		for (int i = 0; i < ANIM_MAX; ++i) {
			if (m_anim_num == ANIM_RUN) 
			{
				m_anim_frame[i] += 0.9f;
			}
			else
			{
				m_anim_frame[i] += 1.0f;
			}
			if (m_anim_frame[i] >= m_anim_total[i]) 
			{
				m_anim_frame[i] = 0.0f;
			}
			// アニメーションの再生
			// 使いたくないアニメーション
			if (i != m_anim_num) 
			{

				m_anim_rate[i] -= 1.0f; // 割合を減らす
			}
			else
			{                         // 使いたいアニメーション		
				m_anim_rate[i] += 1.0f; // 割合を増やす
			}

			m_anim_rate[i] = max(0.0f, min(m_anim_rate[i], 1.0f));                                    // 割合を0.0f ～ 1.0fにする（これをしないと踊り狂う） 
			MV1SetAttachAnimTime(m_model, m_anim_attach[i], m_anim_frame[i]);  // そのフレームのアニメーションにする
			MV1SetAttachAnimBlendRate(m_model, m_anim_attach[i], m_anim_rate[i]);   // それぞれにアニメーションの割合分再生します
		}


		break;

	case ATTACK_ACTION: // 攻撃アクション

		// アニメーションの再生
		// 攻撃アニメーション用のフレームカウントを進める
		m_attack_anim_frame[m_attack_anim_pick] += ATTACK_ANIM_SPEED;
		if (m_combo_flag) 
		{
			// コンボフラグが立っていたら
			if (m_attack_anim_frame[m_attack_anim_pick] >= m_attack_anim_total[m_attack_anim_pick]) 
			{                                           // アニメーションが一周したら
				m_attack_anim_frame[m_attack_anim_pick] = 0.0f;
				m_attack_anim_attach[m_attack_anim_pick] = MV1DetachAnim(m_model, m_attack_anim_attach[m_attack_anim_pick]);  // 攻撃アニメーションをディタッチしておく
				m_attack_anim_attach[m_next_combo] = MV1AttachAnim(m_model, 1, m_attack_anim_model[m_next_combo]); // 次のコンボ攻撃アニメーションをモデルにつけなおす
				m_attack_anim_pick = m_next_combo;                                                                                          // 次の攻撃に差し替える
				m_combo_flag = false;                                                                                                     // コンボフラグを下げる
			}
		}
		else 
		{
			// コンボフラグが降りていたら
			if (m_attack_anim_frame[m_attack_anim_pick] >= m_attack_anim_total[m_attack_anim_pick]) 
			{                                           // アニメーションが一周したら
				m_attack_anim_frame[m_attack_anim_pick] = 0.0f;
				m_attack_anim_attach[m_attack_anim_pick] = MV1DetachAnim(m_model, m_attack_anim_attach[m_attack_anim_pick]);  // 攻撃アニメーションをディタッチしておく
				m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 1, m_anim_model[m_anim_num]);                              // モデルに元のアニメーションをアタッチしなおす（直近のアニメーション）
				m_action_mode = NORMAL_ACTION;                                                                                         	// アニメーションが１ループしたかrATTACK_ACTIONから出る
				m_attack_flag = false;                                                                                                    // 攻撃が終わったのでこうげきしていないようにする
				m_attack_anim_pick = ATTACK_ANIM_MAX;                                                                                     // 攻撃アニメーションが終わったのでアニメーションが設定されていない値にしておく
				m_combo_flag = false;                                                                                                     // コンボフラグを下げる
				m_bead_pos = m_pos;
			}
		}
		MV1SetAttachAnimTime(m_model, m_attack_anim_attach[m_attack_anim_pick], m_attack_anim_frame[m_attack_anim_pick]); // アニメーションの再生

		if (m_attack_flag) 
		{ // 攻撃フラグが上がっていたら
			Attack_Update();  // 攻撃用のアップデート
		}
		break;

	case BLOCK_ACTION:

		// アニメーションの再生
		// ガードアニメーション用のフレームカウントを進める
		// 防御フラグが上がっている間は防御アニメーションをループさせる
		m_block_anim_frame[m_block_anim_pick]++;

		if (m_block_anim_frame[m_block_anim_pick] >= m_block_anim_total[m_block_anim_pick]) 
		{                                                                                                          // アニメーションが一周したら
			m_block_anim_frame[m_block_anim_pick] = 0.0f;                                                              // アニメーションを最初からにしておく
		}
		if (m_block_flag == false) 
		{                                                                                                          // ガードフラグが下がったら
			m_block_anim_attach[m_block_anim_pick] = MV1DetachAnim(m_model, m_block_anim_attach[m_block_anim_pick]);       // ガードアニメーションをディタッチしておく
			m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 1, m_anim_model[m_anim_num]);                               // モデルに元のアニメーションをアタッチしなおす（直近のアニメーション）
			m_action_mode = NORMAL_ACTION; 	                                                                       // アニメーションが１ループしたかrATTACK_ACTIONから出る
			m_block_anim_pick = BLOCK_ANIM_MAX;                                                                      // ガードのピックをリセット
		}
		//=================================
		// ガード中にダメージを食らったとき
		//=================================
		if (m_damage_flag && m_block_flag == true) 
		{
			m_block_anim_frame[m_block_anim_pick] = 0.0f;                                                              // アニメーションを最初からにしておく
			m_block_anim_attach[m_block_anim_pick] = MV1DetachAnim(m_model, m_block_anim_attach[m_block_anim_pick]);       // ガードアニメーションをディタッチしておく
			m_action_mode = DAMAGE_ACTION; 	                                                                       // ダメージを受けているのでDAMAGE_ACTIOに移動
			m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 1, m_anim_model[m_anim_num]);                               // モデルに元のアニメーションをアタッチしなおす（直近のアニメーシ
			CharacterBase::Damage_Action(1);                                                                       // 行いたいダメージアニメーションをセット
			// damage_anim_attach[damage_anim_pick] = MV1AttachAnim(m_model, 1, damage_anim_model[damage_anim_pick]);      	// 使いたいアニメーションをモデルにつけなおす
			m_block_anim_pick = BLOCK_ANIM_MAX;																	   // ガードのピックをリセット
			m_block_flag = false;
			break;
		}
		MV1SetAttachAnimTime(m_model, m_block_anim_attach[m_block_anim_pick], m_block_anim_frame[m_block_anim_pick]); // アニメーションの再生

		if (m_block_flag)
		{                     // ガードフラグが上がったら
			Block_Update();   // ガード用のアップデート
		}
		break;

	case DAMAGE_ACTION: // ダメージを食らった時のアニメーション再生

		m_damage_anim_frame[m_damage_anim_pick]++;
		if (m_damage_anim_frame[m_damage_anim_pick] >= m_damage_anim_total[m_damage_anim_pick]) 
		{                                                                                                                          // アニメーションが一周したら
			m_damage_anim_frame[m_damage_anim_pick] = (float)MV1DetachAnim((int)m_model, (int)m_damage_anim_attach[m_damage_anim_pick]);   // 攻撃アニメーションをディタッチしておく
			m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 1, m_anim_model[m_anim_num]);                              // モデルに元のアニメーションをアタッチしなおす（直近のアニメーション）
			m_action_mode = NORMAL_ACTION; 	                                                                      // アニメーションが１ループしたからダメージアニメーションから出る
			// キャラのｈｐがゼロ以外の時
			if (m_now_hp != 0) 
			{
				m_damage_anim_frame[m_damage_anim_pick] = 0.0f;
				m_damage_flag = false; // ダメージアニメーションフラグを下す
				m_damage_anim_pick = 0;// DAMAGE_ANIM_MAX;	// !!修正ポイント!!
			}
			// 攻撃アニメーションが終わったのでアニメーションが設定されていない値にしておく
		}
		MV1SetAttachAnimTime(m_model, m_damage_anim_attach[m_damage_anim_pick], m_damage_anim_frame[m_damage_anim_pick]);

		break;
	}


	CharacterBase::Update_Status();
}


//---------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------
void Player::Draw()
{
	if (!m_bead_hit_flag) 
	{
		DrawCapsule3D(m_bead_pos.VGet(), m_bead_pos.VGet(), m_bead_r, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	// 玉を描画する(今だけ)
#ifdef DEBUG
	// プレイヤー自身の当たり判定を見えるようにしている
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	// 当たり判定を見えるようにする物
	// 向いている方向に座標を設定（今はパンチに位置）
	//hit_areas[ATTACK_LONG_NORMAL_ANIM].hit_top = Vector3();

	if (cd_hit_flag && attack_flag) {
		DrawCapsule3D(m_hit_cd_pos_top.VGet(), m_hit_cd_pos_under.VGet(), m_hit_cd_r, 8, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
	}
	if (cd_hit_flag && block_flag) {
		DrawCapsule3D(m_block_top.VGet(), m_block_under.VGet(), m_block_r, 8, GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);
	}
#endif // DEBUG
	// 1P,2Pに応じてキャラの色を変える
	if (m_player_num == 0) 
	{
		MV1SetMaterialDifColor(m_model, 0, GetColorF(0.8f, 0.0f, 0.0f, 1.0f));
		MV1SetMaterialDifColor(m_model, 1, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else 
	{
		MV1SetMaterialDifColor(m_model, 0, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
		MV1SetMaterialDifColor(m_model, 1, GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
	}

	// プレイヤーの描画設定
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z)); // 描画するプレイヤーモデルの座標の設定
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y + 180), TO_RADIAN(m_rot.z))); // モデルの回転
	MV1SetScale(m_model, VGet(0.1f, 0.1f, 0.1f)); // モデルの大きさ(10分の１のサイズ)
	MV1DrawModel(m_model); // モデルの描画

	// Effekseer描画処理
	DrawEffekseer3D();
}

//---------------------------------------------------------------------------
// 終了処理
//---------------------------------------------------------------------------
void Player::Exit()
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

	// 攻撃用あたり判定が解放されていなかったら
	if (!m_now_hit_area) 
	{
		m_now_hit_area = nullptr;
	}

	// baseでnewした変数たちのdelete
	CharacterBase::Delete();

}

//---------------------------------------------------------------------------
// SE用の初期処理
//---------------------------------------------------------------------------
void Player::SE_Init()
{
	// SEの数分の配列の取得
	player_se.SE_ContainerNew(SE_MAX);
	player_se.Load_SE("Data/Model/Player/SE/long.mp3", SE_LONG);      // パンチ１
	player_se.Load_SE("Data/Model/Player/SE/punch1.mp3", SE_PUNCH_1); // パンチ１
	player_se.Load_SE("Data/Model/Player/SE/punch2.mp3", SE_PUNCH_2); // パンチ２
	player_se.Load_SE("Data/Model/Player/SE/punch3.mp3", SE_PUNCH_3); // ぱんち３
	player_se.Load_SE("Data/Model/Player/SE/kick.mp3", SE_KICK);      // キック
	player_se.Load_SE("Data/Model/Player/SE/special.mp3", SE_SPECIAL);// 必殺技
}


//---------------------------------------------------------------------------
// プレイヤーの移動用当たり判定（壁擦り）
//---------------------------------------------------------------------------
void Player::Move_Hit_Update()
{
	CharacterBase::Move_Hit(&m_before_mov, &m_move_hit_box_size, &m_hit_other_pos, &m_hit_other_size);
}


//---------------------------------------------------------------------------
// アクションに関するボタン押し用の関数（見やすくするための関数）
//---------------------------------------------------------------------------
void Player::Attack_PressButton_Update(Vector3* camera_rot)
{

	//=================================
	// 近距離攻撃
	//=================================
	// マウスの左クリックまたはAボタンでパンチ攻撃
	// なおかつバグが出ないようにaction_flagが下りてたら
	if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no) && m_action_flag == false) 
	{
		m_action_mode = ATTACK_ACTION;                    // モデルのアクションを攻撃に変更
		m_attack_anim_pick = ATTACK_PUNCH_1_ANIM;         // 近距離攻撃アクションを設定
		CharacterBase::Attack_Action(1);          // 行いたい攻撃アニメーションをセット	
		m_action_flag = true;                             // アクションフラグを上げる
		//m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // エフェクトの再生
		//SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
	}

	//=================================
	// 遠距離攻撃
	//=================================
	// マウスの右クリック、または、Bボタンで遠距離攻撃
	// なおかつバグが出ないようにaction_flagが下りてたら
	if (PushMouseInput(MOUSE_INPUT_RIGHT) || IsPadOn(PAD_ID::PAD_B, m_pad_no) && m_action_flag == false) 
	{
		//if (IsPadRepeat(PAD_ID::PAD_Y, PAD_NO::PAD_NO1)) {

		m_action_mode = ATTACK_ACTION;                 // モデルのアクションを攻撃に変更
		m_attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // 近距離攻撃アクションを設定
		//bead_hit_flag = false;
		CharacterBase::Attack_Action(1);       // 行いたい攻撃アニメーションをセット	
		m_action_flag = true;                          // アクションフラグを上げる
		m_lifespan_count = NULL;
	}

	//=================================
	// ワープ
	//=================================
	if (m_skill_flag) { // スキルが使用できるなら
		// スペースキークリック、または、Yボタンで遠距離攻撃
		// なおかつバグが出ないようにaction_flagが下りてたら
		if (PushHitKey(KEY_INPUT_SPACE) || IsPadOn(PAD_ID::PAD_Y, m_pad_no) && m_action_flag == false) 
		{

			m_skill_count.x = 0; // スキルの使用なのでカウントをリセット
			m_action_mode = ATTACK_ACTION;           // モデルのアクションを攻撃に変更
			m_attack_anim_pick = ATTACK_WARP_ANIM;   // 近距離攻撃アクションを設定
			CharacterBase::Attack_Action(1);        // 行いたい攻撃アニメーションをセット
			CharacterBase::Move_Front(&m_check_move, &m_rot, &m_rot, &WARP);
			m_action_flag = true;                          // アクションフラグを上げる
			m_skill_flag = false;                          // skillを使用済みにしておく
			// エフェクトの再生
			m_effect_handle[WARP_EFFECT] = PlayEffekseer3DEffect(m_effect_container[WARP_EFFECT]); // エフェクトの再生
			SetRotationPlayingEffekseer3DEffect(m_effect_handle[WARP_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
			// エフェクトの座標を設定
			SetPosPlayingEffekseer3DEffect(m_effect_handle[WARP_EFFECT], m_pos.x, m_pos.y, m_pos.z);
		}
	}

	//=================================
	// 必殺技
	//=================================
	// 『 Eキー ＋ Qキー 』クリック、または、『 Rボタン + Lボタン 』で必殺技攻撃
	// なおかつバグが出ないようにaction_flagが下りてたら
	if (m_sp_flag)
	{ // 必殺技が使用可能なら
		if (PushHitKey(KEY_INPUT_E) && PushHitKey(KEY_INPUT_Q) || IsPadOn(PAD_ID::PAD_L, m_pad_no) && IsPadOn(PAD_ID::PAD_R, m_pad_no) && m_action_flag == false)
		{
			m_sp_count.x = 0;                        // SPの使用なのでカウントをリセット
			m_action_mode = ATTACK_ACTION;             // モデルのアクションを攻撃に変更
			m_attack_anim_pick = ATTACK_SPECIAL_ANIM;  // 必殺攻撃アクションを設定
			CharacterBase::Attack_Action(1);   // 行いたい攻撃アニメーションをセット
			// bead_hit_flag = false;
			m_action_flag = true;                      // アクションフラグを上げる
			m_sp_flag = false;                         // SPを使用済みにしておく
			m_lifespan_count = NULL;
		}
	}

	//=================================
	// ガード
	//=================================
	// または、Xボタンで遠距離攻撃
	/*if (PushHitKey(KEY_INPUT_LSHIFT) || IsPadOn(PAD_ID::PAD_X, pad_no)) {*/      // ボタンの一度押し
	// ダメージを受けていない
	// なおかつバグが出ないようにaction_flagが下りてたら
	if (/*CheckHitKey(KEY_INPUT_LSHIFT) ||*/ IsPadRepeat(PAD_ID::PAD_X, m_pad_no) && m_action_flag == false) 
	{                                         // Xボタンの長押し
		m_action_mode = BLOCK_ACTION;           // モデルのアクションをガードに変更
		m_block_anim_pick = BLOCK_ANIM;         // ガードアクションを設定
		CharacterBase::Block_Action(1);       // 行いたい攻撃アニメーションをセット
		m_action_flag = true;                   // アクションフラグを上げる

	}
}
//---------------------------------------------------------------------------
// 攻撃用アップデート
//---------------------------------------------------------------------------
void Player::Attack_Update()
{
	switch (m_attack_anim_pick)
	{
	case ATTACK_LONG_NORMAL_ANIM: // 遠距離攻撃（弾を出す）

		if (m_attack_anim_frame[m_attack_anim_pick] >= 30) 
		{
			if (m_attack_anim_frame[m_attack_anim_pick] <= 30 + ATTACK_ANIM_SPEED) 
			{
				m_effect_handle[THROW_EFFECT] = PlayEffekseer3DEffect(m_effect_container[THROW_EFFECT]);            // エフェクトの再生
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[THROW_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
				SetSpeedPlayingEffekseer3DEffect(m_effect_handle[THROW_EFFECT], (float)1.9);                        // エフェクトの再生速度
				m_bead_pos = m_pos;    // 一旦プレイヤーの位置にしておく（本来プレイヤーの手の位置に合わせる）
				m_bead_pos.y += 10.0f; // y座標をずらして空中に浮かべる
				m_bead_r = 2.0f;       // 半径の設定
				m_bead_hit_flag = false;
			}
			// SEの再生
			if (!player_se.Playing_SE(SE_LONG))
			{
				player_se.Play_SE(SE_LONG, DX_PLAYTYPE_BACK, true);
			}

			// 一旦前に飛ばす
			m_bead_pos.x += 3 * sinf(TO_RADIAN(m_rot.y));
			m_bead_pos.z += 3 * cosf(TO_RADIAN(m_rot.y));
			m_lifespan_count -= ATTACK_ANIM_SPEED; // 弾が消えるまでのカウントを進める

			m_now_hit_area = &hit_areas[THROW_ATTACK_HIT];

			m_cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 当たり判定を見えるようにする物
			// 向いている方向に座標を設定（今はパンチに位置）
			m_hit_cd_pos_top.set(m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
			m_hit_cd_pos_under.set(m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
			m_hit_cd_r = m_now_hit_area->hit_r;

			// カウントが一定にまで減るか、当たり判定があったら
			if (m_attack_anim_frame[m_attack_anim_pick] >= m_attack_anim_total[m_attack_anim_pick] - 30  || m_bead_hit_flag) 
			{
				m_bead_hit_flag = true;   // 弾が何かに当たったか消えたので判定をリセット
				m_attack_flag = false;    // 攻撃を終わらせておく
				m_cd_hit_flag = false;    //< 当たり判定をしてほしくないのでフラグを下す
			}

			// エフェクトの座標を設定
			SetPosPlayingEffekseer3DEffect(m_effect_handle[THROW_EFFECT], m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
		}
		break;

	case ATTACK_PUNCH_1_ANIM: // パンチ通攻撃１ 


		// 当たり判定の作成
		m_now_hit_area = &hit_areas[ATTACK_PUNCH_1_HIT];
		if (m_attack_anim_frame[ATTACK_PUNCH_1_ANIM] >= m_now_hit_area->hit_anim_frame) 
		{
			m_cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 向いている方向に座標を設定（今はパンチに位置）
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_under.z);
			m_hit_cd_r = m_now_hit_area->hit_r;

			// SEの再生
			if (!player_se.Playing_SE(SE_PUNCH_1))
			{
				player_se.Play_SE(SE_PUNCH_1, DX_PLAYTYPE_BACK, true);
			}

			// エフェクトが再生中か沿うてないかを調べる
			int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[PUNCH2_EFFECT]);
			// 再生中でなければ
			if (play_effect == -1) 
			{
				// エフェクトの再生
				m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // エフェクトの再生
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
			}
		}
		else {
			m_cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す
		}

		// エフェクトの座標を設定
		SetPosPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], m_hit_cd_pos_top.x, m_hit_cd_pos_top.y, m_hit_cd_pos_top.z);
		// アニメーションの中に
		// マウスの左クリックまたはAボタンでパンチコンボ
		if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no)) 
		{
			m_combo_flag = true;                // コンボフラグを立てる
			m_next_combo = ATTACK_PUNCH_2_ANIM; // 次の攻撃にセットする
		}

		break;


	case ATTACK_PUNCH_2_ANIM: // パンチ攻撃２（コンボ攻撃）

		// 当たり判定の作成
		m_now_hit_area = &hit_areas[ATTACK_PUNCH_2_HIT];
		if (m_attack_anim_frame[ATTACK_PUNCH_2_ANIM] >= m_now_hit_area->hit_anim_frame)
		{
			m_cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 向いている方向に座標を設定（今のパンチに位置に座標と向きをいじる）
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y - 10)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y - 10)) * m_now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 3)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 3)) * m_now_hit_area->hit_under.z);
			m_hit_cd_r = m_now_hit_area->hit_r;
			// SEの再生
			if (!player_se.Playing_SE(SE_PUNCH_2)) 
			{
				player_se.Play_SE(SE_PUNCH_2, DX_PLAYTYPE_BACK, true);
			}

			// 一回だけ再生してほしのでワンフレームだけを探す
			if (m_attack_anim_frame[ATTACK_PUNCH_2_ANIM] >= m_now_hit_area->hit_anim_frame) 
			{
				// エフェクトが再生中か沿うてないかを調べる
				int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[PUNCH2_EFFECT]);
				// 再生中でなければ
				if (play_effect == -1) 
				{
					// エフェクトの再生
					m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // エフェクトの再生
					SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる				
				}
			}
		}
		else 
		{
			m_cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す

		}
		// エフェクトの座標を設定
		SetPosPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], m_hit_cd_pos_top.x, m_hit_cd_pos_top.y, m_hit_cd_pos_top.z);

		// アニメーションの中に
		// マウスの左クリックまたはAボタンでパンチコンボ
		if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no))
		{
			m_combo_flag = true;                // コンボフラグを立てる
			m_next_combo = ATTACK_PUNCH_3_ANIM; // 次の攻撃にセットする
		}
		break;
	case ATTACK_PUNCH_3_ANIM: // パンチ攻撃3（コンボ攻撃）
		// 当たり判定の作成
		m_now_hit_area = &hit_areas[ATTACK_PUNCH_3_HIT];
		if (m_attack_anim_frame[ATTACK_PUNCH_3_ANIM] >= m_now_hit_area->hit_anim_frame) 
		{
			m_cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 向いている方向に座標を設定（今のパンチに位置に座標と向きをいじる）
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 15)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 15)) * m_now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 25)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 25)) * m_now_hit_area->hit_under.z);
			m_hit_cd_r = m_now_hit_area->hit_r;
			// SEの再生
			if (!player_se.Playing_SE(SE_PUNCH_3)) 
			{
				player_se.Play_SE(SE_PUNCH_3, DX_PLAYTYPE_BACK, true);
			}
			// エフェクトが再生中か沿うてないかを調べる
			int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[PUNCH2_EFFECT]);
			// 再生中でなければ
			if (play_effect == -1) 
			{
				// エフェクトの再生
				m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // エフェクトの再生
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
			}
		}
		else 
		{
			m_cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す
		}
		// エフェクトの座標を設定
		SetPosPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], m_hit_cd_pos_top.x, m_hit_cd_pos_top.y, m_hit_cd_pos_top.z);
		// アニメーションの中に
		// マウスの左クリックまたはAボタンでパンチコンボ
		if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no))
		{
			m_combo_flag = true;                // コンボフラグを立てる
			m_next_combo = ATTACK_PUNCH_4_ANIM; // 次の攻撃にセットする
		}
		break;
	case ATTACK_PUNCH_4_ANIM: // パンチ攻撃3（コンボ攻撃）

		// 当たり判定の作成
		m_now_hit_area = &hit_areas[ATTACK_PUNCH_4_HIT];
		if (m_attack_anim_frame[ATTACK_PUNCH_4_ANIM] >= m_now_hit_area->hit_anim_frame) 
		{
			m_cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 向いている方向に座標を設定（今のパンチに位置に座標と向きをいじる）
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 5)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 5)) * m_now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 15)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 15)) * m_now_hit_area->hit_under.z);
			m_hit_cd_r = m_now_hit_area->hit_r;
			// SEの再生
			if (!player_se.Playing_SE(SE_KICK))
			{
				player_se.Play_SE(SE_KICK, DX_PLAYTYPE_BACK, true);
			}
			// エフェクトが再生中か沿うてないかを調べる
			int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[PUNCH2_EFFECT]);
			// 再生中でなければ
			if (play_effect == -1) 
			{
				// エフェクトの再生
				m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // エフェクトの再生
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
			}
		}
		else
		{
			m_cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す
		}
		// エフェクトの座標を設定
		SetPosPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], m_hit_cd_pos_top.x, m_hit_cd_pos_top.y, m_hit_cd_pos_top.z);
		break;

	case ATTACK_WARP_ANIM: // ワープ（当たり判定の作成）
	{
		m_now_hit_area = &hit_areas[ATTACK_WARP_ANIM]; // 構造体を触りやすくするために違う変数に入れておく
		//cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

		//// 当たり判定を見えるようにする物
		//// 向いている方向に座標を設定（今はパンチに位置）
		//if (attack_anim_frame[ATTACK_WARP_ANIM] == now_hit_area->hit_anim_frame) {
		//	m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.x, m_pos.y + now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.z);
		//	m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.x, m_pos.y + now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.z);
		//}
		//else {
		//	cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す
		//}
		break;
	}

	case ATTACK_SPECIAL_ANIM: // 必殺技 (弾を出す)

		// カウントがからだったら
		if (m_lifespan_count == NULL) 
		{
			m_lifespan_count = 240.0f; // カウントのセット

		}
		// 弾用の変数
		if (m_lifespan_count >= 240.0f)
		{
			//	bead_pos = m_pos; // 一旦プレイヤーの位置にしておく（本来プレイヤーの手の位置に合わせる）
				// 座標の設定
			m_bead_pos.set(m_pos.x + 300 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 300, m_pos.z + 300 * cosf(TO_RADIAN(m_rot.y)));
			m_bead_r = 100.0f;        // 半径の設定
			m_bead_hit_flag = false;
		}
		m_bead_pos.y--;
		m_lifespan_count--; // 弾が消えるまでのカウントを進める


		//now_hit_area = &hit_areas[SPECIAL_HIT];
		// 当たり判定を見えるようにする物
		// 向いている方向に座標を設定（今はパンチに位置）
		m_hit_cd_pos_top.set(m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
		m_hit_cd_pos_under.set(m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
		m_hit_cd_r = 100;//now_hit_area->hit_r;

		m_cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

		// エフェクトが再生中かどうてないかを調べる
		int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[SPECIAL_EFFECT]);
		int play_effect2 = IsEffekseer3DEffectPlaying(m_effect_handle[SPECIAL2_EFFECT]);
		SetSpeedPlayingEffekseer3DEffect(m_effect_handle[SPECIAL_EFFECT], 1.0f);            // エフェクトの再生速度
		SetSpeedPlayingEffekseer3DEffect(m_effect_handle[SPECIAL2_EFFECT], (float)0.6);
		// 再生中でなければ
		if (play_effect == -1)
		{
			// エフェクトの再生
			m_effect_handle[SPECIAL_EFFECT] = PlayEffekseer3DEffect(m_effect_container[SPECIAL_EFFECT]); // エフェクトの再生
			SetRotationPlayingEffekseer3DEffect(m_effect_handle[SPECIAL_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
		}
		if (play_effect2 == -1)
		{
			m_effect_handle[SPECIAL2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[SPECIAL2_EFFECT]); // エフェクトの再生
			SetRotationPlayingEffekseer3DEffect(m_effect_handle[SPECIAL2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
		}
		// エフェクトの座標を設定
		SetPosPlayingEffekseer3DEffect(m_effect_handle[SPECIAL_EFFECT], m_pos.x, m_pos.y, m_pos.z);
		SetPosPlayingEffekseer3DEffect(m_effect_handle[SPECIAL2_EFFECT], m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
		// カウントが一定にまで減るか、当たり判定があったら
		if (m_lifespan_count <= 0 || m_bead_hit_flag) 
		{
			m_lifespan_count = NULL;  // 次のために空にしておく
			m_bead_hit_flag = true;  // 弾が何かに当たったか消えたので判定をリセット
			m_attack_flag = false;    // 攻撃を終わらせておく
			m_cd_hit_flag = false;    //< 当たり判定をしてほしくないのでフラグを下す
		}
		// SEの再生
		if (!player_se.Playing_SE(SE_SPECIAL)) 
		{
			player_se.Play_SE(SE_SPECIAL, DX_PLAYTYPE_BACK, true);
		}
	}
}


//---------------------------------------------------------------------------
// ダメージを食らった時用の関数(食らったダメージに合わせてアニメーションをを変える)
//---------------------------------------------------------------------------
void Player::Damage_Update(int* m_attack_damage)
{
	// 与えられたダメージによってアニメーションを変化させる
	// 今は入っている値は仮です
	if (*m_attack_damage < 60) 
	{
		m_damage_anim_pick = BLOCK_ANIM;
	}
	else if (*m_attack_damage >= 50 && *m_attack_damage < 70) 
	{
		m_damage_anim_pick = DAMAGE_ANIM_1;
	}
	else if (*m_attack_damage >= 70) 
	{
		m_damage_anim_pick = DAMAGE_ANIM_END;
	}
}

//---------------------------------------------------------------------------
// ガードをした時用の関数
//---------------------------------------------------------------------------
void Player::Block_Update()
{
	switch (m_block_anim_pick)
	{
	case BLOCK_ANIM:
		m_now_hit_area = &hit_areas[BLOCK_HIT];
		if (m_attack_anim_frame[BLOCK_HIT] <= m_now_hit_area->hit_anim_frame)
		{
			m_cd_hit_flag = true; //< 当たり判定を行っていい用にフラグを立てる

			// 当たり判定を見えるようにする物
			// 向いている方向に座標を設定（今はパンチに位置）

			m_block_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_top.z);
			m_block_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_under.z);
			m_block_r = m_now_hit_area->hit_r;


			// エフェクトが再生中かどうてないかを調べる
			int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[GUARD_EFFECT]);
			SetColorPlayingEffekseer3DEffect(m_effect_handle[GUARD_EFFECT], 0, 255, 124, 50); // エフェクトの色と透明度の設定
			SetSpeedPlayingEffekseer3DEffect(m_effect_handle[GUARD_EFFECT], 5);                      // エフェクトの再生速度
			// 再生中でなければ
			if (play_effect == -1)
			{
				// エフェクトの再生
				m_effect_handle[GUARD_EFFECT] = PlayEffekseer3DEffect(m_effect_container[GUARD_EFFECT]); // エフェクトの再生
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[GUARD_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // キャラの向いている方向にエフェクトを合わせる
			}
			// エフェクトの座標設定
			SetPosPlayingEffekseer3DEffect(m_effect_handle[GUARD_EFFECT], m_pos.x, m_pos.y, m_pos.z);

		}
		else 
		{
			m_cd_hit_flag = false; //< 当たり判定をしてほしくないのでフラグを下す
		}

		// ガードキーを離したとき
		if (IsPadRelease(PAD_ID::PAD_X, m_pad_no))
		{
			// はなししている時は
			m_block_flag = false; // 防御フラグを下す
			StopEffekseer3DEffect(m_effect_handle[GUARD_EFFECT]); // エフェクトを停止する
		}

		break;
	}
}