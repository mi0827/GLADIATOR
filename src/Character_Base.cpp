#include "WinMain.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Base.h"
#include "InputPad.h"
#include "Character_Base.h"


const int MAX_ = 3;
CharacterBase::CharacterBase()
{
	// HP
	m_hp_pos.set(SCREEN_W / 50.0, SCREEN_H / 20.0);           // HPバーの描画位置初期化
	m_hp_count.set(HP_MAX, m_hp_pos.y + STATUS_BAR_SIZE);   // HPの計算用の初期化
	m_now_hp = HP_MAX;                    // 最初は体力マックス      
	// SP
	m_sp_pos.set(SCREEN_W / (float)50.0, SCREEN_H / (float)1.3);		   	 // SPのクールダウンバーの描画位置初期化
	m_sp_count.set((float)0, m_sp_pos.y + STATUS_BAR_SIZE); // SPのクールダウンバーの計算用の初期化
	// スキル
	m_skill_pos.set(SCREEN_W / (float)50.0, SCREEN_H / (float)1.1);			    // スキルのクールダウンバーの描画位置初期化
	m_skill_count.set((float)0, m_skill_pos.y + STATUS_BAR_SIZE);// スキルのクールダウンバーの計算用の初期化

}

//---------------------------------------------------------------------------
// ステータスを更新関数
//---------------------------------------------------------------------------
void CharacterBase::Update_Status()
{
	// HPバーが振り切れないようにする
	// HPが０になったら
	if (0 >= m_hp_count.x) 
	{
		m_hp_count.x = 0;
	}
	m_now_hp = m_hp_count.x; // わかりやすくするために入れる

	skill_flame_count++; // フレームカウントを増やす
	// スキルクールダウンのカウントを増やす
	if (skill_flame_count % 60 == 0) 
	{
		m_skill_count.x += 30;
	}
	// スキルポイントがたまったら
	if (m_skill_count.x >= SKILL_POINT_MAX) 
	{
		m_skill_count.x  = SKILL_POINT_MAX;
		skill_flag = true; // スキルを使用できるようにする
	}
	m_now_skill = m_skill_count.x; // わかりやすくするために入れる

	sp_flame_count++; // フレームカウントを増やす
	// SPクールダウンのカウントを増やす
	if (sp_flame_count % 60 == 0) 
	{
		// SPバーのカウントを増やす
		m_sp_count.x += 40;
	}

	// SPポイントがたまったら
	if (m_sp_count.x >= SP_POINT_MAX) 
	{
		m_sp_count.x = SP_POINT_MAX;
		sp_flag = true; // 必殺技を使用できるようにする
	}
	m_now_sp = m_sp_count.x; // わかりやすくするために入れる
}

//---------------------------------------------------------------------------
//  ステータスのリセット用関数
//---------------------------------------------------------------------------
void CharacterBase::Reset_Status()
{
	m_skill_count.x = 0; // スキルポイントを戻す
	skill_flag = false;   // スキルを使用できないようにする
	m_sp_count.x = 0;    // SPポイントを戻す
	sp_flag = false;     // 必殺技を使できないようにする
}

