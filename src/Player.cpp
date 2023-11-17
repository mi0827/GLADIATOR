#include "WinMain.h"
#include "GameMain.h"
#include "Player.h"



#define PANEL_SIZE	5.0f              // �p�l���̑傫��
#define PANEL_HALF	(PANEL_SIZE/2.0f) // �p�l���̔����̑傫��

//---------------------------------------------------------------------------
// �R���X�g���N�^�i�������j
//---------------------------------------------------------------------------
Player::Player()
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

	// �����蔻��p
	m_hit_attack_pos_top.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 13, m_pos.z + 8 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_attack_pos_under.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 12.7, m_pos.z + 6 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_attack_r = 1.0f;
	//======================
	// �ړ��p�̃{�b�N�X                                                   
	m_move_hit_box_size.set(PANEL_HALF - 0.1, PANEL_HALF - 0.1, PANEL_HALF - 0.1);    // �p�l���̑傫��

	// ���f�p�A�t���O�ϐ�
	m_move_judge = false;                              // �ŏ��͓����Ă͂����Ȃ�
	m_attack_judge = false;                            // �U�����Ă��Ȃ�
	bead_hit_judg = false;                            // �Ȃɂɂ��������ĂȂ�

	m_hp_pos.set(10, 32);         // HP�o�[�̕`��ʒu������
	m_hp_count.set(HP_MAX, 32 + 30);   // HP�̌v�Z�p�̏�����
}

