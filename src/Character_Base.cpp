#include "WinMain.h"
#include "GameMain.h"
#include "Base.h"
#include "Character_Base.h"



CharacterBase::CharacterBase()
{
}


//---------------------------------------------------------------------------
// 前移動
//---------------------------------------------------------------------------
void CharacterBase::Move_Front( bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
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
void CharacterBase::Move_Left( bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
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
		// 移動ベクトルのｘｚの多胎から向きを求めます
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
	if (before_pos->x + hit_size->x >= other_pos->x -other_size->x && before_pos->x - hit_size->x <= other_pos->x +other_size->x) {
		// 縦方向だけ戻す
		m_pos.z = before_pos->z;
		
	}
	if (before_pos->z + hit_size->z >= other_pos->z -other_size->z && before_pos->z - hit_size->z <= other_pos->z +other_size->z) {
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
		anim_attach[i] = MV1AttachAnim(m_model, index, anim_model[i]);             // モデルにアニメーションをアタッチ（つける）する
		anim_total[i] = MV1GetAttachAnimTotalTime(m_model, anim_attach[i]);               // 取得したアタッチ番号からそのアニメーションが何フレームかを取得
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
void CharacterBase::Attack_Anim_Init(int ATTACK_ANIM_MAX , int index)
{
	for (int i = 0; i < ATTACK_ANIM_MAX; i++)
	{
		attack_anim_attach[i] = MV1AttachAnim(m_model, index, attack_anim_model[i]);  // モデルにアニメーションをアタッチ（つける）する
		attack_anim_total[i] = MV1GetAttachAnimTotalTime(m_model, attack_anim_attach[i]);    // 取得したアタッチ番号からそのアニメーションが何フレームかを取得
		attack_anim_attach[i] = MV1DetachAnim(m_model, attack_anim_attach[i]);               // 最初は攻撃アニメーションはしないのでディタッチしておく（使いたいときにまたアタッチする）
	}
	
}

//---------------------------------------------------------------------------
// アニメーション用変数たちのdelete用関数
//---------------------------------------------------------------------------
void CharacterBase::Anim_Delete(int ANIM_MAX, int ATTACK_ANIM_MAX)
{
	for (int i = 0; i < ANIM_MAX; i++)
	{
		delete[] anim_model;
		delete[] anim_attach;
		delete[] anim_total;
		delete[] anim_rate;
		delete[] anim_frame;
	}
	for (int i = 0; i < ATTACK_ANIM_MAX; i++) {
		delete[] attack_anim_model;
		delete[] attack_anim_attach;
		delete[] attack_anim_total;
		delete[] attack_anim_rate;
		delete[] attack_anim_frame;
	}
}

//---------------------------------------------------------------------------
// 攻撃にあったアニメーションさせる関数
//---------------------------------------------------------------------------
void CharacterBase::Attack_Action(int index)
{
	anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // 攻撃アニメーションに入る前に普通アニメを外す（直近のアニメーション） 
	attack_anim_attach[attack_anim_pick] = MV1AttachAnim(m_model, index, attack_anim_model[attack_anim_pick]);      	// 使いたいアニメーションをモデルにつけなおす
	 
	m_attack_judge = true;
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

