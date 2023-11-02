#include "WinMain.h"
#include "GameMain.h"
#include "Base.h"
#include "Character_Base.h"



CharacterBase::CharacterBase()
{
}

// 前移動
void CharacterBase::Move_Front(bool* m_move_judg, bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	//　画面奥：カメラのある方向の逆の方向
	player_rot->y = camera_rot->y;
	// 動いていい
	*m_check_move = true;
	// 向いている方向に座標移動
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

// 後ろ移動
void CharacterBase::Move_Dehind(bool* m_move_judg, bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// 画面手前（カメラのある方向）
	player_rot->y = camera_rot->y + 180.0f;
	// 動いていい
	*m_check_move = true;
	// 向いている方向に座標移動
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

// 左移動
void CharacterBase::Move_Left(bool* m_move_judg, bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// 画面から見て：左
	player_rot->y = camera_rot->y - 90;
	// 動いていい
	*m_check_move = true;
	// 向いている方向に座標移動
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

// 右移動
void CharacterBase::Move_Right(bool* m_move_judg, bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// 画面から見て：右
	player_rot->y = camera_rot->y + 90;
	// 動いていい
	*m_check_move = true;
	// 向いている方向に座標移動		
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

// キャラクターの移動用関数(ゲームパッド用)
void CharacterBase::Move_GamePad(bool* m_move_judg, bool* m_check_move, Vector3* mov, Vector3* camera_rot, const float* mov_speed)
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

void CharacterBase::Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r)
{
	m_hit_other_pos = { *hit_other_x,*hit_other_z,*hit_other_r };
}

// 当たった相手の情報をもらう
void CharacterBase::Get_other(Vector3* hit_other_pos, Vector3* hit_other_size)
{
	m_hit_other_pos = *hit_other_pos;   // 座標
	m_hit_other_size = *hit_other_size; // サイズ
}