//---------------------------------------------------------------------------
// ステータスを描画する用の関数
//---------------------------------------------------------------------------
void CharacterBase::Draw_Status(int player_num)
{
	// 文字の最初の大きさをとっておく
	int original_font_size = GetFontSize();
	SetFontSize(SCREEN_H / 27);
	int hp_x    = SCREEN_W / (int)10.5 + HP_MAX;
	int skill_x = SCREEN_W / (int)3.3  + SKILL_POINT_MAX;
	int sp_x    = SCREEN_W / (int)4.0  + SP_POINT_MAX;
	const char* skill = "スキル";
	// 描画幅の取得
	float skill_w = (float)GetDrawStringWidth(skill, -1);
	const char* sp = "SP";
	// 描画幅の取得
	float sp_w = (float)GetDrawStringWidth(sp, -1);

	// HPバーの描画
	if (player_num == 0) 
	{
		// SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 描画するものを半透明にする
		DrawBox(    (int)m_hp_pos.x ,                (int)m_hp_pos.y,   (int)(m_hp_pos.x + m_hp_count.x), (int)m_hp_count.y, GetColor(  0, 255,   0), TRUE); // 本体バー
		DrawBox(   (int)(m_hp_pos.x + m_hp_count.x), (int)m_hp_count.y, (int)(HP_MAX + m_hp_pos.x),       (int)m_hp_pos.y,   GetColor(255,  20,  20), TRUE); // 余白バー
		DrawLineBox((int)m_hp_pos.x ,                (int)m_hp_pos.y,   (int)(HP_MAX + m_hp_pos.x),       (int)m_hp_count.y, GetColor(255, 255, 255));               // 外枠
		// スキルクールダウンバーの描画
		DrawString((int)m_skill_pos.x, (int)m_skill_pos.y - SCREEN_H / (int)27, skill, GetColor(255, 255, 255));
		DrawBox(   (int)m_skill_pos.x ,                    (int) m_skill_pos.y,   (int)(m_skill_pos.x + m_skill_count.x), (int)m_skill_count.y, GetColor(  0, 191, 255), TRUE); // 本体バー
		DrawBox(   (int)(m_skill_pos.x + m_skill_count.x), (int) m_skill_count.y, (int)(SKILL_POINT_MAX + m_skill_pos.x), (int)m_skill_pos.y,   GetColor(105, 105, 105), TRUE); // 余白バー
		DrawLineBox((int)m_skill_pos.x,                    (int)m_skill_pos.y,    (int)(SKILL_POINT_MAX + m_skill_pos.x), (int)m_skill_count.y, GetColor(255, 255, 255));	    // 外枠
		// SPバーの描画
		DrawString( (int)m_sp_pos.x , (int)(m_sp_pos.y - SCREEN_H / 27), sp, GetColor(255, 255, 255));
		DrawBox(    (int)m_sp_pos.x ,                   (int)m_sp_pos.y,   (int)(m_sp_pos.x + m_sp_count.x), (int)m_sp_count.y, GetColor(255, 215,   0), TRUE); // 本体バー
		DrawBox(    (int)(m_sp_pos.x  + m_sp_count.x),  (int)m_sp_count.y, (int)(SP_POINT_MAX + m_sp_pos.x), (int)m_sp_pos.y,   GetColor(105, 105, 105), TRUE); // 余白バー
		DrawLineBox((int)m_sp_pos.x ,                   (int)m_sp_pos.y,   (int)(SP_POINT_MAX + m_sp_pos.x), (int)m_sp_count.y, GetColor(255, 255, 255));		         // 外枠
	}
	else 
	{
		DrawBox(    (int)(m_hp_pos.x + hp_x - HP_MAX), (int)m_hp_count.y,   (int)(hp_x + m_hp_pos.x),               (int)m_hp_pos.y,   GetColor(255, 20,   20), TRUE); // 余白バー
		DrawBox(    (int)(m_hp_pos.x + hp_x),          (int)m_hp_pos.y,     (int)(m_hp_pos.x + hp_x - m_hp_count.x),(int)m_hp_count.y, GetColor(  0, 255,   0), TRUE); // 本体バー
		DrawLineBox((int)(m_hp_pos.x + hp_x - HP_MAX), (int)m_hp_pos.y,     (int)(hp_x + m_hp_pos.x),               (int)m_hp_count.y, GetColor(255, 255, 255));               // 外枠
		// スキルクールダウンバーの描画
		DrawString(  (int)(m_skill_pos.x + skill_x - skill_w),        (int)(m_skill_pos.y - SCREEN_H / 27), skill, GetColor(255, 255, 255));
		DrawBox(     (int)(m_skill_pos.x + skill_x),                  (int)m_skill_pos.y,   (int)(m_skill_pos.x + skill_x - m_skill_count.x), (int)m_skill_count.y, GetColor(  0, 191, 255), TRUE); // 本体バー
		DrawBox(     (int)(m_skill_pos.x + skill_x - SKILL_POINT_MAX),(int)m_skill_count.y, (int)(m_skill_pos.x + skill_x - m_skill_count.x), (int)m_skill_pos.y,   GetColor(105, 105, 105), TRUE); // 余白バー
		DrawLineBox( (int)(m_skill_pos.x + skill_x - SKILL_POINT_MAX),(int)m_skill_pos.y,   (int)(skill_x + m_skill_pos.x),                   (int)m_skill_count.y, GetColor(255, 255, 255));	    // 外枠
		// SPバーの描画
		DrawString( (int)(m_sp_pos.x + sp_x - sp_w), (int)(m_sp_pos.y - SCREEN_H / 27), sp, GetColor(255, 255, 255));
		DrawBox(    (int)(m_sp_pos.x + sp_x - SP_POINT_MAX), (int)m_sp_count.y, (int)(m_sp_pos.x + sp_x - m_sp_count.x), (int)m_sp_pos.y,   GetColor(105, 105, 105), TRUE);  // 余白バー
		DrawBox(    (int)(m_sp_pos.x + sp_x),                (int)m_sp_pos.y,   (int)(m_sp_pos.x + sp_x - m_sp_count.x), (int)m_sp_count.y, GetColor(255, 215,   0), TRUE);  // 本体バー
		DrawLineBox((int)(m_sp_pos.x + sp_x - SP_POINT_MAX), (int)m_sp_pos.y,   (int)(sp_x + m_sp_pos.x),                (int)m_sp_count.y, GetColor(255, 255, 255));		          // 外枠
	}
	SetFontSize(original_font_size);
}

