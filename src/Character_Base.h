#pragma once
//#include "Vector2.h"
//#include "Base.h"
// �L�����N�^�[�N���X
// Base�N���X���p��
class CharacterBase : public Base
{
public:

	// �S�L�������ʂ̒l
#define HP_MAX 700          // HP�̍ő�l
#define SKILL_POINT_MAX 300 // �X�L���|�C���g�̍ő�l
#define SP_POINT_MAX 400    // SP�|�C���g�̍ő�l
#define STATUS_BAR_SIZE 80  // �X�e�[�^�X�o�[�̑����̃T�C�Y

//#define PUNCH_MAX 2
	//---------------
	// �֐��̒�`
	//---------------
	//virtual �� = 0 ���Ă������ƂŔh���N���X�ŃI�[�o�[���[�h�ł���
	CharacterBase();

	// ��������
	// ����
	// �v���C���[�̈�l�ڂ���l�ڂ��̔ԍ�
	virtual void Init(int player_num) = 0; 
	virtual void Animation_Init() = 0;     // �A�j���[�V�����p�̏�������
	// �J�����ɑ΂��đO�㍶�E�Ɉړ����邽��
	// �J�������ǂ̕����ɂ���̂������Ƃ��Ďg��
	// �X�V����
	// ����
	// �P�F�J�����̌���
	// �Q�FSE�̃{�����[��
	virtual void Update(Vector3* camera_rot, int SE_Volume/*, bool status_flag*/) = 0;		
	virtual void Draw() = 0;		               // �`�揈��
	virtual void Exit() = 0;		               // �I������
	virtual void Move_Hit_Update() = 0;            // �ǎC��p�̊֐�
	virtual void Attack_PressButton_Update(Vector3* camera_rot) = 0;  // �A�N�V�����Ɋւ���{�^�������p�̊֐��i���₷�����邽�߂̊֐��j
	virtual void Attack_Update() = 0;              // �U�����s��ꂽ���ɍs��
	virtual void Damage_Update(int* m_attack_damage) = 0;              // �_���[�W��H��������ɍs��
	virtual void Block_Update() = 0;               // �K�[�h���s��ꂽ���ɍs��
	virtual void SE_Init() = 0;                    // SE�̏������悤�֐�

	void Update_Status();        // �X�e�[�^�X�X�V����
	void Reset_Status();         // �X�e�[�^�X�̃��Z�b�g�p�֐�

	// �X�e�[�^�X�`��p�֐�
	// ����
	// �v���C���[�̈�l�ڂ���l�ڂ��̔ԍ�
	void Draw_Status(int player_num);    


	// �v���C���[�̈ړ�������֐�
	// // ����
	// �P�F�������Ă����̂�
	// �Q�F���܂͈ړ����Ă����Ă������̔��f
	// �R�F�v���C���[�̌����Ă������
	// �S�F�ړ��X�s�[�h
	void Move_Player(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);

	// �O�ړ�
	// ����
	// �P�F�������Ă����̂�
	// �Q�F���܂͈ړ����Ă����Ă������̔��f
	// �R�F�v���C���[�̌����Ă������
	// �S�F�ړ��X�s�[�h
	void Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	