//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void Player::Init(int player_num)
{
	m_model = MV1LoadModel("Data/Model/Player/Player.mv1");   // �v���C���[���f���̓ǂݍ���
	// ���ʃA�j���[�V�����̏�����
	// �A�j���[�V�����̓ǂݍ���
	CharacterBase::Nomal_Anim_New(ANIM_MAX);  // ���ʃA�j���[�V�����ɕK�v�ȕϐ��̔z������
	anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Player/Animation/Player_Idle.mv1"); // �A�C�h��
	anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Player/Animation/Player_Run.mv1");   // ����
	CharacterBase::Nomal_Anim_Init(ANIM_IDLE, ANIM_MAX, 1); // ���ʃA�j���[�V�����̏����ݒ�

	// �U���A�j���[�V�����̏�����
	// �A�j���[�V�����̓ǂݍ���
	CharacterBase::Attack_Anim_New(ATTACK_ANIM_MAX); // �U���A�j���[�V�����ɕK�v�ȕϐ��̔z������
	attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/long_normal_attack.mv1");       // ���������ʍU��
	attack_anim_model[ATTACK_SHORT_NORMAL_1_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch.mv1");                 // �ߋ����U���P
	attack_anim_model[ATTACK_SHORT_NORMAL_2_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/short_normal_attack_2.mv1"); // �ߋ����U���Q
	attack_anim_model[ATTACK_SLIDE_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/slide.mv1");                          // �X���C�f�B���O
	attack_anim_model[ATTACK_SPECIAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/special_attack.mv1");               // �K�E�Z
	CharacterBase::Attack_Anim_Init(ATTACK_ANIM_MAX, 1); // �U���A�j���[�V�����̏����ݒ�

	// pad_input = GetJoypadInputState(DX_INPUT_PAD3);  // �Q�[���p�b�h�̓ǂݍ���

	if (player_num == 0) {
		m_pos.set(0.0f, 0.0f, -50.0f);           // �������W�̐ݒ�
		m_rot.set(0.0f, 0.0f, 0.0f);             // �����̐ݒ�
	}
	else {
		m_pos.set(0.0f, 0.0f, 500.0f);            // �������W�̐ݒ�
		m_rot.set(0.0f, 180.0f, 0.0f);			  // �����̐ݒ�
	}
}

//---------------------------------------------------------------------------
// �X�V����
//---------------------------------------------------------------------------
void Player::Update(Vector3* camera_rot)
{
	before_mov = m_pos; // �ړ������O�ɓ���ւ��Ƃ�

	// �A�N�V�������[�h�̔��f���Ă���ɍ��������������悤�ɂ���
	switch (action_mode)
	{
	case NORMAL_ACTION:        // ���ʃA�N�V���� 
		m_check_move = false;  // ��Ƀ��Z�b�g

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
		if (PushMouseInput(MOUSE_INPUT_LEFT) || GetJoypadInputState(pad_no) & PAD_INPUT_1) {
			action_mode = ATTACK_ACTION;                    // ���f���̃A�N�V�������U���ɕύX
			attack_anim_pick = ATTACK_SHORT_NORMAL_1_ANIM;  // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(1);                 // �s�������U���A�j���[�V�������Z�b�g

			break;
		}

		//=================================
		// �������U��
		//=================================
		// �}�E�X�̉E�N���b�N�A�܂��́AY�{�^���ŉ������U��
		if (PushMouseInput(MOUSE_INPUT_RIGHT) || GetJoypadInputState(pad_no) & PAD_INPUT_4) {
			action_mode = ATTACK_ACTION;                 // ���f���̃A�N�V�������U���ɕύX
			attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(1);              // �s�������U���A�j���[�V�������Z�b�g
			break;
		}

		//=================================
		// �X���C�f�B���O
		//=================================
		// �X�y�[�X�L�[�N���b�N�A�܂��́AB�{�^���ŉ������U��
		if (PushHitKey(KEY_INPUT_SPACE) || GetJoypadInputState(pad_no) & PAD_INPUT_2) {
			action_mode = ATTACK_ACTION;           // ���f���̃A�N�V�������U���ɕύX
			attack_anim_pick = ATTACK_SLIDE_ANIM;  // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(1);        // �s�������U���A�j���[�V�������Z�b�g
			break;
		}

		//=================================
		// �K�E�Z
		//=================================
		// �w E�L�[ �{ Q�L�[ �x�N���b�N�A�܂��́A�w R�{�^�� + L�{�^�� �x�ŕK�E�Z�U��
		if (PushHitKey(KEY_INPUT_E) && PushHitKey(KEY_INPUT_Q) || GetJoypadInputState(pad_no) & PAD_INPUT_6 && GetJoypadInputState(pad_no) & PAD_INPUT_5) {
			action_mode = ATTACK_ACTION;             // ���f���̃A�N�V�������U���ɕύX
			attack_anim_pick = ATTACK_SPECIAL_ANIM;  // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(1);   // �s�������U���A�j���[�V�������Z�b�g
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
			anim_attach[anim_num] = MV1AttachAnim(m_model, 1, anim_model[anim_num]);                   // ���f���Ɍ��̃A�j���[�V�������A�^�b�`���Ȃ����i���߂̃A�j���[�V�����j
			action_mode = NORMAL_ACTION; 	// �A�j���[�V�������P���[�v������rATTACK_ACTION����o��
			// �U�����I������̂ł����������Ă��Ȃ��悤�ɂ���
			//m_attack_judge = false;
			attack_anim_pick = ATTACK_ANIM_MAX; // �U���A�j���[�V�������I������̂ŃA�j���[�V�������ݒ肳��Ă��Ȃ��l�ɂ��Ă���
		}
		MV1SetAttachAnimTime(m_model, attack_anim_attach[attack_anim_pick], attack_anim_frame[attack_anim_pick]); // �A�j���[�V�����̍Đ�
		break;
	}


	switch (attack_anim_pick)
	{
	case ATTACK_LONG_NORMAL_ANIM: // �������U���i�e���o���j
		// �J�E���g�����炾������
		if (lifespan_count == NULL) {
			lifespan_count = 120.0f; // �J�E���g�̃Z�b�g
		}
		// �e�p�̕ϐ�
		if (lifespan_count >= 120.0f) {
			bead_pos = new Vector3;
			*bead_pos = m_pos; // ��U�v���C���[�̈ʒu�ɂ��Ă����i�{���v���C���[�̎�̈ʒu�ɍ��킹��j
			bead_pos->y += 10.0f; // y���W�����炵�ċ󒆂ɕ����ׂ�
			bead_r = 2.0f;        // ���a�̐ݒ�
		}
		// ��U�O�ɔ�΂�
		bead_pos->x += 3 * sinf(TO_RADIAN(m_rot.y));
		bead_pos->z += 3 * cosf(TO_RADIAN(m_rot.y));
		lifespan_count--; // �e��������܂ł̃J�E���g��i�߂�
		// �J�E���g�����ɂ܂Ō��邩�A�����蔻�肪��������
		if (lifespan_count <= 0 || bead_hit_judg) {
			delete bead_pos; // �e�̉��
			bead_pos = NULL;
			lifespan_count = NULL; // ���̂��߂ɋ�ɂ��Ă���
			m_attack_judge = false; // �U�����I��点�Ă���
		}
		break;

	case ATTACK_SHORT_NORMAL_1_ANIM: // �ߋ������ʍU���P (�����蔻��̍쐬)
		if (m_attack_judge) { // �U���t���O���オ���Ă�����
			now_hit_area = hit_areas[ATTACK_SHORT_NORMAL_1_ANIM];
			if (attack_anim_frame[ATTACK_SHORT_NORMAL_1_ANIM] == now_hit_area.fit_anim_frame) {
				// �����蔻���������悤�ɂ��镨
				// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
				m_hit_attack_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_top.x, m_pos.y + now_hit_area.hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_top.z);
				m_hit_attack_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_under.x, m_pos.y + now_hit_area.hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_under.z);
			}
			else {
				/*if (now_hit_area != NULL) {
					now_hit_area = NULL;
				}*/
			}
		}
		break;

	case ATTACK_SLIDE_ANIM: // �X���C�f�B���O�i�����蔻��̍쐬�j
		if (m_attack_judge) { // �U���t���O���オ���Ă�����
			now_hit_area = hit_areas[ATTACK_SLIDE_ANIM]; // �\���̂�G��₷�����邽�߂ɈႤ�ϐ��ɓ���Ă���
			// �����蔻���������悤�ɂ��镨
			// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
			if (attack_anim_frame[ATTACK_SLIDE_ANIM] == now_hit_area.fit_anim_frame) {
				m_hit_attack_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_top.x, m_pos.y + now_hit_area.hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_top.z);
				m_hit_attack_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_under.x, m_pos.y + now_hit_area.hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area.hit_under.z);
			}
		}
		break;
	case ATTACK_SPECIAL_ANIM: // �K�E�Z (�e���o��)
		// �J�E���g�����炾������
		if (lifespan_count == NULL) {
			lifespan_count = 240.0f; // �J�E���g�̃Z�b�g
		}
		// �e�p�̕ϐ�
		if (lifespan_count >= 240.0f) {
			bead_pos = new Vector3;
			*bead_pos = m_pos; // ��U�v���C���[�̈ʒu�ɂ��Ă����i�{���v���C���[�̎�̈ʒu�ɍ��킹��j

			// ���W�̐ݒ�
			bead_pos->set(m_pos.x + 300 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 300, m_pos.z + 300 * cosf(TO_RADIAN(m_rot.y)));
			bead_r = 100.0f;        // ���a�̐ݒ�
		}
		bead_pos->y--;
		lifespan_count--; // �e��������܂ł̃J�E���g��i�߂�
		// �J�E���g�����ɂ܂Ō��邩�A�����蔻�肪��������
		if (lifespan_count <= 0 || bead_hit_judg) {
			delete bead_pos; // �e�̉��
			bead_pos = NULL;
			lifespan_count = NULL; // ���̂��߂ɋ�ɂ��Ă���
			m_attack_judge = false; // �U�����I��点�Ă���
		}
	}


	// �X�e�[�^�X�̍X�V����
	CharacterBase::Update_Status();
}