//---------------------------------------------------------------------------
// プレイヤーの移動をする関数
//---------------------------------------------------------------------------
void CharacterBase::Move_Player(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// 移動中はダッシュする
		// ゲームパッドの入力状態をとる
		//	ゲームパッドの左スティックの値を使って座標（ m_pos ）の値を変更
		// 左ステックでプレイヤーの向きや座標の更新
		// ゲームパッドの情報を取得（XINPUT の情報）
	XINPUT_STATE input = { {'\0'}, '\0','\0',0,0,0,0 };
	// ゲームパッドの情報を丸ごと取得
	//GetJoypadXInputState(DX_INPUT_PAD1, &input);
	// GetJoypadXInputState((int) pad_no, &input);

	//GetJoypadXInputState((int)((PAD_NO)pad_no), &input);
	switch (pad_no)
	{
	case PAD_NO::PAD_NO1:
		GetJoypadXInputState(DX_INPUT_PAD1, &input);
		break;
	case PAD_NO::PAD_NO2:
		GetJoypadXInputState(DX_INPUT_PAD2, &input);
		break;
	case PAD_NO::PAD_NO3:
		GetJoypadXInputState(DX_INPUT_PAD3, &input);
		break;
	case PAD_NO::PAD_NO4:
		GetJoypadXInputState(DX_INPUT_PAD4, &input);
		break;
	}
	
	// 左スティックの値を設定
	mov.x = input.ThumbLX;
	mov.z = input.ThumbLY;
	// -32768 ～ 32767 を-1.0f　～　1.0fにします
	mov /= 32768.0f;
	// この移動用ベクトルの大きさがある程度大きい時だけ移動させようと思います
	if (mov.GetLength() > 0.5f) 
	{
		Move_GamePad(m_check_move, &mov, camera_rot, mov_speed);
	}
	// WASDキーでプレイヤーの移動
	if (CheckHitKey(KEY_INPUT_W)) // 上移動
	{
		Move_Front(m_check_move, camera_rot, player_rot, mov_speed);
	}
	if (CheckHitKey(KEY_INPUT_S)) // 下移動
	{
		Move_Dhindo(m_check_move, camera_rot, player_rot, mov_speed);
	}
	if (CheckHitKey(KEY_INPUT_A)) // 左移動
	{
		Move_Left(m_check_move, camera_rot, player_rot, mov_speed);
	}
	if (CheckHitKey(KEY_INPUT_D)) // 右移動
	{
		Move_Right(m_check_move, camera_rot, player_rot, mov_speed);
	}
}

