#include "WinMain.h"
#include "GameMain.h"
#include "Player2.h"

// �R���X�g���N�^�i�������j
Player2::Player2()
{
	m_pos.set(0.0f, 0.0f, 10.0f);            // �������W�̐ݒ�
	m_rot.set(0.0f, 180.0f, 0.0f);			  // �����̐ݒ�


	// �A�j���[�V���������t���[���i��ł��邩�p�̕ϐ�
	// �ŏ��͂O����J�n
	for (int i = 0; i < ANIM_MAX; i++)
	{
		anim_frame[i] = 0.0f;
	}
	anim_num = 0;                                     // �ŏ��͂O�΂�̃A�j���[�V����������
	action_mode = 0;                                  // �ŏ��͕��ʃA�j���[�V�������[�h�ɂ��Ă���
	attack_anim_pick = -1;                            // �ŏ��͂Ȃ�̃A�j���[�V�����������Ă��Ȃ�
	m_check_move = false;                             // �ŏ��͑����Ă����Ȃ�

	// �����蔻��p�ϐ�
	m_hit_body_pos_top.clear();                       // �J�v�Z���̏㑤
	m_hit_body_pos_under.clear();                     // ����
	m_hit_body_r = 2.0f;                              // ���a
	m_move_judge = false;                              // �ŏ��͓����Ă͂����Ȃ�
	m_attack_judge = false;                            // �U�����Ă��Ȃ�
	bead_hit_judg = false;                            // �Ȃɂɂ��������ĂȂ�
}

// ��������
void Player2::Init()
{

	m_model = MV1LoadModel("Data/Model/Player/Player.mv1");   // �v���C���[���f���̓ǂݍ���
	// ���ʃA�j���[�V�����̏�����
	// �A�j���[�V�����̓ǂݍ���
	anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Player/Animation/Player_Idle.mv1"); // �A�C�h��
	anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Player/Animation/Player_Run.mv1");   // ����
	for (int i = 0; i < ANIM_MAX; i++)
	{

		anim_attach[i] = MV1AttachAnim(m_model, 1, anim_model[i]);             // ���f���ɃA�j���[�V�������A�^�b�`�i����j����
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

	// �U���A�j���[�V�����̏�����
	// �A�j���[�V�����̓ǂݍ���
	attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/long_normal_attack.mv1"); // ���������ʍU��
	for (int i = 0; i < ATTACK_ANIM_MAX; i++)
	{

		attack_anim_attach[i] = MV1AttachAnim(m_model, 1, attack_anim_model[i]);  // ���f���ɃA�j���[�V�������A�^�b�`�i����j����
		attack_anim_total[i] = MV1GetAttachAnimTotalTime(m_model, attack_anim_attach[i]);    // �擾�����A�^�b�`�ԍ����炻�̃A�j���[�V���������t���[�������擾
		attack_anim_attach[i] = MV1DetachAnim(m_model, attack_anim_attach[i]);               // �ŏ��͍U���A�j���[�V�����͂��Ȃ��̂Ńf�B�^�b�`���Ă����i�g�������Ƃ��ɂ܂��A�^�b�`����j
	}
}

// �X�V����
void Player2::Update(Vector3* camera_rot)
{
	// �A�N�V�������[�h�̔��f���Ă���ɍ��������������悤�ɂ���
	switch (action_mode)
	{
	case NORMAL_ACTION:        // ���ʃA�N�V���� 
		m_check_move = false;  // ��Ƀ��Z�b�g
		// WASD�L�[�Ńv���C���[�̈ړ�
		// �ړ����̓_�b�V������
		if (CheckHitKey(KEY_INPUT_UP)) // ��ړ�
		{
			CharacterBase::Move_Front(&m_move_judge, &m_check_move, camera_rot, &m_rot, &DASH_SPEED);
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) // ���ړ�
		{
			CharacterBase::Move_Dehind(&m_move_judge, &m_check_move, camera_rot, &m_rot, &DASH_SPEED);
		}
		if (CheckHitKey(KEY_INPUT_LEFT)) // ���ړ�
		{
			CharacterBase::Move_Left(&m_move_judge, &m_check_move, camera_rot, &m_rot, &DASH_SPEED);
		}
		if (CheckHitKey(KEY_INPUT_RIGHT)) // �E�ړ�
		{
			CharacterBase::Move_Right(&m_move_judge, &m_check_move, camera_rot, &m_rot, &DASH_SPEED);
		}

		// �\���L�[�̂ǂꂩ��������Ă����瓮���Ă��悢
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

		// �}�E�X�̍��N���b�N�ōU��
		if (PushMouseInput(MOUSE_INPUT_LEFT)) {
			anim_attach[anim_num] = MV1DetachAnim(m_model, anim_attach[anim_num]);  // �U���A�j���[�V�����ɓ���O�ɕ��ʃA�j�����O���i���߂̃A�j���[�V�����j 
			attack_anim_attach[ATTACK_LONG_NORMAL_ANIM] = MV1AttachAnim(m_model, 1, attack_anim_model[ATTACK_LONG_NORMAL_ANIM]);      	// �g�������A�j���[�V���������f���ɂ��Ȃ���
			action_mode = ATTACK_ACTION;                 // �U���A�N�V�����ɕύX
			attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // �ʓ����A�N�V�����ɐݒ� 
			m_attack_judge = true;                        // �U�����n�܂�̂ōU�����ɂ��Ă���
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
			// m_attack_judg = false;
		}
		MV1SetAttachAnimTime(m_model, attack_anim_attach[attack_anim_pick], attack_anim_frame[attack_anim_pick]); // �A�j���[�V�����̍Đ�
		break;
	}


	if (m_attack_judge) {

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
			lifespan_count = 120.0f; // �J�E���g�̃��Z�b�g
			m_attack_judge = false; // �U�����I��点�Ă���
		}
	}

	/*if (m_attack_judg) {
		switch (attack_anim_pick)
		{
		case ATTACK_LONG_NORMAL_ANIM:

			break;
		}

	}*/
}

void Player2::Move_Hit_Update()
{
}


// �`�揈��
void Player2::Draw()
{
	// �ʂ�`�悷��(������)
	if (bead_pos != NULL) {
		DrawSphere3D(bead_pos->VGet(), 2.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));                                                                // �`�悷��v���C���[���f���̍��W�̐ݒ�
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y + 180), TO_RADIAN(m_rot.z)));   // ���f���̉�]
	MV1SetScale(m_model, VGet(0.1f, 0.1f, 0.1f));                                                                     // ���f���̑傫��(10���̂P�̃T�C�Y)
	MV1DrawModel(m_model);
}


// �I������
void Player2::Exit()
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
}