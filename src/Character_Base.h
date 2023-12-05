#pragma once

#include "Base.h"
#include "InputPad.h"
// �L�����N�^�[�N���X
// Base�N���X���p��
class CharacterBase : public Base
{
public:

#define HP_MAX 350          // HP�̍ő�l
#define SKILL_POINT_MAX 150 // �X�L���|�C���g�̍ő�l
#define SP_POINT_MAX 200    // SP�|�C���g�̍ő�l
#define PUNCH_MAX 2
	//---------------
	// �֐��̒�`
	//---------------
	//virtual �� = 0 ���Ă������ƂŔh���N���X�ŃI�[�o�[���[�h�ł���
	CharacterBase();
	virtual void Init(int player_num) = 0; // ��������
	virtual void Animation_Init() = 0;     // �A�j���[�V�����p�̏�������
	// �J�����ɑ΂��đO�㍶�E�Ɉړ����邽��
	// �J�������ǂ̕����ɂ���̂������Ƃ��Ďg��
	virtual void Update(Vector3* camera_rot/*, bool status_flag*/) = 0;		// �X�V����
	virtual void Draw() = 0;		               // �`�揈��
	virtual void Exit() = 0;		               // �I������
	virtual void Move_Hit_Update() = 0;            // �ǎC��p�̊֐�
	virtual void Attack_PressButton_Update(Vector3* camera_rot) = 0;  // �A�N�V�����Ɋւ���{�^�������p�̊֐��i���₷�����邽�߂̊֐��j
	virtual void Attack_Update() = 0;              // �U�����s��ꂽ���ɍs��
	virtual void Damage_Update() = 0;              // �_���[�W��H��������ɍs��
	virtual void Block_Update() = 0;               // �K�[�h���s��ꂽ���ɍs��


	void Update_Status();   // �X�e�[�^�X�X�V����
	void Reset_Status();    // �X�e�[�^�X�̃��Z�b�g�p�֐�
	void Draw_Status();     // �X�e�[�^�X�`��p�֐�
	//---------------------------------------------------------------------------
	// �v���C���[�̈ړ�������֐�
	//---------------------------------------------------------------------------
	void Move_Player(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	//---------------------------------------------------------------------------
	// �ړ��p�֐�
	// ����
	// �P�F�������Ă����̂�
	// �Q�F���܂͈ړ����Ă����Ă������̔��f
	// �R�F�v���C���[�̌����Ă������
	// �S�F�ړ��X�s�[�h
	//---------------------------------------------------------------------------
	// �O�ړ�
	void Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	// ���ړ�
	void Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	// ���ړ�
	void Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);
	// �E�ړ�
	void Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed);

	// �L�����N�^�[�̈ړ��p�֐�(�Q�[���p�b�h�p)
	void Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, const float* mov_speed);

	// �L�����N�^�[�̕ǎC��p�֐�
	void Move_Hit(Vector3* before_pos, Vector3* hit_size, Vector3* other_pos, Vector3* other_size);


	// ���ʃA�j���[�V�����ϐ���New�p�֐�
	void Nomal_Anim_New(int ANIM_MAX);
	// ���ʃA�j���[�V�����̏����ݒ�
	void Nomal_Anim_Init(int ANIM_IDLE, int ANIM_MAX, int index);

	// �U���A�j���[�V�����ϐ���New�p�֐�
	void Attack_Anim_New(int ATTACK_ANIM_MAX);
	// �U���A�j���[�V�����̏����ݒ�
	void Attack_Anim_Init(int ATTACK_ANIM_MAX, int index);
	// �A�N�V�����ɂ������A�j���[�V��������֐��i�U���j
	void Attack_Action(int index);

	// �_���[�W�A�j���[�V�����p�̕ϐ���New�p�֐�
	void Damage_Anim_New(int DAMAGE_ANIM_MAX);
	// �_���[�W�A�j���[�V�����̏����ݒ�
	void Damage_Anim_Init(int DAMAGE_ANIM_MAX, int index);
	// �A�N�V�����ɂ������A�j���[�V��������֐��i�_���[�W�j
	void Damage_Action(int index);

	// �K�[�h�A�j���[�V�����p�̕ϐ���New�p�֐�
	void Block_Anim_New(int DAMAGE_ANIM_MAX);
	// �K�[�h�A�j���[�V�����̏����ݒ�
	void Block_Anim_Init(int DAMAGE_ANIM_MAX, int index);
	// �A�N�V�����ɂ������A�j���[�V��������֐��i�K�[�h�j
	void Block_Action(int index);

	// �A�j���[�V�����ϐ���delete����p�̊֐�
	void Anim_Delete();




	// �����蔻��̂������Ƃ�������������̏����Ƃ��Ă���֐�
	void Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r); // �J�v�Z���A�~

	void Get_other(Vector3* hit_other_1, Vector3* hit_other_2);                 // ������

	// �����蔻������֐�
	void Attack_Hit_New(Vector3* pot_pos, Vector3* under_pos);

	// �U���͂�ۑ�����p�̊֐�
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
	int pad_input;

	PAD_NO pad_no = PAD_NO::PAD_NO1;				// ���Ԃ̃p�b�h���g���Ă���̂�
	// �Q�[���p�b�h�̔ԍ����Z�b�g����
	void SetPadNo(PAD_NO no)
	{
		pad_no = no;
	}
	// �Q�[���p�b�h�̔ԍ����Ƃ��Ă���
	PAD_NO GetPadNo() const
	{
		return pad_no;
	}