//---------------------------------------------------------------------------
// 前移動
//---------------------------------------------------------------------------
void CharacterBase::Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	//　画面奥：カメラのある方向の逆の方向
	player_rot->y = camera_rot->y;
	// 動いていい
	*m_check_move = true;
	// 向いている方向に座標移動
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

//---------------------------------------------------------------------------
// 後ろ移動
//---------------------------------------------------------------------------
void CharacterBase::Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// 画面手前（カメラのある方向）
	player_rot->y = camera_rot->y + 180.0f;
	// 動いていい
	*m_check_move = true;
	// 向いている方向に座標移動
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

//---------------------------------------------------------------------------
// 左移動
//---------------------------------------------------------------------------
void CharacterBase::Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// 画面から見て：左
	player_rot->y = camera_rot->y - 90;
	// 動いていい
	*m_check_move = true;
	// 向いている方向に座標移動
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

//---------------------------------------------------------------------------
// 右移動
//---------------------------------------------------------------------------
void CharacterBase::Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// 画面から見て：右
	player_rot->y = camera_rot->y + 90;
	// 動いていい
	*m_check_move = true;
	// 向いている方向に座標移動		
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

//---------------------------------------------------------------------------
// キャラクターの移動用関数(ゲームパッド用)
//---------------------------------------------------------------------------
void CharacterBase::Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, const float* mov_speed)
{
	*m_check_move = true; // 動いていい
	// 向いている方向に座標移動
	// 当たり判定がある時は座標移動をしない
	//	そのベクトルを回転させるための行列を作成します。
	MATRIX mat_y = MGetRotY(TO_RADIAN(camera_rot->y));
	//	その行列を使ってベクトルを回転させます。
	*mov = GetVector3VTransform(*mov, mat_y);
	// 移動ベクトルのｘｚのから向きを求めます
	m_rot.y = TO_DEGREE(atan2f(mov->x, mov->z));
	// 移動ベクトルの大きさを PLAYER_MOV_SPEED のおおきさにします
	mov->SetLength(*mov_speed);
	// その移動ベクトル分座標移動
	m_pos += *mov;
}

//---------------------------------------------------------------------------
// キャラクターの壁擦り用関数
//---------------------------------------------------------------------------
void CharacterBase::Move_Hit(Vector3* before_pos, Vector3* hit_size, Vector3* other_pos, Vector3* other_size)
{
	if (before_pos->x + hit_size->x >= other_pos->x - other_size->x && before_pos->x - hit_size->x <= other_pos->x + other_size->x)
	{
		// 縦方向だけ戻す
		m_pos.z = before_pos->z;
	}
	if (before_pos->z + hit_size->z >= other_pos->z - other_size->z && before_pos->z - hit_size->z <= other_pos->z + other_size->z) 
	{
		// 縦方向だけ戻す
		m_pos.x = before_pos->x;
	}
}

