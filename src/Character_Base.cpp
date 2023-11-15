#include "WinMain.h"
#include "GameMain.h"
#include "Base.h"
#include "Character_Base.h"



CharacterBase::CharacterBase()
{
}


//---------------------------------------------------------------------------
// �X�e�[�^�X���X�V�֐�
//---------------------------------------------------------------------------
void CharacterBase::Update_Status()
{
	// HP�o�[���U��؂�Ȃ��悤�ɂ���
	// HP���O�ɂȂ�����
	if (0 >= m_hp_count.x) {
		m_hp_count.x = 0;
	}
}

//---------------------------------------------------------------------------
// �X�e�[�^�X��`�悷��p�̊֐�
//---------------------------------------------------------------------------
void CharacterBase::Draw_Status()
{
	// HP�o�[�̕`��
	DrawBox(m_hp_pos.x, m_hp_pos.y, m_hp_pos.x + m_hp_count.x, m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(m_hp_pos.x, m_hp_pos.y, HP_MAX + m_hp_pos.x, m_hp_count.y, GetColor(255, 255, 255));
}

//---------------------------------------------------------------------------
// �v���C���[�̈ړ�������֐�
//---------------------------------------------------------------------------
void CharacterBase::Move_Player(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// �ړ����̓_�b�V������
		// �Q�[���p�b�h�̓��͏�Ԃ��Ƃ�
		//	�Q�[���p�b�h�̍��X�e�B�b�N�̒l���g���č��W�i m_pos �j�̒l��ύX
		// ���X�e�b�N�Ńv���C���[�̌�������W�̍X�V
		// �Q�[���p�b�h�̏����擾�iXINPUT �̏��j
	XINPUT_STATE input;
	// �Q�[���p�b�h�̏����ۂ��Ǝ擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	// ���X�e�B�b�N�̒l��ݒ�
	mov.x = input.ThumbLX;
	mov.z = input.ThumbLY;
	// -32768 �` 32767 ��-1.0f�@�`�@1.0f�ɂ��܂�
	mov /= 32768.0f;
	// ���̈ړ��p�x�N�g���̑傫����������x�傫���������ړ������悤�Ǝv���܂�
	if (mov.GetLength() > 0.5f) {
		CharacterBase::Move_GamePad(m_check_move, &mov, camera_rot, mov_speed);
	}
	// WASD�L�[�Ńv���C���[�̈ړ�
	if (CheckHitKey(KEY_INPUT_W)) // ��ړ�
	{
		Move_Front(m_check_move, camera_rot, player_rot, mov_speed);
	}
	if (CheckHitKey(KEY_INPUT_S)) // ���ړ�
	{
		Move_Dhindo(m_check_move, camera_rot, player_rot, mov_speed);
	}
	if (CheckHitKey(KEY_INPUT_A)) // ���ړ�
	{
		Move_Left(m_check_move, camera_rot, player_rot, mov_speed);
	}
	if (CheckHitKey(KEY_INPUT_D)) // �E�ړ�
	{
		Move_Right(m_check_move, camera_rot, player_rot, mov_speed);
	}
}

//---------------------------------------------------------------------------
// �O�ړ�
//---------------------------------------------------------------------------
void CharacterBase::Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	//�@��ʉ��F�J�����̂�������̋t�̕���
	player_rot->y = camera_rot->y;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

//---------------------------------------------------------------------------
// ���ړ�
//---------------------------------------------------------------------------
void CharacterBase::Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// ��ʎ�O�i�J�����̂�������j
	player_rot->y = camera_rot->y + 180.0f;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

//---------------------------------------------------------------------------
// ���ړ�
//---------------------------------------------------------------------------
void CharacterBase::Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// ��ʂ��猩�āF��
	player_rot->y = camera_rot->y - 90;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

//---------------------------------------------------------------------------
// �E�ړ�
//---------------------------------------------------------------------------
void CharacterBase::Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed)
{
	// ��ʂ��猩�āF�E
	player_rot->y = camera_rot->y + 90;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�		
	m_pos.x += *mov_speed * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += *mov_speed * cosf(TO_RADIAN(m_rot.y));
}

//---------------------------------------------------------------------------
// �L�����N�^�[�̈ړ��p�֐�(�Q�[���p�b�h�p)
//---------------------------------------------------------------------------
void CharacterBase::Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, const float* mov_speed)
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

//---------------------------------------------------------------------------
// �L�����N�^�[�̕ǎC��p�֐�
//---------------------------------------------------------------------------
void CharacterBase::Move_Hit(Vector3* before_pos, Vector3* hit_size, Vector3* other_pos, Vector3* other_size)
{
	if (before_pos->x + hit_size->x >= other_pos->x - other_size->x && before_pos->x - hit_size->x <= other_pos->x + other_size->x) {
		// �c���������߂�
		m_pos.z = before_pos->z;
	}
	if (before_pos->z + hit_size->z >= other_pos->z - other_size->z && before_pos->z - hit_size->z <= other_pos->z + other_size->z) {
		// �c���������߂�
		m_pos.x = before_pos->x;
	}
}

//---------------------------------------------------------------------------
// ���ʃA�j���[�V�����ϐ���New�p�֐�
//---------------------------------------------------------------------------
void CharacterBase::Nomal_Anim_New(int ANIM_MAX)
{
	anim_model = new int[ANIM_MAX];   // �A�j���[�V�������f��
	anim_attach = new int[ANIM_MAX];  // �A�^�b�`�p�ϐ�
	anim_total = new float[ANIM_MAX]; // �A�j���[�V���������t���[�����邩
	anim_rate = new float[ANIM_MAX];  // �A�j���[�V�����̃u�����h��
	anim_frame = new float[ANIM_MAX]; // �A�j���[�V�����̐i�߂�t���[��
	// �A�j���[�V���������t���[���i��ł��邩�p�̕ϐ�
	// �ŏ��͂O����J�n
	for (int i = 0; i < ANIM_MAX; i++)
	{
		anim_frame[i] = 0.0f;
	}
}

