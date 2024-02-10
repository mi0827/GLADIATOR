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
	m_hp_pos.set(SCREEN_W / 50.0, SCREEN_H / 20.0);           // HP�o�[�̕`��ʒu������
	m_hp_count.set(HP_MAX, m_hp_pos.y + STATUS_BAR_SIZE);   // HP�̌v�Z�p�̏�����
	m_now_hp = HP_MAX;                    // �ŏ��̗͑̓}�b�N�X      
	// SP
	m_sp_pos.set(SCREEN_W / (float)50.0, SCREEN_H / (float)1.3);		   	 // SP�̃N�[���_�E���o�[�̕`��ʒu������
	m_sp_count.set((float)0, m_sp_pos.y + STATUS_BAR_SIZE); // SP�̃N�[���_�E���o�[�̌v�Z�p�̏�����
	// �X�L��
	m_skill_pos.set(SCREEN_W / (float)50.0, SCREEN_H / (float)1.1);			    // �X�L���̃N�[���_�E���o�[�̕`��ʒu������
	m_skill_count.set((float)0, m_skill_pos.y + STATUS_BAR_SIZE);// �X�L���̃N�[���_�E���o�[�̌v�Z�p�̏�����

}

//---------------------------------------------------------------------------
// �X�e�[�^�X���X�V�֐�
//---------------------------------------------------------------------------
void CharacterBase::Update_Status()
{
	// HP�o�[���U��؂�Ȃ��悤�ɂ���
	// HP���O�ɂȂ�����
	if (0 >= m_hp_count.x) 
	{
		m_hp_count.x = 0;
	}
	m_now_hp = m_hp_count.x; // �킩��₷�����邽�߂ɓ����

	skill_flame_count++; // �t���[���J�E���g�𑝂₷
	// �X�L���N�[���_�E���̃J�E���g�𑝂₷
	if (skill_flame_count % 60 == 0) 
	{
		m_skill_count.x += 30;
	}
	// �X�L���|�C���g�����܂�����
	if (m_skill_count.x >= SKILL_POINT_MAX) 
	{
		m_skill_count.x  = SKILL_POINT_MAX;
		skill_flag = true; // �X�L�����g�p�ł���悤�ɂ���
	}
	m_now_skill = m_skill_count.x; // �킩��₷�����邽�߂ɓ����

	sp_flame_count++; // �t���[���J�E���g�𑝂₷
	// SP�N�[���_�E���̃J�E���g�𑝂₷
	if (sp_flame_count % 60 == 0) 
	{
		// SP�o�[�̃J�E���g�𑝂₷
		m_sp_count.x += 40;
	}

	// SP�|�C���g�����܂�����
	if (m_sp_count.x >= SP_POINT_MAX) 
	{
		m_sp_count.x = SP_POINT_MAX;
		sp_flag = true; // �K�E�Z���g�p�ł���悤�ɂ���
	}
	m_now_sp = m_sp_count.x; // �킩��₷�����邽�߂ɓ����
}

//---------------------------------------------------------------------------
//  �X�e�[�^�X�̃��Z�b�g�p�֐�
//---------------------------------------------------------------------------
void CharacterBase::Reset_Status()
{
	m_skill_count.x = 0; // �X�L���|�C���g��߂�
	skill_flag = false;   // �X�L�����g�p�ł��Ȃ��悤�ɂ���
	m_sp_count.x = 0;    // SP�|�C���g��߂�
	sp_flag = false;     // �K�E�Z���g�ł��Ȃ��悤�ɂ���
}