	// ���ړ�
	// ����
	// �P�F�������Ă����̂�
	// �Q�F���܂͈ړ����Ă����Ă������̔��f
	// �R�F�v���C���[�̌����Ă������
	// �S�F�ړ��X�s�[�h
	void Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);

	// ���ړ�
	// ����
	// �P�F�������Ă����̂�
	// �Q�F���܂͈ړ����Ă����Ă������̔��f
	// �R�F�v���C���[�̌����Ă������
	// �S�F�ړ��X�s�[�h
	void Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	
	// �E�ړ�
	// ����
	// �P�F�������Ă����̂�
	// �Q�F���܂͈ړ����Ă����Ă������̔��f
	// �R�F�v���C���[�̌����Ă������
	// �S�F�ړ��X�s�[�h
	void Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);

	// �L�����N�^�[�̈ړ��p�֐�(�Q�[���p�b�h�p)
	// ����
	// �P�F�������Ă����̂�
	// �Q�F���܂͈ړ����Ă����Ă������̔��f
	// �R�F�v���C���[�̌����Ă������
	// �S�F�ړ��X�s�[�h
	void Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, const float* mov_speed);

	// �L�����N�^�[�̕ǎC��p�֐�
	// ����
	// �P�F�����i�L�����j�̍��W
	// �Q�F�����i�L�����j�̂����蔻��̃T�C�Y�i���S���猩���T�C�Y�j
	// �R�F�ǂ̍��W
	// �S�F�ǂ̂����蔻��̃T�C�Y�i���S���猩���T�C�Y�j
	void Move_Hit(Vector3* before_pos, Vector3* hit_size, Vector3* other_pos, Vector3* other_size);


	// ���ʃA�j���[�V�����ϐ���New�p�֐�
	// ����
	// �P�F�A�j���[�V�����̐�
	void Nomal_Anim_New(int ANIM_MAX);
	// ���ʃA�j���[�V�����̏����ݒ�
	// ����
	// �P�F�ŏ��ɂ��Ă��Ăق������A�j���[�V�����̔ԍ�
	// �Q�F�A�j���[�V�����̍ő吔
	// �R�F�A�^�b�`����Ƃ��̔ԍ� �P�Ƃ�0�Ƃ��̐���
	void Nomal_Anim_Init(int ANIM_IDLE, int ANIM_MAX, int index);

	// �U���A�j���[�V�����ϐ���New�p�֐�
	// ����
	// �U���A�j���[�V�����̐�
	void Attack_Anim_New(int ATTACK_ANIM_MAX);

	// �U���A�j���[�V�����̏����ݒ�
	// ����
	// �P�F�U���A�j���[�V�����̐�
	// �Q�F�A�^�b�`����Ƃ��̔ԍ� �P�Ƃ�0�Ƃ��̐���
	void Attack_Anim_Init(int ATTACK_ANIM_MAX, int index);

	// �A�N�V�����ɂ������A�j���[�V��������֐��i�U���j
	// ����
	// �A�^�b�`����Ƃ��̔ԍ� �P�Ƃ�0�Ƃ��̐���
	void Attack_Action(int index);

	// �_���[�W�A�j���[�V�����p�̕ϐ���New�p�֐�
	// ����
	// �_���[�W�A�j���[�V�����̐�
	void Damage_Anim_New(int DAMAGE_ANIM_MAX);

	// �_���[�W�A�j���[�V�����̏����ݒ�
	// ����
	// �P�F�_���[�W�A�j���[�V�����̐�
	// �Q�F�A�^�b�`����Ƃ��̔ԍ� �P�Ƃ�0�Ƃ��̐���
	void Damage_Anim_Init(int DAMAGE_ANIM_MAX, int index);

	// �A�N�V�����ɂ������A�j���[�V��������֐��i�_���[�W�j
	// ����
	// �A�^�b�`����Ƃ��̔ԍ� �P�Ƃ�0�Ƃ��̐���
	void Damage_Action(int index);

	// �K�[�h�A�j���[�V�����p�̕ϐ���New�p�֐�
	// ����
	// �K�[�h�A�j���[�V�����̐�
	void Block_Anim_New(int BLOCK_ANIM_MAX);

	// �K�[�h�A�j���[�V�����̏����ݒ�
	// ����
	// �P�F�K�[�h�A�j���[�V�����̐�
	// �Q�F�A�^�b�`����Ƃ��̔ԍ� �P�Ƃ�0�Ƃ��̐���
	void Block_Anim_Init(int BLOCK_ANIM_MAX, int index);

	// �A�N�V�����ɂ������A�j���[�V��������֐��i�K�[�h�j
	// ����
	// �A�^�b�`����Ƃ��̔ԍ� �P�Ƃ�0�Ƃ��̐���
	void Block_Action(int index);

	// �A�j���[�V�����ϐ���delete����p�̊֐�
	void Anim_Delete();




	// �����蔻��̂������Ƃ�������������̏����Ƃ��Ă���֐�
    // �J�v�Z���A�~
	// ����
	// �P�F�w���W
	// �Q�F�x���W
	// �R�F���a
	void Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r);

	// �����蔻��̂������Ƃ�������������̏����Ƃ��Ă���֐�
	// ������
	// ����
	// �P�F���W�iVector3�^�j
	// �Q�F�T�C�Y�iVector3�^�j
	void Get_other(Vector3* hit_other_1, Vector3* hit_other_2);                

	// �����蔻������֐�(�J�v�Z���^�A�~�^)
	// ����
	// �P�F�~�A�J�v�Z���̏�̕���
	// �Q�F�~�A�J�v�Z���̉��̕���
	void Attack_Hit_New(Vector3* pot_pos, Vector3* under_pos);

	// �U���͂�ۑ�����p�̊֐�
	// ����
	// �P�F�U���A�j���[�V�����̐�
	// �Q�F�e�U���̃_���[�W�p�ϐ�
	void Set_Attack_Damage(int ATTACK_ANIM_MAX, const int* attack_damage);

	// delete�p�̊֐�
	void Delete();
	//---------------
	// �萔�̒�`
	//---------------