//---------------------------------------------------------------------------
// 普通アニメーション変数のNew用関数
//---------------------------------------------------------------------------
void CharacterBase::Nomal_Anim_New(int ANIM_MAX)
{
	anim_model = new int[ANIM_MAX];   // アニメーションモデル
	anim_attach = new int[ANIM_MAX];  // アタッチ用変数
	anim_total = new float[ANIM_MAX]; // アニメーションが何フレームあるか
	anim_rate = new float[ANIM_MAX];  // アニメーションのブレンド率
	anim_frame = new float[ANIM_MAX]; // アニメーションの進めるフレーム

	// アニメーションが何フレーム進んでいるか用の変数
	// 最初は０から開始
	for (int i = 0; i < ANIM_MAX; i++)
	{
		anim_frame[i] = 0.0f;
	}
}
//---------------------------------------------------------------------------
// 普通アニメーションの初期設定(アニメーションのアタッチから最初のブレンド率の調整までを行う)
//---------------------------------------------------------------------------
void CharacterBase::Nomal_Anim_Init(int ANIM_IDLE, int ANIM_MAX, int index)
{
	for (int i = 0; i < ANIM_MAX; i++)
	{
		anim_attach[i] = MV1AttachAnim(m_model, index, anim_model[i]);         // モデルにアニメーションをアタッチ（つける）する
		anim_total[i] = MV1GetAttachAnimTotalTime(m_model, anim_attach[i]);    // 取得したアタッチ番号からそのアニメーションが何フレームかを取得
		anim_rate[i] = MV1GetAttachAnimBlendRate(m_model, anim_attach[i]);     // ブレンド率の取得
		// 不必要なものにはブレンド率を0.0fにしておく（最初はアイドルにしておく）
		if (i != ANIM_IDLE)  // アイドル以外のアニメーションをモデルから外す
		{
			anim_rate[i] = 0.0f;
		}
		else {
			anim_rate[i] = 1.0f;
		}
	}
}

//---------------------------------------------------------------------------
// 攻撃アニメーション変数のNew用関数
//---------------------------------------------------------------------------
void CharacterBase::Attack_Anim_New(int ATTACK_ANIM_MAX)
{
	attack_anim_model = new int[ATTACK_ANIM_MAX];   // アニメーションモデル
	attack_anim_attach = new int[ATTACK_ANIM_MAX];  // アタッチ用変数
	attack_anim_total = new float[ATTACK_ANIM_MAX]; // アニメーションが何フレームあるか
	attack_anim_rate = new float[ATTACK_ANIM_MAX];  // アニメーションのブレンド率
	attack_anim_frame = new float[ATTACK_ANIM_MAX]; // アニメーションの進めるフレーム
	// アニメーションが何フレーム進んでいるか用の変数
	// 最初は０から開始
	for (int i = 0; i < ATTACK_ANIM_MAX; i++)
	{
		attack_anim_frame[i] = 0.0f;
	}
}
//---------------------------------------------------------------------------
// 攻撃アニメーションの初期設定(アタッチから最初のディタッチまでを行う)
//---------------------------------------------------------------------------
void CharacterBase::Attack_Anim_Init(int ATTACK_ANIM_MAX, int index)
{
	for (int i = 0; i < ATTACK_ANIM_MAX; i++)
	{
		attack_anim_attach[i] = MV1AttachAnim(m_model, index, attack_anim_model[i]);  // モデルにアニメーションをアタッチ（つける）する
		attack_anim_total[i] = MV1GetAttachAnimTotalTime(m_model, attack_anim_attach[i]);        // 取得したアタッチ番号からそのアニメーションが何フレームかを取得
		attack_anim_rate[i] = MV1GetAttachAnimBlendRate(m_model, attack_anim_attach[i]);         // ブレンド率の取得
		attack_anim_attach[i] = MV1DetachAnim(m_model, attack_anim_attach[i]);                   // 最初は攻撃アニメーションはしないのでディタッチしておく（使いたいときにまたアタッチする）
	}
}
//---------------------------------------------------------------------------
// 攻撃にあったアニメーションさせる関数
//---------------------------------------------------------------------------
void CharacterBase::Attack_Action(int index)
{
	//// アニメーションの再生
	anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // 攻撃アニメーションに入る前に普通アニメを外す（直近のアニメーション） 
	attack_anim_attach[attack_anim_pick] = MV1AttachAnim(m_model, index, attack_anim_model[attack_anim_pick]); // 使いたいアニメーションをモデルにつけなおす
	attack_flag = true; // 攻撃中にする
}


