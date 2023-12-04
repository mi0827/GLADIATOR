#include "WinMain.h"
#include "GameMain.h"
#include "Ninja.h"

#define PANEL_SIZE	5.0f              // �p�l���̑傫��
#define PANEL_HALF	(PANEL_SIZE/2.0f) // �p�l���̔����̑傫��


// �R���X�g���N�^�i�������j
Ninja::Ninja()
{
	m_pos.set(0.0f, 0.0f, 0.0f);             // �������W�̐ݒ�
	m_rot.set(0.0f, 0.0f, 0.0f);             // �����̐ݒ�
	before_mov.set(m_pos);                       // �ŏ��͍ŏ��̍��W�����Ƃ�

	anim_num = 0;                                     // �ŏ��͂O�΂�̃A�j���[�V����������
	action_mode = 0;                                  // �ŏ��͕��ʃA�j���[�V�������[�h�ɂ��Ă���
	attack_anim_pick = -1;                            // �ŏ��͂Ȃ�̃A�j���[�V�����������Ă��Ȃ�
	m_check_move = false;                             // �ŏ��͑����Ă����Ȃ�

	//------------------------------
	// �����蔻��p�ϐ�

	//=============
	// �J�v�Z��
	m_hit_body_pos_top.clear();                       // �㑤
	m_hit_body_pos_under.clear();                     // ����
	m_hit_body_r = 2.0f;                              // ���a
	//======================
	// �ړ��p�̃{�b�N�X                                                   
	m_move_hit_box_size.set(PANEL_HALF - 0.1, PANEL_HALF - 0.1, PANEL_HALF - 0.1);    // �p�l���̑傫��

	// ���f�p�A�t���O�ϐ�
	m_move_judge = false;     // �ŏ��͓����Ă͂����Ȃ�
	bead_hit_judg = false;    // �Ȃɂɂ��������ĂȂ�
	attack_flag = false;  // �U�����Ă��Ȃ�
	damage_flag = false;  // ���_���[�W���󂯂Ă���̂�
	block_flag = false;   // ���K�[�h���Ȃ̂�


	m_hp_pos.set(10, 32);         // HP�o�[�̕`��ʒu������
	m_hp_count.set(HP_MAX, 32 + 30);   // HP�̌v�Z�p�̏�����
}

// ��������
void Ninja::Init(int player_num)
{
	m_model = MV1LoadModel("Data/Model/Ninja/Ninja.mv1");   // �v���C���[���f���̓ǂݍ���
	Animation_Init(); //< �A�j���[�V�����̐ݒ�

	//pad_input = GetJoypadInputState(DX_INPUT_PAD3);  // �Q�[���p�b�h�̓ǂݍ���

	if (player_num == 0) {
		m_pos.set(0.0f, 0.0f, -50.0f);           // �������W�̐ݒ�
		m_rot.set(0.0f, 0.0f, 0.0f);             // �����̐ݒ�
	}
	else {
		m_pos.set(0.0f, 0.0f, 500.0f);            // �������W�̐ݒ�
		m_rot.set(0.0f, 180.0f, 0.0f);			  // �����̐ݒ�
	}

	//// ��
	//SetPadNo(DX_INPUT_PAD1);
}