public:

	//---------------
	// �ϐ��̒�`
	//---------------
public:
	// �Q�[���p�b�h�p�̕ϐ�
	int m_pad_input = 0;

	PAD_NO m_pad_no = PAD_NO::PAD_NO1;				// ���Ԃ̃p�b�h���g���Ă���̂�
	// �Q�[���p�b�h�̔ԍ����Z�b�g����
	// DX���C�u�����[���ł̃p�b�h�̔ԍ����擾
	void SetPadNo(PAD_NO no, int dx_no)
	{
		m_pad_no = no;
		m_pad_input = dx_no;
	}
	// �Q�[���p�b�h�̔ԍ����Ƃ��Ă���
	PAD_NO GetPadNo() const
	{
		return m_pad_no;
	}


protected:

	//---------------------------------------------------------------------------
	// ���f���A�j���[�V�����p�ϐ�
	//---------------------------------------------------------------------------
	int	m_model = 0;	  // �e�L�����̃��f��������p�̕ϐ�
	int m_anim_num = 0;     // �e�p����̃N���X�ł̃A�j���[�V������؂�ւ���p�̕ϐ�
	int m_action_mode = 0;  // ���U�����[�h�Ȃ̂����ʃ��[�h�Ȃ̂��𔻕ʂ���𔻒f����p�̕ϐ�

	//---------------------------------------------------------------------------
	// ���ʃA�j���[�V�����ǂݍ��ݗp�̔z��
	//---------------------------------------------------------------------------
	int* m_anim_model = 0;    // �A�j���[�V�������f��
	int* m_anim_attach = 0;   // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* m_anim_total = 0;  // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float* m_anim_rate = 0;	// ���ꂼ��̃A�j���[�V�����̃u�����h���i0.0f ~ 1.0f�j
	float* m_anim_frame = 0;  // �A�j���[�V���������t���[���i��ł���̂�


	//---------------------------------------------------------------------------
	// �U���A�j���[�V�����p�ϐ�
	//---------------------------------------------------------------------------
	int* m_attack_anim_model = 0;    // �e�U���A�j���[�V�����A�j���[�V�����ǂݍ��ݗp�̔z��
	int* m_attack_anim_attach = 0;   // ���f���ɍU���A�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* m_attack_anim_total = 0;  // �U���A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float* m_attack_anim_rate = 0;   // ���ꂼ��̍U���A�j���[�V�����̃u�����h���i0.0f ~ 1.0f�j
	float* m_attack_anim_frame = 0;  // �U���A�j���[�V���������t���[���i��ł���̂�


	//---------------------------------------------------------------------------
	// �K�[�h�A�j���[�V�����p�ϐ�
	//---------------------------------------------------------------------------
	int* m_block_anim_model = 0;         // �A�j���[�V�������f��
	int* m_block_anim_attach = 0;        // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* m_block_anim_total = 0;       // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float* m_block_anim_rate = 0;	       // ���ꂼ��̃A�j���[�V�����̃u�����h���i0.0f ~ 1.0f�j
	float* m_block_anim_frame = 0;       // �A�j���[�V���������t���[���i��ł���̂�


	//---------------------------------------------------------------------------
	// �_���[�W�i�󂯂����́j�A�j���[�V�����p�ϐ�
	//---------------------------------------------------------------------------
	int* m_damage_anim_model = 0;    // �A�j���[�V�������f��
	int* m_damage_anim_attach = 0;   // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* m_damage_anim_total = 0;  // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float* m_damage_anim_rate = 0;   // ���ꂼ��̃A�j���[�V�������ǂ̂��炤�̂�肠���ɂȂ邩�i0.0f ~ 1.0f�j
	float* m_damage_anim_frame = 0;  // �A�j���[�V���������t���[���i��ł���̂�

	//---------------------------------------------------------------------------
	// �G�t�F�N�g�p�̕ϐ�
	//---------------------------------------------------------------------------
	int* m_effect_container = 0; // �G�t�F�N�g������p�̕ϐ�
	int* m_effect_handle = 0;        // �G�t�F�N�g���g�����p�̃n���h��
public:
	int m_attack_anim_pick = 0;     // �ǂ̃A�j���[�V���������Ă���̂��𔻒f����p
	int m_block_anim_pick = 0;      // �ǂ̃A�j���[�V���������Ă���̂��𔻒f����p
	int m_damage_anim_pick = 0;     // �ǂ̃A�j���[�V���������Ă��邩�𔻒f����p�̕ϐ�

public:
	//---------------------------------------------------------------------------
	// �e�L�����̓����蔻��p�ϐ�
	//---------------------------------------------------------------------------
	bool m_cd_hit_flag = false; //< �����蔻����s�Ă悢���̃t���O


	//---------------------------------------------------------------------------
	// �e�A�N�V�������f�p�ϐ�
	//---------------------------------------------------------------------------
	bool m_action_flag = false;       // �A�N�V�����i�����̃A�j���[�V�����j����Ă��邩�̃t���O
	bool m_attack_flag = false;       // ���U�����Ȃ̂��̔��f 
	bool m_damage_flag = false;       // ���_���[�W���󂯂Ă���̂�
	bool m_block_flag = false;        // ���K�[�h���Ȃ̂�
	bool m_bead_hit_flag = false;     // �e�������ɂ���������
	bool m_skill_flag = false;        // �X�L���Z�̎g�p�ł��邩�̃t���O
	bool m_sp_flag = false;           // �K�E�Z�̎g�p�ł��邩�̃t���O

	//---------------------------------------------------------------------------
	// �R���{�֘A
	//---------------------------------------------------------------------------
	bool m_combo_flag = false;        // �ߋ����U���ł̃R���{�t���O
	int m_next_combo =0;         // ���ɏo���Ăق����U��

	//---------------------------------------------------------------------------
	// �����蔻�肪�������Ƃ��̊e�����̔��f�p�ϐ�
	//---------------------------------------------------------------------------
	bool m_move_judge = false;         // ���܂͈ړ����Ă����Ă������̔��f
	Vector3 m_hit_other_pos = { 0.0f,0.0f,0.0f };   // �����蔻�肪����������̍��W������
	Vector3 m_hit_other_size = { 0.0f,0.0f,0.0f };  // �����蔻�肪����������̃T�C�Y������i�����̂̏ꍇ�j

	//---------------------------------------------------------------------------
	// �L�����N�^�[�̃J�v�Z���^�̓����蔻��p�ϐ�
	//---------------------------------------------------------------------------
	Vector3 m_hit_body_pos_top = { 0.0f,0.0f,0.0f };     // �J�v�Z���̏㑤 
	Vector3 m_hit_body_pos_under = { 0.0f,0.0f,0.0f };   // ����
	float   m_hit_body_r = 0.0f;       // ���a

	//---------------------------------------------------------------------------
	// �ړ��p�����蔻��i�{�b�N�X�j
	//---------------------------------------------------------------------------
	Vector3 m_move_hit_box_pos = { 0.0f,0.0f,0.0f };  // �L�����̑��̉��Ƀp�l���̂悤�ɂ��Ďg��
	Vector3 m_move_hit_box_size = { 0.0f,0.0f,0.0f }; // �p�l���T�C�Y
	Vector3 m_character_size = { 0.0f,0.0f,0.0f };    // �v���C���[���{�b�N�X�Ƃ����Ƃ��̑傫��(���S���W����PANEL_HAL)

	//---------------------------------------------------------------------------
	// �A�N�V�������̓����蔻��p�ϐ��i�J�v�Z���j
	//---------------------------------------------------------------------------
	Vector3 m_hit_cd_pos_top = { 0.0f,0.0f,0.0f };     // �J�v�Z���̏㑤 
	Vector3 m_hit_cd_pos_under = { 0.0f,0.0f,0.0f };   // ����
	float   m_hit_cd_r = 0.0f;       // ���a

	//---------------------------------------------------------------------------
	// �K�[�h���̓����蔻��p�ϐ��i�J�v�Z���j
	//---------------------------------------------------------------------------
	Vector3 m_block_top = { 0.0f,0.0f,0.0f };   // �J�v�Z���̏㑤
	Vector3 m_block_under = { 0.0f,0.0f,0.0f }; // ����
	float   m_block_r = 0.0f; // ���a

	//---------------------------------------------------------------------------
	// �������̂̓�����`��p�ϐ��i�~�j
	//---------------------------------------------------------------------------
	Vector3 m_bead_pos = { 0.0f,0.0f,0.0f };  // ���W
	float   m_bead_r = 0.0f;    // ���a

