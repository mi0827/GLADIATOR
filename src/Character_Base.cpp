#include "WinMain.h"
#include "GameMain.h"
#include "Base.h"
#include "Character_Base.h"



CharacterBase::CharacterBase()
{
}

// �O�ړ�
void CharacterBase::Move_Front(bool* m_move_judg, bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	//�@��ʉ��F�J�����̂�������̋t�̕���
	player_rot->y = camera_rot->y;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

// ���ړ�
void CharacterBase::Move_Dehind(bool* m_move_judg, bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// ��ʎ�O�i�J�����̂�������j
	player_rot->y = camera_rot->y + 180.0f;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

// ���ړ�
void CharacterBase::Move_Left(bool* m_move_judg, bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// ��ʂ��猩�āF��
	player_rot->y = camera_rot->y - 90;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

// �E�ړ�
void CharacterBase::Move_Right(bool* m_move_judg, bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// ��ʂ��猩�āF�E
	player_rot->y = camera_rot->y + 90;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�		
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

// �L�����N�^�[�̈ړ��p�֐�(�Q�[���p�b�h�p)
void CharacterBase::Move_GamePad(bool* m_move_judg, bool* m_check_move, Vector3* mov, Vector3* camera_rot, const float* mov_speed)
{
	*m_check_move = true; // �����Ă���
	// �����Ă�������ɍ��W�ړ�
	// �����蔻�肪���鎞�͍��W�ړ������Ȃ�
	
		//	���̃x�N�g������]�����邽�߂̍s����쐬���܂��B
		MATRIX mat_y = MGetRotY(TO_RADIAN(camera_rot->y));
		//	���̍s����g���ăx�N�g������]�����܂��B
		*mov = GetVector3VTransform(*mov, mat_y);
		// �ړ��x�N�g���̂����̑��ق�����������߂܂�
		m_rot.y = TO_DEGREE(atan2f(mov->x, mov->z));
		// �ړ��x�N�g���̑傫���� PLAYER_MOV_SPEED �̂��������ɂ��܂�
		mov->SetLength(*mov_speed);
		// ���̈ړ��x�N�g�������W�ړ�
		m_pos += *mov;
	
}

void CharacterBase::Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r)
{
	m_hit_other_pos = { *hit_other_x,*hit_other_z,*hit_other_r };
}

// ������������̏������炤
void CharacterBase::Get_other(Vector3* hit_other_pos, Vector3* hit_other_size)
{
	m_hit_other_pos = *hit_other_pos;   // ���W
	m_hit_other_size = *hit_other_size; // �T�C�Y
}