//---------------------------------------------------------------------------
// �A�j���[�V�����p�̏�������
//---------------------------------------------------------------------------
void Ninja::Animation_Init()
{
	// ���ʃA�j���[�V�����̏�����
	// �A�j���[�V�����̓ǂݍ���
	CharacterBase::Nomal_Anim_New(ANIM_MAX);  // ���ʃA�j���[�V�����ɕK�v�ȕϐ��̔z������
	anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Ninja/Animation/Idle.mv1"); // �A�C�h��
	anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Ninja/Animation/Run.mv1");   // ����
	CharacterBase::Nomal_Anim_Init(ANIM_IDLE, ANIM_MAX, 0); // ���ʃA�j���[�V�����̏����ݒ�

	// �U���A�j���[�V�����̏�����
	// �A�j���[�V�����̓ǂݍ���
	CharacterBase::Attack_Anim_New(ATTACK_ANIM_MAX); // �U���A�j���[�V�����ɕK�v�ȕϐ��̔z������
	attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Ninja/Animation/Attack/long_normal_attack.mv1");       // ���������ʍU��
	attack_anim_model[ATTACK_SHORT_NORMAL_1_ANIM] = MV1LoadModel("Data/Model/Ninja/Animation/Attack/Punch.mv1"); // �ߋ����U���P
	attack_anim_model[ATTACK_SLIDE_ANIM] = MV1LoadModel("Data/Model/Ninja/Animation/Attack/slide.mv1");                          // �X���C�f�B���O
	attack_anim_model[ATTACK_SPECIAL_ANIM] = MV1LoadModel("Data/Model/Ninja/Animation/Attack/special_attack.mv1");               // �K�E�Z
	CharacterBase::Attack_Anim_Init(ATTACK_ANIM_MAX, 0); // �U���A�j���[�V�����̏����ݒ�
}