protected:
	//---------------------------------------------------------------------------
	// �ړ��Ɋւ��镨
	//---------------------------------------------------------------------------
	bool m_check_move = false;    // �ړ������ǂ����𔻒f����ϐ�
	Vector3 m_mov = { 0.0f,0.0f,0.0f };          //  �Q�[���p�b�h�p�ړ��p�x�N�g���p�ϐ�
public:
	Vector3 m_before_mov = { 0.0f,0.0f,0.0f };   // ���t���[���ړ��O�̍��W�������p�̕ϐ�

	//---------------------------------------------------------------------------
	// �L�����N�^�[�̃X�e�[�^�X�p�̕ϐ�
	//---------------------------------------------------------------------------
	// �L�����N�^�[�̗̑�
	Vector2 m_hp_pos = { 0,0 };          // �`����W
	Vector2 m_hp_count = { 0,0 };        // �v�Z�p
	float m_now_hp = 0;                  // ����hp
	Vector2 m_skill_pos = { 0,0 };       // �`����W
	Vector2 m_skill_count = { 0,0 };     // �v�Z�p
	float m_now_skill = 0;               // ���̃X�L���|�C���g
	int m_skill_flame_count = 0;           // �t���[���J�E���g�p�ϐ�
	Vector2 m_sp_pos = { 0,0 };          // �`����W
	Vector2 m_sp_count = { 0,0 };        // �v�Z�p
	float m_now_sp = 0;                  // ����SP�|�C���g
	int m_sp_flame_count = 0;              // �t���[���J�E���g�p�ϐ�

	int* m_attack_damage = 0; // �U����
	bool m_skill_cooldown = false;  // �X�L���g�p��̃N�[���_�E��
	bool m_SP = false;              // �K�E�Z��SP
	// ����̓�̕ϐ��̏���͊e�L�����̃N���X�Œ�`����
	//---------------------------------------------------------------------------
	// �U�����̓����蔻��p�ϐ�
	//---------------------------------------------------------------------------
	Vector3 m_hit_pos_pot = { 0.0f,0.0f,0.0f };
	Vector3 m_hit_pos_under = { 0.0f,0.0f,0.0f };
};