//---------------------------------------------------------------------------
// ダメージアニメーション変数のNew用関数
//---------------------------------------------------------------------------
void CharacterBase::Damage_Anim_New(int DAMAGE_ANIM_MAX)
{
	damage_anim_model  = new int[DAMAGE_ANIM_MAX];   // アニメーションモデル
	damage_anim_attach = new int[DAMAGE_ANIM_MAX];   // アタッチ用変数
	damage_anim_total  = new float[DAMAGE_ANIM_MAX]; // アニメーションが何フレームあるか
	damage_anim_rate   = new float[DAMAGE_ANIM_MAX]; // アニメーションのブレンド率
	damage_anim_frame  = new float[DAMAGE_ANIM_MAX]; // アニメーションの進めるフレーム
	// アニメーションが何フレーム進んでいるか用の変数
	// 最初は０から開始
	for (int i = 0; i < DAMAGE_ANIM_MAX; i++)
	{
		damage_anim_frame[i] = 0.0f;
	}
}
//---------------------------------------------------------------------------
// ダメージアニメーションの初期設定(アタッチから最初のディタッチまでを行う)
//---------------------------------------------------------------------------
void CharacterBase::Damage_Anim_Init(int DAMAGE_ANIM_MAX, int index)
{
	for (int i = 0; i < DAMAGE_ANIM_MAX; i++)
	{
		damage_anim_attach[i] = MV1AttachAnim(m_model, index, damage_anim_model[i]);  // モデルにアニメーションをアタッチ（つける）する
		damage_anim_total[i] = MV1GetAttachAnimTotalTime(m_model, damage_anim_attach[i]);        // 取得したアタッチ番号からそのアニメーションが何フレームかを取得
		damage_anim_rate[i] = MV1GetAttachAnimBlendRate(m_model, damage_anim_attach[i]);         // ブレンド率の取得
		damage_anim_attach[i] = MV1DetachAnim(m_model, damage_anim_attach[i]);                   // 最初は攻撃アニメーションはしないのでディタッチしておく（使いたいときにまたアタッチする）
	}
}
//---------------------------------------------------------------------------
// ダメージアニメーションにあったアニメーションさせる関数
//---------------------------------------------------------------------------
void CharacterBase::Damage_Action(int index)
{
	anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // 攻撃アニメーションに入る前に普通アニメを外す（直近のアニメーション） 
	damage_anim_attach[damage_anim_pick] = MV1AttachAnim(m_model, index, damage_anim_model[damage_anim_pick]);      	// 使いたいアニメーションをモデルにつけなおす
	// damage_flag = true; // 攻撃中にする
}


//---------------------------------------------------------------------------
// ガードアニメーション変数のNew用関数
//---------------------------------------------------------------------------
void CharacterBase::Block_Anim_New(int BLOCK_ANIM_MAX)
{
	block_anim_model  = new int[BLOCK_ANIM_MAX];   // アニメーションモデル
	block_anim_attach = new int[BLOCK_ANIM_MAX];   // アタッチ用変数
	block_anim_total  = new float[BLOCK_ANIM_MAX]; // アニメーションが何フレームあるか
	block_anim_rate   = new float[BLOCK_ANIM_MAX]; // アニメーションのブレンド率
	block_anim_frame  = new float[BLOCK_ANIM_MAX]; // アニメーションの進めるフレーム
	// アニメーションが何フレーム進んでいるか用の変数
	// 最初は０から開始
	for (int i = 0; i < BLOCK_ANIM_MAX; i++)
	{
		block_anim_frame[i] = 0.0f;
	}
}
//---------------------------------------------------------------------------
// ガードアニメーションの初期設定(アタッチから最初のディタッチまでを行う)
//---------------------------------------------------------------------------
void CharacterBase::Block_Anim_Init(int BLOCK_ANIM_MAX, int index)
{
	for (int i = 0; i < BLOCK_ANIM_MAX; i++)
	{
		block_anim_attach[i] = MV1AttachAnim(m_model, index, block_anim_model[i]);   // モデルにアニメーションをアタッチ（つける）する
		block_anim_total[i] =  MV1GetAttachAnimTotalTime(m_model, block_anim_attach[i]);        // 取得したアタッチ番号からそのアニメーションが何フレームかを取得
		block_anim_attach[i] = MV1DetachAnim(m_model, block_anim_attach[i]);                    // 最初は攻撃アニメーションはしないのでディタッチしておく（使いたいときにまたアタッチする）
	}
}
//---------------------------------------------------------------------------
// ガードアニメーションにあったアニメーションさせる関数
//---------------------------------------------------------------------------
void CharacterBase::Block_Action(int index)
{
	anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // 攻撃アニメーションに入る前に普通アニメを外す（直近のアニメーション） 
	block_anim_attach[block_anim_pick] = MV1AttachAnim(m_model, index, block_anim_model[block_anim_pick]); // 使いたいアニメーションをモデルにつけなおす
	block_flag = true; // 防御フラグを上げる
}