protected:

	//---------------------------------------------------------------------------
	// ���f���A�j���[�V�����p�ϐ�
	//---------------------------------------------------------------------------
	int	m_model = 0;	  // �e�L�����̃��f��������p�̕ϐ�
	int anim_num = 0;     // �e�p����̃N���X�ł̃A�j���[�V������؂�ւ���p�̕ϐ�
	int action_mode;      // ���U�����[�h�Ȃ̂����ʃ��[�h�Ȃ̂��𔻕ʂ���𔻒f����p�̕ϐ�

	//---------------------------------------------------------------------------
	// ���ʃA�j���[�V�����ǂݍ��ݗp�̔z��
	//---------------------------------------------------------------------------
	int* anim_model;    // �A�j���[�V�������f��
	int* anim_attach;   // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* anim_total;  // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float* anim_rate;	// ���ꂼ��̃A�j���[�V�������ǂ̂��炤�̂�肠���ɂȂ邩�i0.0f ~ 1.0f�j
	float* anim_frame;  // �A�j���[�V���������t���[���i��ł���̂�

	//---------------------------------------------------------------------------
	// �U���A�j���[�V�����p�ϐ�
	//---------------------------------------------------------------------------
	int* attack_anim_model;   // �e�U���A�j���[�V�����A�j���[�V�����ǂݍ��ݗp�̔z��
	int* attack_anim_attach;  // ���f���ɍU���A�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* attack_anim_total; // �U���A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float* attack_anim_rate;  // ���ꂼ��̍U���A�j���[�V�������ǂ̂��炤�̂�肠���ɂȂ邩�i0.0f ~ 1.0f�j
	float* attack_anim_frame; // �U���A�j���[�V���������t���[���i��ł���̂�


	//---------------------------------------------------------------------------
	// �K�[�h�A�j���[�V�����p�ϐ�
	//---------------------------------------------------------------------------
	int* block_anim_model;    // �A�j���[�V�������f��
	int* block_anim_attach;   // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* block_anim_total;  // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float* block_anim_rate;	  // ���ꂼ��̃A�j���[�V�������ǂ̂��炤�̂�肠���ɂȂ邩�i0.0f ~ 1.0f�j
	float* block_anim_frame;  // �A�j���[�V���������t���[���i��ł���̂�


	//---------------------------------------------------------------------------
	// �_���[�W�i�󂯂����́j�A�j���[�V�����p�ϐ�
	//---------------------------------------------------------------------------
	int* damage_anim_model;    // �A�j���[�V�������f��
	int* damage_anim_attach;   // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* damage_anim_total;  // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float* damage_anim_rate;   // ���ꂼ��̃A�j���[�V�������ǂ̂��炤�̂�肠���ɂȂ邩�i0.0f ~ 1.0f�j
	float* damage_anim_frame;  // �A�j���[�V���������t���[���i��ł���̂�

public:
	int attack_anim_pick;     // �ǂ̃A�j���[�V���������Ă���̂��𔻒f����p
	int block_anim_pick;      // �ǂ̃A�j���[�V���������Ă���̂��𔻒f����p
	int damage_anim_pick;     // �ǂ̃A�j���[�V���������Ă��邩�𔻒f����p�̕ϐ�

public:
	//---------------------------------------------------------------------------
	// �e�L�����̓����蔻��p�ϐ�
	//---------------------------------------------------------------------------
	bool cd_hit_flag; //< �����蔻����s�Ă悢���̃t���O


	//---------------------------------------------------------------------------
	// �e�A�N�V�������f�p�ϐ�
	//---------------------------------------------------------------------------
	bool action_flag;       // �A�N�V�����i�����̃A�j���[�V�����j����Ă��邩�̃t���O
	bool attack_flag;       // ���U�����Ȃ̂��̔��f 
	bool damage_flag;       // ���_���[�W���󂯂Ă���̂�
	bool block_flag;        // ���K�[�h���Ȃ̂�
	bool bead_hit_flag;     // �e�������ɂ���������
	bool skill_flag;        // �X�L���Z�̎g�p�ł��邩�̃t���O
	bool sp_flag;           // �K�E�Z�̎g�p�ł��邩�̃t���O

	//---------------------------------------------------------------------------
	// �����蔻�肪�������Ƃ��̊e�����̔��f�p�ϐ�
	//---------------------------------------------------------------------------
	bool m_move_judge;         // ���܂͈ړ����Ă����Ă������̔��f
	Vector3 m_hit_other_pos;   // �����蔻�肪����������̍��W������
	Vector3 m_hit_other_size;  // �����蔻�肪����������̃T�C�Y������i�����̂̏ꍇ�j

	//---------------------------------------------------------------------------
	// �L�����N�^�[�̃J�v�Z���^�̓����蔻��p�ϐ�
	//---------------------------------------------------------------------------
	Vector3 m_hit_body_pos_top;     // �J�v�Z���̏㑤 
	Vector3 m_hit_body_pos_under;   // ����
	float   m_hit_body_r = 0;       // ���a

	//---------------------------------------------------------------------------
	// �ړ��p�����蔻��i�{�b�N�X�j
	//---------------------------------------------------------------------------
	Vector3 m_move_hit_box_pos;  // �L�����̑��̉��Ƀp�l���̂悤�ɂ��Ďg��
	Vector3 m_move_hit_box_size; // �p�l���T�C�Y
	Vector3 m_character_size;    // �v���C���[���{�b�N�X�Ƃ����Ƃ��̑傫��(���S���W����PANEL_HAL)

	//---------------------------------------------------------------------------
	// �A�N�V�������̓����蔻��p�ϐ��i�J�v�Z���j
	//---------------------------------------------------------------------------
	Vector3 m_hit_cd_pos_top;     // �J�v�Z���̏㑤 
	Vector3 m_hit_cd_pos_under;   // ����
	float   m_hit_cd_r = 0;       // ���a

	//---------------------------------------------------------------------------
	// �K�[�h���̓����蔻��p�ϐ��i�J�v�Z���j
	//---------------------------------------------------------------------------
	Vector3 m_block_top;   // �J�v�Z���̏㑤
	Vector3 m_block_under; // ����
	float   m_block_r = 0; // ���a

	//---------------------------------------------------------------------------
	// �������̂̓�����`��p�ϐ��i�~�j
	//---------------------------------------------------------------------------
	Vector3 bead_pos;  // ���W
	float   bead_r;    // ���a

protected:
	//---------------------------------------------------------------------------
	// �ړ��Ɋւ��镨
	//---------------------------------------------------------------------------
	bool m_check_move;    // �ړ������ǂ����𔻒f����ϐ�
	Vector3 mov;          //  �Q�[���p�b�h�p�ړ��p�x�N�g���p�ϐ�
public:
	Vector3 before_mov;   // ���t���[���ړ��O�̍��W�������p�̕ϐ�

	//---------------------------------------------------------------------------
	// �L�����N�^�[�̃X�e�[�^�X�p�̕ϐ�
	//---------------------------------------------------------------------------
	// �L�����N�^�[�̗̑�
	Vector2 m_hp_pos;          // �`����W
	Vector2 m_hp_count;        // �v�Z�p
	float m_now_hp;            // ����hp
	Vector2 m_skill_pos;       // �`����W
	Vector2 m_skill_count;     // �v�Z�p
	float m_now_skill;         // ���̃X�L���|�C���g
	int skill_flame_count = 0; // �t���[���J�E���g�p�ϐ�
	Vector2 m_sp_pos;          // �`����W
	Vector2 m_sp_count;        // �v�Z�p
	float m_now_sp;            // ����SP�|�C���g
	int sp_flame_count = 0;    // �t���[���J�E���g�p�ϐ�

	int* m_attack_damage; // �U����
	bool skill_cooldown;  // �X�L���g�p��̃N�[���_�E��
	bool SP;              // �K�E�Z��SP
	// ����̓�̕ϐ��̏���͊e�L�����̃N���X�Œ�`����
	//---------------------------------------------------------------------------
	// �U�����̓����蔻��p�ϐ�
	//---------------------------------------------------------------------------
	Vector3 hit_pos_pot;
	Vector3 hit_pos_under;
};