// �X�V����
void Ninja::Update(Vector3* camera_rot, bool status_flag)
{
	before_mov = m_pos; // �ړ������O�ɓ���ւ��Ƃ�

	// �A�N�V�������[�h�̔��f���Ă���ɍ��������������悤�ɂ���
	switch (action_mode)
	{
	case NORMAL_ACTION:        // ���ʃA�N�V���� 
		m_check_move = false;  // ��Ƀ��Z�b�g

		// �ړ����̓_�b�V������
		// �Q�[���p�b�h�̓��͏�Ԃ��Ƃ�
		//	�Q�[���p�b�h�̍��X�e�B�b�N�̒l���g���č��W�i m_pos �j�̒l��ύX
		// ���X�e�b�N�Ńv���C���[�̌�������W�̍X�V
		// �Q�[���p�b�h�̏����擾�iXINPUT �̏��j
		XINPUT_STATE input;
		// �Q�[���p�b�h�̏����ۂ��Ǝ擾
		//GetJoypadXInputState(DX_INPUT_PAD2, &input);
		GetJoypadXInputState((int)pad_no, &input);


		// ���X�e�B�b�N�̒l��ݒ�
		mov.x = input.ThumbLX;
		mov.z = input.ThumbLY;
		// -32768 �` 32767 ��-1.0f�@�`�@1.0f�ɂ��܂�
		mov /= 32768.0f;
		// ���̈ړ��p�x�N�g���̑傫����������x�傫���������ړ������悤�Ǝv���܂�
		if (mov.GetLength() > 0.5f) {
			CharacterBase::Move_GamePad(&m_check_move, &mov, camera_rot, &MOVE_SPEED);
		}

		// �ړ������܂͂�߂Ă���
		// �ړ�����
		CharacterBase::Move_Player(&m_check_move, camera_rot, &m_rot, &MOVE_SPEED);


		// �ړ����Ȃ�A�j���[�V�����̕ύX�Ɠ����蔻��̈ړ�
		if (m_check_move) {

			anim_num = ANIM_RUN;  // �ړ����Ȃ̂ő���A�j���[�V������
			{                     // �v���C���[���W�ɓ����蔻��p�̃J�v�Z���̈ʒu�����킹��
				m_hit_body_pos_top = m_pos;
				m_hit_body_pos_top.y += 17.0f; // �������o��
				m_hit_body_pos_under = m_pos;
				m_hit_body_pos_under.y += 3.0f;
			}
		}
		else {                           // �ǂ̈ړ��L�[��������ĂȂ�������
			anim_num = ANIM_IDLE;        // �A�C�h����Ԃɂ���
			{                            // �v���C���[���W�ɓ����蔻��p�̃J�v�Z���̈ʒu�����킹��
				m_hit_body_pos_top = m_pos;
				m_hit_body_pos_top.y += 17.0f; // �������o��
				m_hit_body_pos_under = m_pos;
				m_hit_body_pos_under.y += 3.0f;

			}
		}

		//=================================
		// �ߋ����U��
		//=================================
		// �}�E�X�̍��N���b�N�܂���A�{�^���ŋߋ����U��
		if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, pad_no)) {
			action_mode = ATTACK_ACTION;                    // ���f���̃A�N�V�������U���ɕύX
			attack_anim_pick = ATTACK_SHORT_NORMAL_1_ANIM;  // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(0);                 // �s�������U���A�j���[�V�������Z�b�g

			break;
		}

		//=================================
		// �������U��
		//=================================
		// �}�E�X�̉E�N���b�N�A�܂��́AY�{�^���ŉ������U��
		if (PushMouseInput(MOUSE_INPUT_RIGHT) || IsPadOn(PAD_ID::PAD_Y, pad_no)) {
			action_mode = ATTACK_ACTION;                 // ���f���̃A�N�V�������U���ɕύX
			attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(0);              // �s�������U���A�j���[�V�������Z�b�g
			break;
		}

		//=================================
		// �X���C�f�B���O
		//=================================
		// �X�y�[�X�L�[�N���b�N�A�܂��́AB�{�^���ŉ������U��
		if (PushHitKey(KEY_INPUT_SPACE) || IsPadOn(PAD_ID::PAD_B, pad_no)) {
			action_mode = ATTACK_ACTION;           // ���f���̃A�N�V�������U���ɕύX
			attack_anim_pick = ATTACK_SLIDE_ANIM;  // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(0);        // �s�������U���A�j���[�V�������Z�b�g
			break;
		}


		//=================================
		// �K�E�Z
		//=================================
		// �w E�L�[ �{ Q�L�[ �x�N���b�N�A�܂��́A�w R�{�^�� + L�{�^�� �x�ŕK�E�Z�U��
		if (PushHitKey(KEY_INPUT_E) && PushHitKey(KEY_INPUT_Q) || IsPadOn(PAD_ID::PAD_L, pad_no) && IsPadOn(PAD_ID::PAD_R, pad_no)) {
			action_mode = ATTACK_ACTION;             // ���f���̃A�N�V�������U���ɕύX
			attack_anim_pick = ATTACK_SPECIAL_ANIM;  // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(0);          // �s�������U���A�j���[�V�������Z�b�g
			break;
		}

		// �A�j���[�V�����p�̃t���[���J�E���g��i�߂�
		for (int i = 0; i < ANIM_MAX; ++i) {
			anim_frame[i] += 1.0f;
			if (anim_frame[i] >= anim_total[i]) {
				anim_frame[i] = 0.0f;
			}
			// �A�j���[�V�����̍Đ�
			// �g�������Ȃ��A�j���[�V����
			if (i != anim_num) {

				anim_rate[i] -= 0.1f; // ���������炷
			}
			else {// �g�������A�j���[�V����		
				anim_rate[i] += 0.1f; // �����𑝂₷
			}

			anim_rate[i] = max(0.0f, min(anim_rate[i], 1.0f));                                    // ������0.0f �` 1.0f�ɂ���i��������Ȃ��Ɨx�苶���j 
			MV1SetAttachAnimTime(m_model, anim_attach[i], anim_frame[i]);  // ���̃t���[���̃A�j���[�V�����ɂ���
			MV1SetAttachAnimBlendRate(m_model, anim_attach[i], anim_rate[i]);   // ���ꂼ��ɃA�j���[�V�����̊������Đ����܂�
		}
		break;

	case ATTACK_ACTION: // �U���A�N�V����
		// �A�j���[�V�����̍Đ�
		// �U���A�j���[�V�����p�̃t���[���J�E���g��i�߂�
		attack_anim_frame[attack_anim_pick]++;
		if (attack_anim_frame[attack_anim_pick] >= attack_anim_total[attack_anim_pick]) { // �A�j���[�V���������������
			attack_anim_frame[attack_anim_pick] = 0.0f;
			attack_anim_attach[attack_anim_pick] = MV1DetachAnim(m_model, attack_anim_attach[attack_anim_pick]);  // �U���A�j���[�V�������f�B�^�b�`���Ă���
			anim_attach[anim_num] = MV1AttachAnim(m_model, 0, anim_model[anim_num]);                   // ���f���Ɍ��̃A�j���[�V�������A�^�b�`���Ȃ����i���߂̃A�j���[�V�����j
			action_mode = NORMAL_ACTION; 	// �A�j���[�V�������P���[�v������rATTACK_ACTION����o��
			// �U�����I������̂ł����������Ă��Ȃ��悤�ɂ���
			// attack_hlag = false;
		}
		MV1SetAttachAnimTime(m_model, attack_anim_attach[attack_anim_pick], attack_anim_frame[attack_anim_pick]); // �A�j���[�V�����̍Đ�
		break;
	}


	if (attack_flag) {

		// �e�p�̕ϐ�
		if (lifespan_count >= 120.0f) {
			bead_pos = new Vector3;
			*bead_pos = m_pos; // ��U�v���C���[�̈ʒu�ɂ��Ă����i�{���v���C���[�̎�̈ʒu�ɍ��킹��j
			bead_pos->y += 10.0f; // y���W�����炵�ċ󒆂ɕ����ׂ�
		}
		// ��U�O�ɔ�΂�
		bead_pos->x += 3 * sinf(TO_RADIAN(m_rot.y));
		bead_pos->z += 3 * cosf(TO_RADIAN(m_rot.y));
		lifespan_count--; // �e��������܂ł̃J�E���g��i�߂�

		// �J�E���g�����ɂ܂Ō��邩�A�����蔻�肪��������
		if (lifespan_count <= 0 || bead_hit_judg) {
			delete bead_pos; // �e�̉��
			bead_pos = NULL;
			lifespan_count = 120.0f; // �J�E���g�̃��Z�b�g
			attack_flag = false; // �U�����I��点�Ă���
		}
	}
	// �X�e�[�^�X�̍X�V����
	CharacterBase::Update_Status();
}