//---------------------------------------------------------------------------
// アニメーション用変数たちのdelete用関数
//---------------------------------------------------------------------------
void CharacterBase::Anim_Delete()
{
	//! 普通アニメーション 
	delete[] anim_model;
	delete[] anim_attach;
	delete[] anim_total;
	delete[] anim_rate;
	delete[] anim_frame;
	// 攻撃アニメーション
	delete[] attack_anim_model;
	delete[] attack_anim_attach;
	delete[] attack_anim_total;
	delete[] attack_anim_rate;
	delete[] attack_anim_frame;
	// ダメージアニメーション
	delete[] damage_anim_model;
	delete[] damage_anim_attach;
	delete[] damage_anim_total;
	delete[] damage_anim_rate;
	delete[] damage_anim_frame;
	// ガードアニメーション
	delete[] block_anim_model;
	delete[] block_anim_attach;
	delete[] block_anim_total;
	delete[] block_anim_rate;
	delete[] block_anim_frame;
}

//---------------------------------------------------------------------------
// 当たった相手の情報をもらう(カプセル, 円)
//---------------------------------------------------------------------------
void CharacterBase::Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r)
{
	m_hit_other_pos = { *hit_other_x,*hit_other_z,*hit_other_r };
}

//---------------------------------------------------------------------------
// 当たった相手の情報をもらう(立方体)
//---------------------------------------------------------------------------
void CharacterBase::Get_other(Vector3* hit_other_pos, Vector3* hit_other_size)
{

	m_hit_other_pos = *hit_other_pos;   // 座標
	m_hit_other_size = *hit_other_size; // サイズ

}

//---------------------------------------------------------------------------
// 当たり判定を作る関数(カプセル型、円型)
//---------------------------------------------------------------------------
void CharacterBase::Attack_Hit_New(Vector3* pot_pos, Vector3* under_pos)
{
	hit_pos_pot;
	hit_pos_under;
	// 当たり判定を見えるようにする物
	// 向いている方向に座標を設定（今はパンチに位置）
	m_hit_cd_pos_top.set(m_pos.x + pot_pos->x * sinf(TO_RADIAN(m_rot.y)), m_pos.y + pot_pos->y, m_pos.z + pot_pos->z * cosf(TO_RADIAN(m_rot.y)));
	m_hit_cd_pos_under.set(m_pos.x + under_pos->x * sinf(TO_RADIAN(m_rot.y)), m_pos.y + under_pos->y, m_pos.z + under_pos->z * cosf(TO_RADIAN(m_rot.y)));
}

//---------------------------------------------------------------------------
// 攻撃力を保存する用の関数
//---------------------------------------------------------------------------
void CharacterBase::Set_Attack_Damage(int ATTACK_ANIM_MAX, const int* attack_damage)
{
	m_attack_damage = new int[ATTACK_ANIM_MAX];
	for (int i = 0; i < ATTACK_ANIM_MAX; i++) {
		m_attack_damage[i] = attack_damage[i];
	}
}

//---------------------------------------------------------------------------
// delete用の関数
//---------------------------------------------------------------------------
void CharacterBase::Delete()
{
	Anim_Delete(); // アニメーションのdelete用の関数
	delete[] m_attack_damage; // 攻撃ダメージの解放
}

