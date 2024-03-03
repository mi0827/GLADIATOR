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
#define PANEL_SIZE	5.0f              // �p�l���̑傫��
#define PANEL_HALF	(PANEL_SIZE/2.0f) // �p�l���̔����̑傫��
#define ATTACK_ANIM_SPEED 1.4f

// SE�N���X�̃I�u�W�F�N�g
SE player_se;
//---------------------------------------------------------------------------
// �R���X�g���N�^�i�������j
//---------------------------------------------------------------------------

Player::Player()
{
	m_pos.set(0.0f, 0.0f, 0.0f);             // �������W�̐ݒ�
	m_rot.set(0.0f, 0.0f, 0.0f);             // �����̐ݒ�
	m_before_mov.set(m_pos);                       // �ŏ��͍ŏ��̍��W�����Ƃ�

	m_anim_num = 0;                                    // �ŏ��͂O�΂�̃A�j���[�V����������
	m_action_mode = 0;                                 // �ŏ��͕��ʃA�j���[�V�������[�h�ɂ��Ă���
	m_attack_anim_pick = -1;                           // �ŏ��͂Ȃ�̃A�j���[�V�����������Ă��Ȃ�
	m_check_move = false;                            // �ŏ��͑����Ă����Ȃ�

	//------------------------------
	// �����蔻��p�ϐ�
	//=============
	// �{�̂̓����蔻��
	// �J�v�Z��
	m_hit_body_pos_top.clear();                       // �㑤
	m_hit_body_pos_under.clear();                     // ����
	m_hit_body_r = HIT_BODY_R;                        // ���a

	// �����蔻��p
	m_hit_cd_pos_top.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 13, m_pos.z + 8 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_cd_pos_under.set(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + (float)12.7, m_pos.z + 6 * cosf(TO_RADIAN(m_rot.y)));
	m_hit_cd_r = 1.0f;
	//======================
	// �ړ��p�̃{�b�N�X                                                   
	m_move_hit_box_size.set(PANEL_HALF - (float)0.1, PANEL_HALF - (float)0.1, PANEL_HALF - (float)0.1);    // �p�l���̑傫��

	// ���f�p�A�t���O�ϐ�
	m_move_judge = false;                              // �ŏ��͓����Ă͂����Ȃ�
	m_attack_flag = false;                               // �U�����Ă��Ȃ�
	m_bead_hit_flag = false;                             // �Ȃɂɂ��������ĂȂ�
	m_lifespan_count = NULL;


	m_combo_flag = false; // �U�����������Ă��Ȃ��̂Ńt���O������
	m_now_hit_area = 0;
	m_player_num = 0;
	for (int i = 0; i < 2; i++)
	{
		m_color[i] = { 0,0,0,0 }; // ���̃L�����̐F
	}
}