//---------------------------------------------------------------------------
// �v���C���[�̈ړ��p�����蔻��i�ǎC��j
//---------------------------------------------------------------------------
void  Ninja::Move_Hit_Update()
{
	CharacterBase::Move_Hit(&before_mov, &m_move_hit_box_size, &m_hit_other_pos, &m_hit_other_size);
}

void Ninja::Attack_PressButton_Update(Vector3* camera_rot)
{
}

void Ninja::Attack_Update()
{
}

void Ninja::Damage_Update()
{
}

void Ninja::Block_Update()
{
}

//---------------------------------------------------------------------------
// �X�e�[�^�X�`�揈��
//---------------------------------------------------------------------------
// CharacterBase::Draw_Status();


// �`�揈��
void Ninja::Draw()
{
	// �ʂ�`�悷��(������)
	if (bead_pos != NULL) {
		DrawSphere3D(bead_pos->VGet(), 2.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	// �����蔻���������悤�ɂ��镨
	Vector3 draw_box_pos;
	draw_box_pos = m_pos + m_move_hit_box_pos;
	Vector3 draw_box_size;
	draw_box_size = m_pos + m_move_hit_box_pos + m_move_hit_box_size;
	DrawCube3D(draw_box_pos.VGet(), draw_box_size.VGet(), GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);

	// �v���C���[�̕`��ݒ�
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));                                             // �`�悷��v���C���[���f���̍��W�̐ݒ�
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y + 180), TO_RADIAN(m_rot.z)));   // ���f���̉�]
	MV1SetScale(m_model, VGet(0.1f, 0.1f, 0.1f));                                                         // ���f���̑傫��(10���̂P�̃T�C�Y)
	MV1DrawModel(m_model);



}


// �I������
void Ninja::Exit()
{
	MV1DeleteModel(m_model);       // ���f���̍폜
	for (int i = 0; i < ANIM_MAX; i++) {  // �A�j���[�V�����̍폜
		MV1DeleteModel(anim_model[i]);
	}

	// �U���A�j���[�V�����̍폜
	for (int i = 0; i < ATTACK_ANIM_MAX; i++) {
		MV1DeleteModel(attack_anim_model[i]);
	}

	// �e���������Ă��Ȃ�������������
	if (bead_pos != NULL) {
		delete bead_pos;
	}

	// �A�j���[�V�����p�ϐ�������delete
	CharacterBase::Anim_Delete();
}