//---------------------------------------------------------------------------
// �v���C���[�̈ړ��p�����蔻��i�ǎC��j
//---------------------------------------------------------------------------
void Player::Move_Hit_Update()
{
	CharacterBase::Move_Hit(&before_mov, &m_move_hit_box_size, &m_hit_other_pos, &m_hit_other_size);
}

//---------------------------------------------------------------------------
// �X�e�[�^�X�`�揈��
//---------------------------------------------------------------------------
// CharacterBase::Draw_Status(); //�X�e�[�^�X�`�揈��

//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void Player::Draw()
{
	// �ʂ�`�悷��(������)
	if (bead_pos != NULL) {
		DrawSphere3D(bead_pos->VGet(), bead_r, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	// �v���C���[���g�̓����蔻��
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	// �����蔻���������悤�ɂ��镨
	// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
	//hit_areas[ATTACK_LONG_NORMAL_ANIM].hit_top = Vector3();
	DrawCapsule3D(m_hit_attack_pos_top.VGet(), m_hit_attack_pos_under.VGet(), m_hit_attack_r, 8, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);


	// �v���C���[�̕`��ݒ�
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z)); // �`�悷��v���C���[���f���̍��W�̐ݒ�
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y + 180), TO_RADIAN(m_rot.z))); // ���f���̉�]
	MV1SetScale(m_model, VGet(0.1f, 0.1f, 0.1f)); // ���f���̑傫��(10���̂P�̃T�C�Y)
	MV1DrawModel(m_model); // ���f���̕`��
}

//---------------------------------------------------------------------------
// �I������
//---------------------------------------------------------------------------
void Player::Exit()
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
	CharacterBase::Anim_Delete(ANIM_MAX, ATTACK_ANIM_MAX);
}