//---------------------------------------------------------------------------
// �X�e�[�^�X��`�悷��p�̊֐�
//---------------------------------------------------------------------------
void CharacterBase::Draw_Status(int player_num)
{
	// �����̍ŏ��̑傫�����Ƃ��Ă���
	int original_font_size = GetFontSize();
	SetFontSize(SCREEN_H / 27);
	int hp_x    = SCREEN_W / (int)10.5 + HP_MAX;
	int skill_x = SCREEN_W / (int)3.3  + SKILL_POINT_MAX;
	int sp_x    = SCREEN_W / (int)4.0  + SP_POINT_MAX;
	const char* skill = "�X�L��";
	// �`�敝�̎擾
	float skill_w = (float)GetDrawStringWidth(skill, -1);
	const char* sp = "SP";
	// �`�敝�̎擾
	float sp_w = (float)GetDrawStringWidth(sp, -1);

	// HP�o�[�̕`��
	if (player_num == 0) 
	{
		// SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // �`�悷����̂𔼓����ɂ���
		DrawBox(    (int)m_hp_pos.x ,                (int)m_hp_pos.y,   (int)(m_hp_pos.x + m_hp_count.x), (int)m_hp_count.y, GetColor(  0, 255,   0), TRUE); // �{�̃o�[
		DrawBox(   (int)(m_hp_pos.x + m_hp_count.x), (int)m_hp_count.y, (int)(HP_MAX + m_hp_pos.x),       (int)m_hp_pos.y,   GetColor(255,  20,  20), TRUE); // �]���o�[
		DrawLineBox((int)m_hp_pos.x ,                (int)m_hp_pos.y,   (int)(HP_MAX + m_hp_pos.x),       (int)m_hp_count.y, GetColor(255, 255, 255));               // �O�g
		// �X�L���N�[���_�E���o�[�̕`��
		DrawString((int)m_skill_pos.x, (int)m_skill_pos.y - SCREEN_H / (int)27, skill, GetColor(255, 255, 255));
		DrawBox(   (int)m_skill_pos.x ,                    (int) m_skill_pos.y,   (int)(m_skill_pos.x + m_skill_count.x), (int)m_skill_count.y, GetColor(  0, 191, 255), TRUE); // �{�̃o�[
		DrawBox(   (int)(m_skill_pos.x + m_skill_count.x), (int) m_skill_count.y, (int)(SKILL_POINT_MAX + m_skill_pos.x), (int)m_skill_pos.y,   GetColor(105, 105, 105), TRUE); // �]���o�[
		DrawLineBox((int)m_skill_pos.x,                    (int)m_skill_pos.y,    (int)(SKILL_POINT_MAX + m_skill_pos.x), (int)m_skill_count.y, GetColor(255, 255, 255));	    // �O�g
		// SP�o�[�̕`��
		DrawString( (int)m_sp_pos.x , (int)(m_sp_pos.y - SCREEN_H / 27), sp, GetColor(255, 255, 255));
		DrawBox(    (int)m_sp_pos.x ,                   (int)m_sp_pos.y,   (int)(m_sp_pos.x + m_sp_count.x), (int)m_sp_count.y, GetColor(255, 215,   0), TRUE); // �{�̃o�[
		DrawBox(    (int)(m_sp_pos.x  + m_sp_count.x),  (int)m_sp_count.y, (int)(SP_POINT_MAX + m_sp_pos.x), (int)m_sp_pos.y,   GetColor(105, 105, 105), TRUE); // �]���o�[
		DrawLineBox((int)m_sp_pos.x ,                   (int)m_sp_pos.y,   (int)(SP_POINT_MAX + m_sp_pos.x), (int)m_sp_count.y, GetColor(255, 255, 255));		         // �O�g
	}
	else 
	{
		DrawBox(    (int)(m_hp_pos.x + hp_x - HP_MAX), (int)m_hp_count.y,   (int)(hp_x + m_hp_pos.x),               (int)m_hp_pos.y,   GetColor(255, 20,   20), TRUE); // �]���o�[
		DrawBox(    (int)(m_hp_pos.x + hp_x),          (int)m_hp_pos.y,     (int)(m_hp_pos.x + hp_x - m_hp_count.x),(int)m_hp_count.y, GetColor(  0, 255,   0), TRUE); // �{�̃o�[
		DrawLineBox((int)(m_hp_pos.x + hp_x - HP_MAX), (int)m_hp_pos.y,     (int)(hp_x + m_hp_pos.x),               (int)m_hp_count.y, GetColor(255, 255, 255));               // �O�g
		// �X�L���N�[���_�E���o�[�̕`��
		DrawString(  (int)(m_skill_pos.x + skill_x - skill_w),        (int)(m_skill_pos.y - SCREEN_H / 27), skill, GetColor(255, 255, 255));
		DrawBox(     (int)(m_skill_pos.x + skill_x),                  (int)m_skill_pos.y,   (int)(m_skill_pos.x + skill_x - m_skill_count.x), (int)m_skill_count.y, GetColor(  0, 191, 255), TRUE); // �{�̃o�[
		DrawBox(     (int)(m_skill_pos.x + skill_x - SKILL_POINT_MAX),(int)m_skill_count.y, (int)(m_skill_pos.x + skill_x - m_skill_count.x), (int)m_skill_pos.y,   GetColor(105, 105, 105), TRUE); // �]���o�[
		DrawLineBox( (int)(m_skill_pos.x + skill_x - SKILL_POINT_MAX),(int)m_skill_pos.y,   (int)(skill_x + m_skill_pos.x),                   (int)m_skill_count.y, GetColor(255, 255, 255));	    // �O�g
		// SP�o�[�̕`��
		DrawString( (int)(m_sp_pos.x + sp_x - sp_w), (int)(m_sp_pos.y - SCREEN_H / 27), sp, GetColor(255, 255, 255));
		DrawBox(    (int)(m_sp_pos.x + sp_x - SP_POINT_MAX), (int)m_sp_count.y, (int)(m_sp_pos.x + sp_x - m_sp_count.x), (int)m_sp_pos.y,   GetColor(105, 105, 105), TRUE);  // �]���o�[
		DrawBox(    (int)(m_sp_pos.x + sp_x),                (int)m_sp_pos.y,   (int)(m_sp_pos.x + sp_x - m_sp_count.x), (int)m_sp_count.y, GetColor(255, 215,   0), TRUE);  // �{�̃o�[
		DrawLineBox((int)(m_sp_pos.x + sp_x - SP_POINT_MAX), (int)m_sp_pos.y,   (int)(sp_x + m_sp_pos.x),                (int)m_sp_count.y, GetColor(255, 255, 255));		          // �O�g
	}
	SetFontSize(original_font_size);
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
	XINPUT_STATE input = { {'\0'}, '\0','\0',0,0,0,0 };
	// �Q�[���p�b�h�̏����ۂ��Ǝ擾
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
	
	// ���X�e�B�b�N�̒l��ݒ�
	mov.x = input.ThumbLX;
	mov.z = input.ThumbLY;
	// -32768 �` 32767 ��-1.0f�@�`�@1.0f�ɂ��܂�
	mov /= 32768.0f;
	// ���̈ړ��p�x�N�g���̑傫����������x�傫���������ړ������悤�Ǝv���܂�
	if (mov.GetLength() > 0.5f) 
	{
		Move_GamePad(m_check_move, &mov, camera_rot, mov_speed);
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
	// �ړ��x�N�g���̂����̂�����������߂܂�
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
	if (before_pos->x + hit_size->x >= other_pos->x - other_size->x && before_pos->x - hit_size->x <= other_pos->x + other_size->x)
	{
		// �c���������߂�
		m_pos.z = before_pos->z;
	}
	if (before_pos->z + hit_size->z >= other_pos->z - other_size->z && before_pos->z - hit_size->z <= other_pos->z + other_size->z) 
	{
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
		anim_attach[i] = MV1AttachAnim(m_model, index, anim_model[i]);         // ���f���ɃA�j���[�V�������A�^�b�`�i����j����
		anim_total[i] = MV1GetAttachAnimTotalTime(m_model, anim_attach[i]);    // �擾�����A�^�b�`�ԍ����炻�̃A�j���[�V���������t���[�������擾
		anim_rate[i] = MV1GetAttachAnimBlendRate(m_model, anim_attach[i]);     // �u�����h���̎擾
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
		attack_anim_total[i] = MV1GetAttachAnimTotalTime(m_model, attack_anim_attach[i]);        // �擾�����A�^�b�`�ԍ����炻�̃A�j���[�V���������t���[�������擾
		attack_anim_rate[i] = MV1GetAttachAnimBlendRate(m_model, attack_anim_attach[i]);         // �u�����h���̎擾
		attack_anim_attach[i] = MV1DetachAnim(m_model, attack_anim_attach[i]);                   // �ŏ��͍U���A�j���[�V�����͂��Ȃ��̂Ńf�B�^�b�`���Ă����i�g�������Ƃ��ɂ܂��A�^�b�`����j
	}
}
//---------------------------------------------------------------------------
// �U���ɂ������A�j���[�V����������֐�
//---------------------------------------------------------------------------
void CharacterBase::Attack_Action(int index)
{
	//// �A�j���[�V�����̍Đ�
	anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // �U���A�j���[�V�����ɓ���O�ɕ��ʃA�j�����O���i���߂̃A�j���[�V�����j 
	attack_anim_attach[attack_anim_pick] = MV1AttachAnim(m_model, index, attack_anim_model[attack_anim_pick]); // �g�������A�j���[�V���������f���ɂ��Ȃ���
	attack_flag = true; // �U�����ɂ���
}


//---------------------------------------------------------------------------
// �_���[�W�A�j���[�V�����ϐ���New�p�֐�
//---------------------------------------------------------------------------
void CharacterBase::Damage_Anim_New(int DAMAGE_ANIM_MAX)
{
	damage_anim_model  = new int[DAMAGE_ANIM_MAX];   // �A�j���[�V�������f��
	damage_anim_attach = new int[DAMAGE_ANIM_MAX];   // �A�^�b�`�p�ϐ�
	damage_anim_total  = new float[DAMAGE_ANIM_MAX]; // �A�j���[�V���������t���[�����邩
	damage_anim_rate   = new float[DAMAGE_ANIM_MAX]; // �A�j���[�V�����̃u�����h��
	damage_anim_frame  = new float[DAMAGE_ANIM_MAX]; // �A�j���[�V�����̐i�߂�t���[��
	// �A�j���[�V���������t���[���i��ł��邩�p�̕ϐ�
	// �ŏ��͂O����J�n
	for (int i = 0; i < DAMAGE_ANIM_MAX; i++)
	{
		damage_anim_frame[i] = 0.0f;
	}
}
//---------------------------------------------------------------------------
// �_���[�W�A�j���[�V�����̏����ݒ�(�A�^�b�`����ŏ��̃f�B�^�b�`�܂ł��s��)
//---------------------------------------------------------------------------
void CharacterBase::Damage_Anim_Init(int DAMAGE_ANIM_MAX, int index)
{
	for (int i = 0; i < DAMAGE_ANIM_MAX; i++)
	{
		damage_anim_attach[i] = MV1AttachAnim(m_model, index, damage_anim_model[i]);  // ���f���ɃA�j���[�V�������A�^�b�`�i����j����
		damage_anim_total[i] = MV1GetAttachAnimTotalTime(m_model, damage_anim_attach[i]);        // �擾�����A�^�b�`�ԍ����炻�̃A�j���[�V���������t���[�������擾
		damage_anim_rate[i] = MV1GetAttachAnimBlendRate(m_model, damage_anim_attach[i]);         // �u�����h���̎擾
		damage_anim_attach[i] = MV1DetachAnim(m_model, damage_anim_attach[i]);                   // �ŏ��͍U���A�j���[�V�����͂��Ȃ��̂Ńf�B�^�b�`���Ă����i�g�������Ƃ��ɂ܂��A�^�b�`����j
	}
}
//---------------------------------------------------------------------------
// �_���[�W�A�j���[�V�����ɂ������A�j���[�V����������֐�
//---------------------------------------------------------------------------
void CharacterBase::Damage_Action(int index)
{
	anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // �U���A�j���[�V�����ɓ���O�ɕ��ʃA�j�����O���i���߂̃A�j���[�V�����j 
	damage_anim_attach[damage_anim_pick] = MV1AttachAnim(m_model, index, damage_anim_model[damage_anim_pick]);      	// �g�������A�j���[�V���������f���ɂ��Ȃ���
	// damage_flag = true; // �U�����ɂ���
}


//---------------------------------------------------------------------------
// �K�[�h�A�j���[�V�����ϐ���New�p�֐�
//---------------------------------------------------------------------------
void CharacterBase::Block_Anim_New(int BLOCK_ANIM_MAX)
{
	block_anim_model  = new int[BLOCK_ANIM_MAX];   // �A�j���[�V�������f��
	block_anim_attach = new int[BLOCK_ANIM_MAX];   // �A�^�b�`�p�ϐ�
	block_anim_total  = new float[BLOCK_ANIM_MAX]; // �A�j���[�V���������t���[�����邩
	block_anim_rate   = new float[BLOCK_ANIM_MAX]; // �A�j���[�V�����̃u�����h��
	block_anim_frame  = new float[BLOCK_ANIM_MAX]; // �A�j���[�V�����̐i�߂�t���[��
	// �A�j���[�V���������t���[���i��ł��邩�p�̕ϐ�
	// �ŏ��͂O����J�n
	for (int i = 0; i < BLOCK_ANIM_MAX; i++)
	{
		block_anim_frame[i] = 0.0f;
	}
}
//---------------------------------------------------------------------------
// �K�[�h�A�j���[�V�����̏����ݒ�(�A�^�b�`����ŏ��̃f�B�^�b�`�܂ł��s��)
//---------------------------------------------------------------------------
void CharacterBase::Block_Anim_Init(int BLOCK_ANIM_MAX, int index)
{
	for (int i = 0; i < BLOCK_ANIM_MAX; i++)
	{
		block_anim_attach[i] = MV1AttachAnim(m_model, index, block_anim_model[i]);   // ���f���ɃA�j���[�V�������A�^�b�`�i����j����
		block_anim_total[i] =  MV1GetAttachAnimTotalTime(m_model, block_anim_attach[i]);        // �擾�����A�^�b�`�ԍ����炻�̃A�j���[�V���������t���[�������擾
		block_anim_attach[i] = MV1DetachAnim(m_model, block_anim_attach[i]);                    // �ŏ��͍U���A�j���[�V�����͂��Ȃ��̂Ńf�B�^�b�`���Ă����i�g�������Ƃ��ɂ܂��A�^�b�`����j
	}
}
//---------------------------------------------------------------------------
// �K�[�h�A�j���[�V�����ɂ������A�j���[�V����������֐�
//---------------------------------------------------------------------------
void CharacterBase::Block_Action(int index)
{
	anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // �U���A�j���[�V�����ɓ���O�ɕ��ʃA�j�����O���i���߂̃A�j���[�V�����j 
	block_anim_attach[block_anim_pick] = MV1AttachAnim(m_model, index, block_anim_model[block_anim_pick]); // �g�������A�j���[�V���������f���ɂ��Ȃ���
	block_flag = true; // �h��t���O���グ��
}


//---------------------------------------------------------------------------
// �A�j���[�V�����p�ϐ�������delete�p�֐�
//---------------------------------------------------------------------------
void CharacterBase::Anim_Delete()
{
	//! ���ʃA�j���[�V���� 
	delete[] anim_model;
	delete[] anim_attach;
	delete[] anim_total;
	delete[] anim_rate;
	delete[] anim_frame;
	// �U���A�j���[�V����
	delete[] attack_anim_model;
	delete[] attack_anim_attach;
	delete[] attack_anim_total;
	delete[] attack_anim_rate;
	delete[] attack_anim_frame;
	// �_���[�W�A�j���[�V����
	delete[] damage_anim_model;
	delete[] damage_anim_attach;
	delete[] damage_anim_total;
	delete[] damage_anim_rate;
	delete[] damage_anim_frame;
	// �K�[�h�A�j���[�V����
	delete[] block_anim_model;
	delete[] block_anim_attach;
	delete[] block_anim_total;
	delete[] block_anim_rate;
	delete[] block_anim_frame;
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
// �����蔻������֐�(�J�v�Z���^�A�~�^)
//---------------------------------------------------------------------------
void CharacterBase::Attack_Hit_New(Vector3* pot_pos, Vector3* under_pos)
{
	hit_pos_pot;
	hit_pos_under;
	// �����蔻���������悤�ɂ��镨
	// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
	m_hit_cd_pos_top.set(m_pos.x + pot_pos->x * sinf(TO_RADIAN(m_rot.y)), m_pos.y + pot_pos->y, m_pos.z + pot_pos->z * cosf(TO_RADIAN(m_rot.y)));
	m_hit_cd_pos_under.set(m_pos.x + under_pos->x * sinf(TO_RADIAN(m_rot.y)), m_pos.y + under_pos->y, m_pos.z + under_pos->z * cosf(TO_RADIAN(m_rot.y)));
}

//---------------------------------------------------------------------------
// �U���͂�ۑ�����p�̊֐�
//---------------------------------------------------------------------------
void CharacterBase::Set_Attack_Damage(int ATTACK_ANIM_MAX, const int* attack_damage)
{
	m_attack_damage = new int[ATTACK_ANIM_MAX];
	for (int i = 0; i < ATTACK_ANIM_MAX; i++) {
		m_attack_damage[i] = attack_damage[i];
	}
}

//---------------------------------------------------------------------------
// delete�p�̊֐�
//---------------------------------------------------------------------------
void CharacterBase::Delete()
{
	Anim_Delete(); // �A�j���[�V������delete�p�̊֐�
	delete[] m_attack_damage; // �U���_���[�W�̉��
}