//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void Player::Init(int player_num)
{
	m_player_num = player_num; // 1p��2p��������
	m_model = MV1LoadModel("Data/Model/Player/Player.mv1");   // �v���C���[���f���̓ǂݍ���
	// ���̃L�����̃��f���̃}�e���A���̐F���擾
	m_color[0] = MV1GetMaterialDifColor(m_model, 0);
	m_color[1] = MV1GetMaterialDifColor(m_model, 1);

	Animation_Init(); //< �A�j���[�V�����̐ݒ�

	//Effect_New(EFFECT_MAX, m_effect_container_ptr, m_effect_handle);
	//m_effect_container_ptr = new int[EFFECT_MAX + 2];
	m_effect_container = EffectContainerNew(EFFECT_MAX);
	m_effect_handle = EffectContainerNew(EFFECT_MAX);
	// �G�t�F�N�g�̓ǂݍ���
	m_effect_container[THROW_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/Aura01.efkefc", 1.0);   // �������̃G�t�F�N�g
	m_effect_container[PUNCH_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/Punch0.efkefc", 0.5f);  // �p���`�G�t�F�N�g
	m_effect_container[PUNCH2_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/Punch1.efkefc", 0.3f);  // �p���`�Q�G�t�F�N�g
	m_effect_container[GUARD_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/guard.efkefc", 3.0f);  // �K�[�h�p
	m_effect_container[SPECIAL_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/special.efkefc", 3.0f);  // �K�E�Z�P
	m_effect_container[SPECIAL2_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/special2.efkefc", 13.0f);  // �K�E�Z�Q
	m_effect_container[WARP_EFFECT] = LoadEffekseerEffect("Data/Model/Player/Effect/warp.efkefc", 1.0f);  // ���[�v�G�t�F�N�g
	// pad_input = GetJoypadInputState(DX_INPUT_PAD3);  // �Q�[���p�b�h�̓ǂݍ���


	if (player_num == 0)
	{
		m_pos.set(350.0f, 0.0f, 150.0f);           // �������W�̐ݒ�
		m_rot.set(0.0f, 0.0f, 0.0f);             // �����̐ݒ�
	}
	else
	{
		m_pos.set(350.0f, 0.0f, 450.0f);            // �������W�̐ݒ�
		m_rot.set(0.0f, 180.0f, 0.0f);			  // �����̐ݒ�
	}

	// �U���͂̐ݒ�
	CharacterBase::Set_Attack_Damage(ATTACK_ANIM_MAX, m_damage);

	SE_Init(); // SE�̏�����
}

//---------------------------------------------------------------------------
// �A�j���[�V�����p�̏�������
//---------------------------------------------------------------------------
void Player::Animation_Init()
{
	// ���ʃA�j���[�V�����̏�����
	CharacterBase::Nomal_Anim_New(ANIM_MAX);  // ���ʃA�j���[�V�����ɕK�v�ȕϐ��̔z������
	m_anim_model[ANIM_IDLE] = MV1LoadModel("Data/Model/Player/Animation/Idle.mv1"); // �A�C�h��
	m_anim_model[ANIM_RUN] = MV1LoadModel("Data/Model/Player/Animation/Player_Run.mv1");   // ����
	CharacterBase::Nomal_Anim_Init(ANIM_IDLE, ANIM_MAX, 1); // ���ʃA�j���[�V�����̏����ݒ�

	// �U���A�j���[�V�����̏�����
	CharacterBase::Attack_Anim_New(ATTACK_ANIM_MAX); //< �U���A�j���[�V�����ɕK�v�ȕϐ��̔z������
	m_attack_anim_model[ATTACK_LONG_NORMAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/long_normal_attack.mv1");       // ���������ʍU��
	m_attack_anim_model[ATTACK_PUNCH_1_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch.mv1");                        // �p���`�P
	m_attack_anim_model[ATTACK_PUNCH_2_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch2.mv1");                       // �p���`�Q
	m_attack_anim_model[ATTACK_PUNCH_3_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch3.mv1");                       // �p���`�R
	m_attack_anim_model[ATTACK_PUNCH_4_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/Punch_Kick.mv1");                   // �R���{�U���̍Ō�̍U���i�L�b�N�ɂȂ��Ă�j
	m_attack_anim_model[ATTACK_WARP_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/slide.mv1");                          // �X���C�f�B���O
	m_attack_anim_model[ATTACK_SPECIAL_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Attack/special_attack.mv1");               // �K�E�Z
	CharacterBase::Attack_Anim_Init(ATTACK_ANIM_MAX, 1); //< �U���A�j���[�V�����̏����ݒ�

	// �_���[�W�A�j���[�V�����̏�����
	CharacterBase::Damage_Anim_New(DAMAGE_ANIM_MAX); //< �_���[�W�A�j���[�V�����ɕK�v�ȕϐ��̔z������
	m_damage_anim_model[DAMAGE_ANIM] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/damage1.mv1");     //< �_���[�W�H�������
	m_damage_anim_model[DAMAGE_ANIM_1] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/damage2.mv1");   //< �_���[�W�H��������Q
	m_damage_anim_model[DAMAGE_ANIM_2] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/SweepFall.mv1"); //< ������ԃA�j���[�V����
	m_damage_anim_model[DAMAGE_ANIM_3] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/GettingUp.mv1"); //< �N���オ��A�j���[�V����
	m_damage_anim_model[DAMAGE_ANIM_END] = MV1LoadModel("Data/Model/Player/Animation/TakeDamage/die.mv1");
	CharacterBase::Damage_Anim_Init(DAMAGE_ANIM_MAX, 1); //< �_���[�W�A�j���[�V�����̏�����

	// �K�[�h�A�j���[�V�����̐ݒ�
	CharacterBase::Block_Anim_New(BLOCK_ANIM_MAX);
	m_block_anim_model[BLOCK_ANIM] = MV1LoadModel("Data/Model/Player/Animation/Block/block.mv1");

	CharacterBase::Block_Anim_Init(BLOCK_ANIM_MAX, 1);
}

//---------------------------------------------------------------------------
// �X�V����
//---------------------------------------------------------------------------
void Player::Update(Vector3* camera_rot, int SE_Volume/*, bool status_flag*/)
{
	
	// SE�̃{�����[������
	player_se.SE_ChangeVolume(SE_Volume, SE_MAX);

	m_before_mov = m_pos; // �ړ������O�ɓ���ւ��Ƃ�
	m_action_flag = false; // �A�N�V�����t���O������
	m_cd_hit_flag = false;
	// �A�N�V�������[�h�̔��f���Ă���ɍ��������������悤�ɂ���
	switch (m_action_mode)
	{
	case NORMAL_ACTION:        // ���ʃA�N�V���� 
		m_check_move = false;  // ��Ƀ��Z�b�g

		//=================================
		// �A�N�V�����Ɋւ���{�^�������p�̊֐��i���₷�����邽�߂̊֐��j
		//=================================
		Attack_PressButton_Update(camera_rot);
		if (m_action_flag)
		{ // �A�N�V�����t���O���オ���Ă�����
			//// �A�j���[�V�����̍Đ�
			//// �g�������Ȃ��A�j���[�V����
			//if (anim_num == 0) {

			//	anim_rate[0] =1.0f; // ���������炷
			//	anim_rate[1] = 0.0f;
			//}
			//else {// �g�������A�j���[�V����		
			//	anim_rate[0] = 0.0f; // ���������炷
			//	anim_rate[1] = 1.0f;
			//}
			
			break;         // ��̏������΂�
		}


		//=================================
		// �_���[�W�̂�H�������
		//=================================
		if (m_damage_flag) 
		{
			m_action_mode = DAMAGE_ACTION;            // ���f���̃A�N�V�������_���[�W�ɕύX
			if (m_now_hp == 0) {                    // �̗͂��Ȃ��Ȃ���
				m_damage_anim_pick = DAMAGE_ANIM_END; // ���ʃA�j���[�V�����ɂ���
			}
			CharacterBase::Damage_Action(1);  // �s�������_���[�W�A�j���[�V�������Z�b�g
			break;
		}
		// �ړ�����
		CharacterBase::Move_Player(&m_check_move, camera_rot, &m_rot, &MOVE_SPEED);
		// �̂̓����蔻��̏ꏊ�̐ݒ�
		m_hit_body_pos_top = m_pos;
		m_hit_body_pos_top.y += 17.0f; // �������o��
		m_hit_body_pos_under = m_pos;
		m_hit_body_pos_under.y += 3.0f;
		// �ړ����Ȃ�A�j���[�V�����̕ύX�Ɠ����蔻��̈ړ�
		if (m_check_move) 
		{
			m_anim_num = ANIM_RUN;  // �ړ����Ȃ̂ő���A�j���[�V������

		}
		else 
		{                           // �ǂ̈ړ��L�[��������ĂȂ�������
			m_anim_num = ANIM_IDLE;   // �A�C�h����Ԃɂ���

		}
		// �A�j���[�V�����p�̃t���[���J�E���g��i�߂�
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
			// �A�j���[�V�����̍Đ�
			// �g�������Ȃ��A�j���[�V����
			if (i != m_anim_num) 
			{

				m_anim_rate[i] -= 1.0f; // ���������炷
			}
			else
			{                         // �g�������A�j���[�V����		
				m_anim_rate[i] += 1.0f; // �����𑝂₷
			}

			m_anim_rate[i] = max(0.0f, min(m_anim_rate[i], 1.0f));                                    // ������0.0f �` 1.0f�ɂ���i��������Ȃ��Ɨx�苶���j 
			MV1SetAttachAnimTime(m_model, m_anim_attach[i], m_anim_frame[i]);  // ���̃t���[���̃A�j���[�V�����ɂ���
			MV1SetAttachAnimBlendRate(m_model, m_anim_attach[i], m_anim_rate[i]);   // ���ꂼ��ɃA�j���[�V�����̊������Đ����܂�
		}


		break;

	case ATTACK_ACTION: // �U���A�N�V����

		// �A�j���[�V�����̍Đ�
		// �U���A�j���[�V�����p�̃t���[���J�E���g��i�߂�
		m_attack_anim_frame[m_attack_anim_pick] += ATTACK_ANIM_SPEED;
		if (m_combo_flag) 
		{
			// �R���{�t���O�������Ă�����
			if (m_attack_anim_frame[m_attack_anim_pick] >= m_attack_anim_total[m_attack_anim_pick]) 
			{                                           // �A�j���[�V���������������
				m_attack_anim_frame[m_attack_anim_pick] = 0.0f;
				m_attack_anim_attach[m_attack_anim_pick] = MV1DetachAnim(m_model, m_attack_anim_attach[m_attack_anim_pick]);  // �U���A�j���[�V�������f�B�^�b�`���Ă���
				m_attack_anim_attach[m_next_combo] = MV1AttachAnim(m_model, 1, m_attack_anim_model[m_next_combo]); // ���̃R���{�U���A�j���[�V���������f���ɂ��Ȃ���
				m_attack_anim_pick = m_next_combo;                                                                                          // ���̍U���ɍ����ւ���
				m_combo_flag = false;                                                                                                     // �R���{�t���O��������
			}
		}
		else 
		{
			// �R���{�t���O���~��Ă�����
			if (m_attack_anim_frame[m_attack_anim_pick] >= m_attack_anim_total[m_attack_anim_pick]) 
			{                                           // �A�j���[�V���������������
				m_attack_anim_frame[m_attack_anim_pick] = 0.0f;
				m_attack_anim_attach[m_attack_anim_pick] = MV1DetachAnim(m_model, m_attack_anim_attach[m_attack_anim_pick]);  // �U���A�j���[�V�������f�B�^�b�`���Ă���
				m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 1, m_anim_model[m_anim_num]);                              // ���f���Ɍ��̃A�j���[�V�������A�^�b�`���Ȃ����i���߂̃A�j���[�V�����j
				m_action_mode = NORMAL_ACTION;                                                                                         	// �A�j���[�V�������P���[�v������rATTACK_ACTION����o��
				m_attack_flag = false;                                                                                                    // �U�����I������̂ł����������Ă��Ȃ��悤�ɂ���
				m_attack_anim_pick = ATTACK_ANIM_MAX;                                                                                     // �U���A�j���[�V�������I������̂ŃA�j���[�V�������ݒ肳��Ă��Ȃ��l�ɂ��Ă���
				m_combo_flag = false;                                                                                                     // �R���{�t���O��������
				m_bead_pos = m_pos;
			}
		}
		MV1SetAttachAnimTime(m_model, m_attack_anim_attach[m_attack_anim_pick], m_attack_anim_frame[m_attack_anim_pick]); // �A�j���[�V�����̍Đ�

		if (m_attack_flag) 
		{ // �U���t���O���オ���Ă�����
			Attack_Update();  // �U���p�̃A�b�v�f�[�g
		}
		break;

	case BLOCK_ACTION:

		// �A�j���[�V�����̍Đ�
		// �K�[�h�A�j���[�V�����p�̃t���[���J�E���g��i�߂�
		// �h��t���O���オ���Ă���Ԃ͖h��A�j���[�V���������[�v������
		m_block_anim_frame[m_block_anim_pick]++;

		if (m_block_anim_frame[m_block_anim_pick] >= m_block_anim_total[m_block_anim_pick]) 
		{                                                                                                          // �A�j���[�V���������������
			m_block_anim_frame[m_block_anim_pick] = 0.0f;                                                              // �A�j���[�V�������ŏ�����ɂ��Ă���
		}
		if (m_block_flag == false) 
		{                                                                                                          // �K�[�h�t���O������������
			m_block_anim_attach[m_block_anim_pick] = MV1DetachAnim(m_model, m_block_anim_attach[m_block_anim_pick]);       // �K�[�h�A�j���[�V�������f�B�^�b�`���Ă���
			m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 1, m_anim_model[m_anim_num]);                               // ���f���Ɍ��̃A�j���[�V�������A�^�b�`���Ȃ����i���߂̃A�j���[�V�����j
			m_action_mode = NORMAL_ACTION; 	                                                                       // �A�j���[�V�������P���[�v������rATTACK_ACTION����o��
			m_block_anim_pick = BLOCK_ANIM_MAX;                                                                      // �K�[�h�̃s�b�N�����Z�b�g
		}
		//=================================
		// �K�[�h���Ƀ_���[�W��H������Ƃ�
		//=================================
		if (m_damage_flag && m_block_flag == true) 
		{
			m_block_anim_frame[m_block_anim_pick] = 0.0f;                                                              // �A�j���[�V�������ŏ�����ɂ��Ă���
			m_block_anim_attach[m_block_anim_pick] = MV1DetachAnim(m_model, m_block_anim_attach[m_block_anim_pick]);       // �K�[�h�A�j���[�V�������f�B�^�b�`���Ă���
			m_action_mode = DAMAGE_ACTION; 	                                                                       // �_���[�W���󂯂Ă���̂�DAMAGE_ACTIO�Ɉړ�
			m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 1, m_anim_model[m_anim_num]);                               // ���f���Ɍ��̃A�j���[�V�������A�^�b�`���Ȃ����i���߂̃A�j���[�V
			CharacterBase::Damage_Action(1);                                                                       // �s�������_���[�W�A�j���[�V�������Z�b�g
			// damage_anim_attach[damage_anim_pick] = MV1AttachAnim(m_model, 1, damage_anim_model[damage_anim_pick]);      	// �g�������A�j���[�V���������f���ɂ��Ȃ���
			m_block_anim_pick = BLOCK_ANIM_MAX;																	   // �K�[�h�̃s�b�N�����Z�b�g
			m_block_flag = false;
			break;
		}
		MV1SetAttachAnimTime(m_model, m_block_anim_attach[m_block_anim_pick], m_block_anim_frame[m_block_anim_pick]); // �A�j���[�V�����̍Đ�

		if (m_block_flag)
		{                     // �K�[�h�t���O���オ������
			Block_Update();   // �K�[�h�p�̃A�b�v�f�[�g
		}
		break;

	case DAMAGE_ACTION: // �_���[�W��H��������̃A�j���[�V�����Đ�

		m_damage_anim_frame[m_damage_anim_pick]++;
		if (m_damage_anim_frame[m_damage_anim_pick] >= m_damage_anim_total[m_damage_anim_pick]) 
		{                                                                                                                          // �A�j���[�V���������������
			m_damage_anim_frame[m_damage_anim_pick] = (float)MV1DetachAnim((int)m_model, (int)m_damage_anim_attach[m_damage_anim_pick]);   // �U���A�j���[�V�������f�B�^�b�`���Ă���
			m_anim_attach[m_anim_num] = MV1AttachAnim(m_model, 1, m_anim_model[m_anim_num]);                              // ���f���Ɍ��̃A�j���[�V�������A�^�b�`���Ȃ����i���߂̃A�j���[�V�����j
			m_action_mode = NORMAL_ACTION; 	                                                                      // �A�j���[�V�������P���[�v��������_���[�W�A�j���[�V��������o��
			// �L�����̂������[���ȊO�̎�
			if (m_now_hp != 0) 
			{
				m_damage_anim_frame[m_damage_anim_pick] = 0.0f;
				m_damage_flag = false; // �_���[�W�A�j���[�V�����t���O������
				m_damage_anim_pick = 0;// DAMAGE_ANIM_MAX;	// !!�C���|�C���g!!
			}
			// �U���A�j���[�V�������I������̂ŃA�j���[�V�������ݒ肳��Ă��Ȃ��l�ɂ��Ă���
		}
		MV1SetAttachAnimTime(m_model, m_damage_anim_attach[m_damage_anim_pick], m_damage_anim_frame[m_damage_anim_pick]);

		break;
	}


	CharacterBase::Update_Status();
}


//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void Player::Draw()
{
	if (!m_bead_hit_flag) 
	{
		DrawCapsule3D(m_bead_pos.VGet(), m_bead_pos.VGet(), m_bead_r, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	}
	// �ʂ�`�悷��(������)
#ifdef DEBUG
	// �v���C���[���g�̓����蔻���������悤�ɂ��Ă���
	DrawCapsule3D(m_hit_body_pos_top.VGet(), m_hit_body_pos_under.VGet(), m_hit_body_r, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

	// �����蔻���������悤�ɂ��镨
	// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
	//hit_areas[ATTACK_LONG_NORMAL_ANIM].hit_top = Vector3();

	if (cd_hit_flag && attack_flag) {
		DrawCapsule3D(m_hit_cd_pos_top.VGet(), m_hit_cd_pos_under.VGet(), m_hit_cd_r, 8, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
	}
	if (cd_hit_flag && block_flag) {
		DrawCapsule3D(m_block_top.VGet(), m_block_under.VGet(), m_block_r, 8, GetColor(255, 255, 0), GetColor(255, 255, 0), FALSE);
	}
#endif // DEBUG
	// 1P,2P�ɉ����ăL�����̐F��ς���
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

	// �v���C���[�̕`��ݒ�
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z)); // �`�悷��v���C���[���f���̍��W�̐ݒ�
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y + 180), TO_RADIAN(m_rot.z))); // ���f���̉�]
	MV1SetScale(m_model, VGet(0.1f, 0.1f, 0.1f)); // ���f���̑傫��(10���̂P�̃T�C�Y)
	MV1DrawModel(m_model); // ���f���̕`��

	// Effekseer�`�揈��
	DrawEffekseer3D();
}

//---------------------------------------------------------------------------
// �I������
//---------------------------------------------------------------------------
void Player::Exit()
{
	MV1DeleteModel(m_model);       // ���f���̍폜
	for (int i = 0; i < ANIM_MAX; i++) 
	{  // �A�j���[�V�����̍폜
		MV1DeleteModel(m_anim_model[i]);
	}

	// �U���A�j���[�V�����̍폜
	for (int i = 0; i < ATTACK_ANIM_MAX; i++) 
	{
		MV1DeleteModel(m_attack_anim_model[i]);
	}

	// �U���p�����蔻�肪�������Ă��Ȃ�������
	if (!m_now_hit_area) 
	{
		m_now_hit_area = nullptr;
	}

	// base��new�����ϐ�������delete
	CharacterBase::Delete();

}

//---------------------------------------------------------------------------
// SE�p�̏�������
//---------------------------------------------------------------------------
void Player::SE_Init()
{
	// SE�̐����̔z��̎擾
	player_se.SE_ContainerNew(SE_MAX);
	player_se.Load_SE("Data/Model/Player/SE/long.mp3", SE_LONG);      // �p���`�P
	player_se.Load_SE("Data/Model/Player/SE/punch1.mp3", SE_PUNCH_1); // �p���`�P
	player_se.Load_SE("Data/Model/Player/SE/punch2.mp3", SE_PUNCH_2); // �p���`�Q
	player_se.Load_SE("Data/Model/Player/SE/punch3.mp3", SE_PUNCH_3); // �ς񂿂R
	player_se.Load_SE("Data/Model/Player/SE/kick.mp3", SE_KICK);      // �L�b�N
	player_se.Load_SE("Data/Model/Player/SE/special.mp3", SE_SPECIAL);// �K�E�Z
}


//---------------------------------------------------------------------------
// �v���C���[�̈ړ��p�����蔻��i�ǎC��j
//---------------------------------------------------------------------------
void Player::Move_Hit_Update()
{
	CharacterBase::Move_Hit(&m_before_mov, &m_move_hit_box_size, &m_hit_other_pos, &m_hit_other_size);
}


//---------------------------------------------------------------------------
// �A�N�V�����Ɋւ���{�^�������p�̊֐��i���₷�����邽�߂̊֐��j
//---------------------------------------------------------------------------
void Player::Attack_PressButton_Update(Vector3* camera_rot)
{

	//=================================
	// �ߋ����U��
	//=================================
	// �}�E�X�̍��N���b�N�܂���A�{�^���Ńp���`�U��
	// �Ȃ����o�O���o�Ȃ��悤��action_flag������Ă���
	if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no) && m_action_flag == false) 
	{
		m_action_mode = ATTACK_ACTION;                    // ���f���̃A�N�V�������U���ɕύX
		m_attack_anim_pick = ATTACK_PUNCH_1_ANIM;         // �ߋ����U���A�N�V������ݒ�
		CharacterBase::Attack_Action(1);          // �s�������U���A�j���[�V�������Z�b�g	
		m_action_flag = true;                             // �A�N�V�����t���O���グ��
		//m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // �G�t�F�N�g�̍Đ�
		//SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
	}

	//=================================
	// �������U��
	//=================================
	// �}�E�X�̉E�N���b�N�A�܂��́AB�{�^���ŉ������U��
	// �Ȃ����o�O���o�Ȃ��悤��action_flag������Ă���
	if (PushMouseInput(MOUSE_INPUT_RIGHT) || IsPadOn(PAD_ID::PAD_B, m_pad_no) && m_action_flag == false) 
	{
		//if (IsPadRepeat(PAD_ID::PAD_Y, PAD_NO::PAD_NO1)) {

		m_action_mode = ATTACK_ACTION;                 // ���f���̃A�N�V�������U���ɕύX
		m_attack_anim_pick = ATTACK_LONG_NORMAL_ANIM;  // �ߋ����U���A�N�V������ݒ�
		//bead_hit_flag = false;
		CharacterBase::Attack_Action(1);       // �s�������U���A�j���[�V�������Z�b�g	
		m_action_flag = true;                          // �A�N�V�����t���O���グ��
		m_lifespan_count = NULL;
	}

	//=================================
	// ���[�v
	//=================================
	if (m_skill_flag) { // �X�L�����g�p�ł���Ȃ�
		// �X�y�[�X�L�[�N���b�N�A�܂��́AY�{�^���ŉ������U��
		// �Ȃ����o�O���o�Ȃ��悤��action_flag������Ă���
		if (PushHitKey(KEY_INPUT_SPACE) || IsPadOn(PAD_ID::PAD_Y, m_pad_no) && m_action_flag == false) 
		{

			m_skill_count.x = 0; // �X�L���̎g�p�Ȃ̂ŃJ�E���g�����Z�b�g
			m_action_mode = ATTACK_ACTION;           // ���f���̃A�N�V�������U���ɕύX
			m_attack_anim_pick = ATTACK_WARP_ANIM;   // �ߋ����U���A�N�V������ݒ�
			CharacterBase::Attack_Action(1);        // �s�������U���A�j���[�V�������Z�b�g
			CharacterBase::Move_Front(&m_check_move, &m_rot, &m_rot, &WARP);
			m_action_flag = true;                          // �A�N�V�����t���O���グ��
			m_skill_flag = false;                          // skill���g�p�ς݂ɂ��Ă���
			// �G�t�F�N�g�̍Đ�
			m_effect_handle[WARP_EFFECT] = PlayEffekseer3DEffect(m_effect_container[WARP_EFFECT]); // �G�t�F�N�g�̍Đ�
			SetRotationPlayingEffekseer3DEffect(m_effect_handle[WARP_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
			// �G�t�F�N�g�̍��W��ݒ�
			SetPosPlayingEffekseer3DEffect(m_effect_handle[WARP_EFFECT], m_pos.x, m_pos.y, m_pos.z);
		}
	}

	//=================================
	// �K�E�Z
	//=================================
	// �w E�L�[ �{ Q�L�[ �x�N���b�N�A�܂��́A�w R�{�^�� + L�{�^�� �x�ŕK�E�Z�U��
	// �Ȃ����o�O���o�Ȃ��悤��action_flag������Ă���
	if (m_sp_flag)
	{ // �K�E�Z���g�p�\�Ȃ�
		if (PushHitKey(KEY_INPUT_E) && PushHitKey(KEY_INPUT_Q) || IsPadOn(PAD_ID::PAD_L, m_pad_no) && IsPadOn(PAD_ID::PAD_R, m_pad_no) && m_action_flag == false)
		{
			m_sp_count.x = 0;                        // SP�̎g�p�Ȃ̂ŃJ�E���g�����Z�b�g
			m_action_mode = ATTACK_ACTION;             // ���f���̃A�N�V�������U���ɕύX
			m_attack_anim_pick = ATTACK_SPECIAL_ANIM;  // �K�E�U���A�N�V������ݒ�
			CharacterBase::Attack_Action(1);   // �s�������U���A�j���[�V�������Z�b�g
			// bead_hit_flag = false;
			m_action_flag = true;                      // �A�N�V�����t���O���グ��
			m_sp_flag = false;                         // SP���g�p�ς݂ɂ��Ă���
			m_lifespan_count = NULL;
		}
	}

	//=================================
	// �K�[�h
	//=================================
	// �܂��́AX�{�^���ŉ������U��
	/*if (PushHitKey(KEY_INPUT_LSHIFT) || IsPadOn(PAD_ID::PAD_X, pad_no)) {*/      // �{�^���̈�x����
	// �_���[�W���󂯂Ă��Ȃ�
	// �Ȃ����o�O���o�Ȃ��悤��action_flag������Ă���
	if (/*CheckHitKey(KEY_INPUT_LSHIFT) ||*/ IsPadRepeat(PAD_ID::PAD_X, m_pad_no) && m_action_flag == false) 
	{                                         // X�{�^���̒�����
		m_action_mode = BLOCK_ACTION;           // ���f���̃A�N�V�������K�[�h�ɕύX
		m_block_anim_pick = BLOCK_ANIM;         // �K�[�h�A�N�V������ݒ�
		CharacterBase::Block_Action(1);       // �s�������U���A�j���[�V�������Z�b�g
		m_action_flag = true;                   // �A�N�V�����t���O���グ��

	}
}
//---------------------------------------------------------------------------
// �U���p�A�b�v�f�[�g
//---------------------------------------------------------------------------
void Player::Attack_Update()
{
	switch (m_attack_anim_pick)
	{
	case ATTACK_LONG_NORMAL_ANIM: // �������U���i�e���o���j

		if (m_attack_anim_frame[m_attack_anim_pick] >= 30) 
		{
			if (m_attack_anim_frame[m_attack_anim_pick] <= 30 + ATTACK_ANIM_SPEED) 
			{
				m_effect_handle[THROW_EFFECT] = PlayEffekseer3DEffect(m_effect_container[THROW_EFFECT]);            // �G�t�F�N�g�̍Đ�
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[THROW_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
				SetSpeedPlayingEffekseer3DEffect(m_effect_handle[THROW_EFFECT], (float)1.9);                        // �G�t�F�N�g�̍Đ����x
				m_bead_pos = m_pos;    // ��U�v���C���[�̈ʒu�ɂ��Ă����i�{���v���C���[�̎�̈ʒu�ɍ��킹��j
				m_bead_pos.y += 10.0f; // y���W�����炵�ċ󒆂ɕ����ׂ�
				m_bead_r = 2.0f;       // ���a�̐ݒ�
				m_bead_hit_flag = false;
			}
			// SE�̍Đ�
			if (!player_se.Playing_SE(SE_LONG))
			{
				player_se.Play_SE(SE_LONG, DX_PLAYTYPE_BACK, true);
			}

			// ��U�O�ɔ�΂�
			m_bead_pos.x += 3 * sinf(TO_RADIAN(m_rot.y));
			m_bead_pos.z += 3 * cosf(TO_RADIAN(m_rot.y));
			m_lifespan_count -= ATTACK_ANIM_SPEED; // �e��������܂ł̃J�E���g��i�߂�

			m_now_hit_area = &hit_areas[THROW_ATTACK_HIT];

			m_cd_hit_flag = true; //< �����蔻����s���Ă����p�Ƀt���O�𗧂Ă�

			// �����蔻���������悤�ɂ��镨
			// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
			m_hit_cd_pos_top.set(m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
			m_hit_cd_pos_under.set(m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
			m_hit_cd_r = m_now_hit_area->hit_r;

			// �J�E���g�����ɂ܂Ō��邩�A�����蔻�肪��������
			if (m_attack_anim_frame[m_attack_anim_pick] >= m_attack_anim_total[m_attack_anim_pick] - 30  || m_bead_hit_flag) 
			{
				m_bead_hit_flag = true;   // �e�������ɓ����������������̂Ŕ�������Z�b�g
				m_attack_flag = false;    // �U�����I��点�Ă���
				m_cd_hit_flag = false;    //< �����蔻������Ăق����Ȃ��̂Ńt���O������
			}

			// �G�t�F�N�g�̍��W��ݒ�
			SetPosPlayingEffekseer3DEffect(m_effect_handle[THROW_EFFECT], m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
		}
		break;

	case ATTACK_PUNCH_1_ANIM: // �p���`�ʍU���P 


		// �����蔻��̍쐬
		m_now_hit_area = &hit_areas[ATTACK_PUNCH_1_HIT];
		if (m_attack_anim_frame[ATTACK_PUNCH_1_ANIM] >= m_now_hit_area->hit_anim_frame) 
		{
			m_cd_hit_flag = true; //< �����蔻����s���Ă����p�Ƀt���O�𗧂Ă�

			// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_under.z);
			m_hit_cd_r = m_now_hit_area->hit_r;

			// SE�̍Đ�
			if (!player_se.Playing_SE(SE_PUNCH_1))
			{
				player_se.Play_SE(SE_PUNCH_1, DX_PLAYTYPE_BACK, true);
			}

			// �G�t�F�N�g���Đ����������ĂȂ����𒲂ׂ�
			int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[PUNCH2_EFFECT]);
			// �Đ����łȂ����
			if (play_effect == -1) 
			{
				// �G�t�F�N�g�̍Đ�
				m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // �G�t�F�N�g�̍Đ�
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
			}
		}
		else {
			m_cd_hit_flag = false; //< �����蔻������Ăق����Ȃ��̂Ńt���O������
		}

		// �G�t�F�N�g�̍��W��ݒ�
		SetPosPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], m_hit_cd_pos_top.x, m_hit_cd_pos_top.y, m_hit_cd_pos_top.z);
		// �A�j���[�V�����̒���
		// �}�E�X�̍��N���b�N�܂���A�{�^���Ńp���`�R���{
		if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no)) 
		{
			m_combo_flag = true;                // �R���{�t���O�𗧂Ă�
			m_next_combo = ATTACK_PUNCH_2_ANIM; // ���̍U���ɃZ�b�g����
		}

		break;


	case ATTACK_PUNCH_2_ANIM: // �p���`�U���Q�i�R���{�U���j

		// �����蔻��̍쐬
		m_now_hit_area = &hit_areas[ATTACK_PUNCH_2_HIT];
		if (m_attack_anim_frame[ATTACK_PUNCH_2_ANIM] >= m_now_hit_area->hit_anim_frame)
		{
			m_cd_hit_flag = true; //< �����蔻����s���Ă����p�Ƀt���O�𗧂Ă�

			// �����Ă�������ɍ��W��ݒ�i���̃p���`�Ɉʒu�ɍ��W�ƌ�����������j
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y - 10)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y - 10)) * m_now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 3)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 3)) * m_now_hit_area->hit_under.z);
			m_hit_cd_r = m_now_hit_area->hit_r;
			// SE�̍Đ�
			if (!player_se.Playing_SE(SE_PUNCH_2)) 
			{
				player_se.Play_SE(SE_PUNCH_2, DX_PLAYTYPE_BACK, true);
			}

			// ��񂾂��Đ����Ăق��̂Ń����t���[��������T��
			if (m_attack_anim_frame[ATTACK_PUNCH_2_ANIM] >= m_now_hit_area->hit_anim_frame) 
			{
				// �G�t�F�N�g���Đ����������ĂȂ����𒲂ׂ�
				int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[PUNCH2_EFFECT]);
				// �Đ����łȂ����
				if (play_effect == -1) 
				{
					// �G�t�F�N�g�̍Đ�
					m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // �G�t�F�N�g�̍Đ�
					SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��				
				}
			}
		}
		else 
		{
			m_cd_hit_flag = false; //< �����蔻������Ăق����Ȃ��̂Ńt���O������

		}
		// �G�t�F�N�g�̍��W��ݒ�
		SetPosPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], m_hit_cd_pos_top.x, m_hit_cd_pos_top.y, m_hit_cd_pos_top.z);

		// �A�j���[�V�����̒���
		// �}�E�X�̍��N���b�N�܂���A�{�^���Ńp���`�R���{
		if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no))
		{
			m_combo_flag = true;                // �R���{�t���O�𗧂Ă�
			m_next_combo = ATTACK_PUNCH_3_ANIM; // ���̍U���ɃZ�b�g����
		}
		break;
	case ATTACK_PUNCH_3_ANIM: // �p���`�U��3�i�R���{�U���j
		// �����蔻��̍쐬
		m_now_hit_area = &hit_areas[ATTACK_PUNCH_3_HIT];
		if (m_attack_anim_frame[ATTACK_PUNCH_3_ANIM] >= m_now_hit_area->hit_anim_frame) 
		{
			m_cd_hit_flag = true; //< �����蔻����s���Ă����p�Ƀt���O�𗧂Ă�

			// �����Ă�������ɍ��W��ݒ�i���̃p���`�Ɉʒu�ɍ��W�ƌ�����������j
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 15)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 15)) * m_now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 25)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 25)) * m_now_hit_area->hit_under.z);
			m_hit_cd_r = m_now_hit_area->hit_r;
			// SE�̍Đ�
			if (!player_se.Playing_SE(SE_PUNCH_3)) 
			{
				player_se.Play_SE(SE_PUNCH_3, DX_PLAYTYPE_BACK, true);
			}
			// �G�t�F�N�g���Đ����������ĂȂ����𒲂ׂ�
			int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[PUNCH2_EFFECT]);
			// �Đ����łȂ����
			if (play_effect == -1) 
			{
				// �G�t�F�N�g�̍Đ�
				m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // �G�t�F�N�g�̍Đ�
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
			}
		}
		else 
		{
			m_cd_hit_flag = false; //< �����蔻������Ăق����Ȃ��̂Ńt���O������
		}
		// �G�t�F�N�g�̍��W��ݒ�
		SetPosPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], m_hit_cd_pos_top.x, m_hit_cd_pos_top.y, m_hit_cd_pos_top.z);
		// �A�j���[�V�����̒���
		// �}�E�X�̍��N���b�N�܂���A�{�^���Ńp���`�R���{
		if (PushMouseInput(MOUSE_INPUT_LEFT) || IsPadOn(PAD_ID::PAD_A, m_pad_no))
		{
			m_combo_flag = true;                // �R���{�t���O�𗧂Ă�
			m_next_combo = ATTACK_PUNCH_4_ANIM; // ���̍U���ɃZ�b�g����
		}
		break;
	case ATTACK_PUNCH_4_ANIM: // �p���`�U��3�i�R���{�U���j

		// �����蔻��̍쐬
		m_now_hit_area = &hit_areas[ATTACK_PUNCH_4_HIT];
		if (m_attack_anim_frame[ATTACK_PUNCH_4_ANIM] >= m_now_hit_area->hit_anim_frame) 
		{
			m_cd_hit_flag = true; //< �����蔻����s���Ă����p�Ƀt���O�𗧂Ă�

			// �����Ă�������ɍ��W��ݒ�i���̃p���`�Ɉʒu�ɍ��W�ƌ�����������j
			m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 5)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 5)) * m_now_hit_area->hit_top.z);
			m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y + 15)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y + 15)) * m_now_hit_area->hit_under.z);
			m_hit_cd_r = m_now_hit_area->hit_r;
			// SE�̍Đ�
			if (!player_se.Playing_SE(SE_KICK))
			{
				player_se.Play_SE(SE_KICK, DX_PLAYTYPE_BACK, true);
			}
			// �G�t�F�N�g���Đ����������ĂȂ����𒲂ׂ�
			int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[PUNCH2_EFFECT]);
			// �Đ����łȂ����
			if (play_effect == -1) 
			{
				// �G�t�F�N�g�̍Đ�
				m_effect_handle[PUNCH2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[PUNCH2_EFFECT]); // �G�t�F�N�g�̍Đ�
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
			}
		}
		else
		{
			m_cd_hit_flag = false; //< �����蔻������Ăق����Ȃ��̂Ńt���O������
		}
		// �G�t�F�N�g�̍��W��ݒ�
		SetPosPlayingEffekseer3DEffect(m_effect_handle[PUNCH2_EFFECT], m_hit_cd_pos_top.x, m_hit_cd_pos_top.y, m_hit_cd_pos_top.z);
		break;

	case ATTACK_WARP_ANIM: // ���[�v�i�����蔻��̍쐬�j
	{
		m_now_hit_area = &hit_areas[ATTACK_WARP_ANIM]; // �\���̂�G��₷�����邽�߂ɈႤ�ϐ��ɓ���Ă���
		//cd_hit_flag = true; //< �����蔻����s���Ă����p�Ƀt���O�𗧂Ă�

		//// �����蔻���������悤�ɂ��镨
		//// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
		//if (attack_anim_frame[ATTACK_WARP_ANIM] == now_hit_area->hit_anim_frame) {
		//	m_hit_cd_pos_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.x, m_pos.y + now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_top.z);
		//	m_hit_cd_pos_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.x, m_pos.y + now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * now_hit_area->hit_under.z);
		//}
		//else {
		//	cd_hit_flag = false; //< �����蔻������Ăق����Ȃ��̂Ńt���O������
		//}
		break;
	}

	case ATTACK_SPECIAL_ANIM: // �K�E�Z (�e���o��)

		// �J�E���g�����炾������
		if (m_lifespan_count == NULL) 
		{
			m_lifespan_count = 240.0f; // �J�E���g�̃Z�b�g

		}
		// �e�p�̕ϐ�
		if (m_lifespan_count >= 240.0f)
		{
			//	bead_pos = m_pos; // ��U�v���C���[�̈ʒu�ɂ��Ă����i�{���v���C���[�̎�̈ʒu�ɍ��킹��j
				// ���W�̐ݒ�
			m_bead_pos.set(m_pos.x + 300 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 300, m_pos.z + 300 * cosf(TO_RADIAN(m_rot.y)));
			m_bead_r = 100.0f;        // ���a�̐ݒ�
			m_bead_hit_flag = false;
		}
		m_bead_pos.y--;
		m_lifespan_count--; // �e��������܂ł̃J�E���g��i�߂�


		//now_hit_area = &hit_areas[SPECIAL_HIT];
		// �����蔻���������悤�ɂ��镨
		// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j
		m_hit_cd_pos_top.set(m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
		m_hit_cd_pos_under.set(m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
		m_hit_cd_r = 100;//now_hit_area->hit_r;

		m_cd_hit_flag = true; //< �����蔻����s���Ă����p�Ƀt���O�𗧂Ă�

		// �G�t�F�N�g���Đ������ǂ��ĂȂ����𒲂ׂ�
		int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[SPECIAL_EFFECT]);
		int play_effect2 = IsEffekseer3DEffectPlaying(m_effect_handle[SPECIAL2_EFFECT]);
		SetSpeedPlayingEffekseer3DEffect(m_effect_handle[SPECIAL_EFFECT], 1.0f);            // �G�t�F�N�g�̍Đ����x
		SetSpeedPlayingEffekseer3DEffect(m_effect_handle[SPECIAL2_EFFECT], (float)0.6);
		// �Đ����łȂ����
		if (play_effect == -1)
		{
			// �G�t�F�N�g�̍Đ�
			m_effect_handle[SPECIAL_EFFECT] = PlayEffekseer3DEffect(m_effect_container[SPECIAL_EFFECT]); // �G�t�F�N�g�̍Đ�
			SetRotationPlayingEffekseer3DEffect(m_effect_handle[SPECIAL_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
		}
		if (play_effect2 == -1)
		{
			m_effect_handle[SPECIAL2_EFFECT] = PlayEffekseer3DEffect(m_effect_container[SPECIAL2_EFFECT]); // �G�t�F�N�g�̍Đ�
			SetRotationPlayingEffekseer3DEffect(m_effect_handle[SPECIAL2_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
		}
		// �G�t�F�N�g�̍��W��ݒ�
		SetPosPlayingEffekseer3DEffect(m_effect_handle[SPECIAL_EFFECT], m_pos.x, m_pos.y, m_pos.z);
		SetPosPlayingEffekseer3DEffect(m_effect_handle[SPECIAL2_EFFECT], m_bead_pos.x, m_bead_pos.y, m_bead_pos.z);
		// �J�E���g�����ɂ܂Ō��邩�A�����蔻�肪��������
		if (m_lifespan_count <= 0 || m_bead_hit_flag) 
		{
			m_lifespan_count = NULL;  // ���̂��߂ɋ�ɂ��Ă���
			m_bead_hit_flag = true;  // �e�������ɓ����������������̂Ŕ�������Z�b�g
			m_attack_flag = false;    // �U�����I��点�Ă���
			m_cd_hit_flag = false;    //< �����蔻������Ăق����Ȃ��̂Ńt���O������
		}
		// SE�̍Đ�
		if (!player_se.Playing_SE(SE_SPECIAL)) 
		{
			player_se.Play_SE(SE_SPECIAL, DX_PLAYTYPE_BACK, true);
		}
	}
}


//---------------------------------------------------------------------------
// �_���[�W��H��������p�̊֐�(�H������_���[�W�ɍ��킹�ăA�j���[�V��������ς���)
//---------------------------------------------------------------------------
void Player::Damage_Update(int* m_attack_damage)
{
	// �^����ꂽ�_���[�W�ɂ���ăA�j���[�V������ω�������
	// ���͓����Ă���l�͉��ł�
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
// �K�[�h���������p�̊֐�
//---------------------------------------------------------------------------
void Player::Block_Update()
{
	switch (m_block_anim_pick)
	{
	case BLOCK_ANIM:
		m_now_hit_area = &hit_areas[BLOCK_HIT];
		if (m_attack_anim_frame[BLOCK_HIT] <= m_now_hit_area->hit_anim_frame)
		{
			m_cd_hit_flag = true; //< �����蔻����s���Ă����p�Ƀt���O�𗧂Ă�

			// �����蔻���������悤�ɂ��镨
			// �����Ă�������ɍ��W��ݒ�i���̓p���`�Ɉʒu�j

			m_block_top.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_top.x, m_pos.y + m_now_hit_area->hit_top.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_top.z);
			m_block_under.set(m_pos.x + sinf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_under.x, m_pos.y + m_now_hit_area->hit_under.y, m_pos.z + cosf(TO_RADIAN(m_rot.y)) * m_now_hit_area->hit_under.z);
			m_block_r = m_now_hit_area->hit_r;


			// �G�t�F�N�g���Đ������ǂ��ĂȂ����𒲂ׂ�
			int play_effect = IsEffekseer3DEffectPlaying(m_effect_handle[GUARD_EFFECT]);
			SetColorPlayingEffekseer3DEffect(m_effect_handle[GUARD_EFFECT], 0, 255, 124, 50); // �G�t�F�N�g�̐F�Ɠ����x�̐ݒ�
			SetSpeedPlayingEffekseer3DEffect(m_effect_handle[GUARD_EFFECT], 5);                      // �G�t�F�N�g�̍Đ����x
			// �Đ����łȂ����
			if (play_effect == -1)
			{
				// �G�t�F�N�g�̍Đ�
				m_effect_handle[GUARD_EFFECT] = PlayEffekseer3DEffect(m_effect_container[GUARD_EFFECT]); // �G�t�F�N�g�̍Đ�
				SetRotationPlayingEffekseer3DEffect(m_effect_handle[GUARD_EFFECT], 0, TO_RADIAN(m_rot.y + 180), 0); // �L�����̌����Ă�������ɃG�t�F�N�g�����킹��
			}
			// �G�t�F�N�g�̍��W�ݒ�
			SetPosPlayingEffekseer3DEffect(m_effect_handle[GUARD_EFFECT], m_pos.x, m_pos.y, m_pos.z);

		}
		else 
		{
			m_cd_hit_flag = false; //< �����蔻������Ăق����Ȃ��̂Ńt���O������
		}

		// �K�[�h�L�[�𗣂����Ƃ�
		if (IsPadRelease(PAD_ID::PAD_X, m_pad_no))
		{
			// �͂Ȃ����Ă��鎞��
			m_block_flag = false; // �h��t���O������
			StopEffekseer3DEffect(m_effect_handle[GUARD_EFFECT]); // �G�t�F�N�g���~����
		}

		break;
	}
}