//---------------------------------------------------------------------------
// ���ʃA�j���[�V�����̏����ݒ�(�A�j���[�V�����̃A�^�b�`����ŏ��̃u�����h���̒����܂ł��s��)
//---------------------------------------------------------------------------
void CharacterBase::Nomal_Anim_Init(int ANIM_IDLE, int ANIM_MAX, int index)
{
	for (int i = 0; i < ANIM_MAX; i++)
	{
		anim_attach[i] = MV1AttachAnim(m_model, index, anim_model[i]);             // ���f���ɃA�j���[�V�������A�^�b�`�i����j����
		anim_total[i] = MV1GetAttachAnimTotalTime(m_model, anim_attach[i]);               // �擾�����A�^�b�`�ԍ����炻�̃A�j���[�V���������t���[�������擾
		// �s�K�v�Ȃ��̂ɂ̓u�����h����0.0f�ɂ��Ă����i�ŏ��̓A�C�h���ɂ��Ă����j
		if (i != ANIM_IDLE)  // �A�C�h���ȊO�̃A�j���[�V���������f������O��
		{
			anim_rate[i] = 0.0f;
		}
		else {
			anim_rate[i] = 1.0f;
		}
	}
}

//---------------------------------------------------------------------------
// �U���A�j���[�V�����ϐ���New�p�֐�
//---------------------------------------------------------------------------
void CharacterBase::Attack_Anim_New(int ATTACK_ANIM_MAX)
{
	attack_anim_model = new int[ATTACK_ANIM_MAX];   // �A�j���[�V�������f��
	attack_anim_attach = new int[ATTACK_ANIM_MAX];  // �A�^�b�`�p�ϐ�
	attack_anim_total = new float[ATTACK_ANIM_MAX]; // �A�j���[�V���������t���[�����邩
	attack_anim_rate = new float[ATTACK_ANIM_MAX];  // �A�j���[�V�����̃u�����h��
	attack_anim_frame = new float[ATTACK_ANIM_MAX]; // �A�j���[�V�����̐i�߂�t���[��
	// �A�j���[�V���������t���[���i��ł��邩�p�̕ϐ�
	// �ŏ��͂O����J�n
	for (int i = 0; i < ATTACK_ANIM_MAX; i++)
	{
		attack_anim_frame[i] = 0.0f;
	}
}

//---------------------------------------------------------------------------
// �U���A�j���[�V�����̏����ݒ�(�A�^�b�`����ŏ��̃f�B�^�b�`�܂ł��s��)
//---------------------------------------------------------------------------
void CharacterBase::Attack_Anim_Init(int ATTACK_ANIM_MAX, int index)
{
	for (int i = 0; i < ATTACK_ANIM_MAX; i++)
	{
		attack_anim_attach[i] = MV1AttachAnim(m_model, index, attack_anim_model[i]);  // ���f���ɃA�j���[�V�������A�^�b�`�i����j����
		attack_anim_total[i] = MV1GetAttachAnimTotalTime(m_model, attack_anim_attach[i]);    // �擾�����A�^�b�`�ԍ����炻�̃A�j���[�V���������t���[�������擾
		attack_anim_attach[i] = MV1DetachAnim(m_model, attack_anim_attach[i]);               // �ŏ��͍U���A�j���[�V�����͂��Ȃ��̂Ńf�B�^�b�`���Ă����i�g�������Ƃ��ɂ܂��A�^�b�`����j
	}
}

//---------------------------------------------------------------------------
// �A�j���[�V�����p�ϐ�������delete�p�֐�
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
// �U���ɂ������A�j���[�V����������֐�
//---------------------------------------------------------------------------
void CharacterBase::Attack_Action(int index)
{
	anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // �U���A�j���[�V�����ɓ���O�ɕ��ʃA�j�����O���i���߂̃A�j���[�V�����j 
	attack_anim_attach[attack_anim_pick] = MV1AttachAnim(m_model, index, attack_anim_model[attack_anim_pick]);      	// �g�������A�j���[�V���������f���ɂ��Ȃ���

	m_attack_judge = true;
}

//---------------------------------------------------------------------------
// ������������̏������炤(�J�v�Z��, �~)
//---------------------------------------------------------------------------
void CharacterBase::Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r)
{
	m_hit_other_pos = { *hit_other_x,*hit_other_z,*hit_other_r };
}

//---------------------------------------------------------------------------
// ������������̏������炤(������)
//---------------------------------------------------------------------------
void CharacterBase::Get_other(Vector3* hit_other_pos, Vector3* hit_other_size)
{
	m_hit_other_pos = *hit_other_pos;   // ���W
	m_hit_other_size = *hit_other_size; // �T�C�Y
}

//---------------------------------------------------------------------------
// �����蔻������֐�
//---------------------------------------------------------------------------
void CharacterBase::Attack_Hit_New(Vector3* pot_pos, Vector3* under_pos)
{
	hit_pos_pot;
	hit_pos_under;
	// �����蔻���������悤�ɂ��镨
	// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
	m_hit_attack_pos_top.set(m_pos.x + pot_pos->x * sinf(TO_RADIAN(m_rot.y)), m_pos.y + pot_pos->y, m_pos.z + pot_pos->z * cosf(TO_RADIAN(m_rot.y)));
	m_hit_attack_pos_under.set(m_pos.x + under_pos->x * sinf(TO_RADIAN(m_rot.y)), m_pos.y + under_pos->y, m_pos.z + under_pos->z * cosf(TO_RADIAN(m_rot.y)));
}

