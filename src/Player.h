#pragma once
#include "Character_Base.h"

// Player�N���X
// CharacterBase�N���X���p��
class Player : public CharacterBase
{
	// �v���C���[���ǂ̃A�N�V���������Ă��邩�̔��f�p�̗񋓑�
	enum ActionMode
	{
		NORMAL_ACTION, // �A�C�h���⑖��A�j���[�V���������Ă���
		ATTACK_ACTION, // �U���A�N�V����
		BLOCK_ACTION,  // �K�[�h�A�N�V����
		DAMAGE_ACTION  // �_���[�W�A�N�V����
	};

	//---------------
	// �萔
	//---------------
private:

	const float MOVE_SPEED = 3.0f; // ����p�̃X�s�[�h
	const float WARP = 50.0f;      // �L�����N�^�[�̃��[�v�����

public:

	//---------------
	// �֐��̒�`
	//---------------
	// �e�֐��̒�`
	Player(); // �R���X�g���N�^
	void Init(int player_num) override;         // ��������
	void Animation_Init()override;              // �A�j���[�V�����p�̏�������
	// �J�����ɑ΂��đO�㍶�E�Ɉړ����邽��
	// �J�������ǂ̕����ɂ���̂������Ƃ��Ďg��
	void Update(Vector3* camera_rot/*, bool status_*/) override;  // �X�V����
	void Move_Hit_Update()override;           // �v���C���[�̈ړ��p�����蔻��X�V�����i�ǎC��j
	void Attack_PressButton_Update(Vector3* camera_rot)override; // �A�N�V�����Ɋւ���{�^�������p�̊֐��i���₷�����邽�߂̊֐��j
	void Attack_Update()override;   // �U�����s��ꂽ���ɍs��
	void Damage_Update()override;	// �_���[�W��H��������ɍs��
	void Block_Update()override;	// �K�[�h���s��ꂽ���ɍs��
	void Draw() override;		// �`�揈��
	void Exit() override;		//�I������


	//---------------
	// �ϐ��̒�`
	//---------------
private:


	//---------------------------------
	// �A�j���[�V�����p�̗񋓑�
	enum Animation
	{
		ANIM_IDLE, // �A�C�h��
		ANIM_RUN,  // ����

		ANIM_MAX // �A�j���[�V�����̍ő��
	};

	// �U���A�j���[�V�����p�̗񋓑�
	enum ATTACK_ANIM
	{
		ATTACK_LONG_NORMAL_ANIM,    // ���������ʍU��
		ATTACK_SHORT_NORMAL_1_ANIM, // �ߋ������ʍU���P
		ATTACK_SHORT_NORMAL_2_ANIM, // �ߋ������ʍU���Q
		ATTACK_SLIDE_ANIM,          // �X���C�f�B���O
		ATTACK_SPECIAL_ANIM,        // �X�y�V����

		ATTACK_ANIM_MAX // �U���A�j���[�V�����̐�
	};

	// �_���[�W�A�j���[�V�����p�̗񋓑�
	enum DAMAGE_ANIM
	{
		DAMAGE_ANIM,     //< �_���[�W���󂯂����̃A�j���[�V����
		DAMAGE_ANIM_1,   //< �_���[�W���󂯂����̃A�j���[�V����
		DAMAGE_ANIM_2,   //< ������ԃA�j���[�V����
		DAMAGE_ANIM_3,   //< �N���オ��A�j���[�V����
		DAMAGE_ANIM_END, //< �Ō㕉�������̃A�j���[�V����

		DAMAGE_ANIM_MAX  // �_���[�W�A�j���[�V�����̐�
	};

	// �K�[�h�A�j���[�V�����p�̗񋓑́@
	enum BLOCK_ANIM
	{
		BLOCK_ANIM, // �u���b�N�A�j���[�V����

		BLOCK_ANIM_MAX
	};


	// �A�N�V�����p�̓����蔻��p�̗񋓑�
	enum HIT_ACTION
	{
		THROW_ATTACK_1_HIT,    // ���������ʍU��
		ATTACK_SHORT_NORMAL_1_HIT, // �ߋ������ʍU���P�p�̓����蔻��
		BLOCK_HIT,                 // �u���b�N�p�̓����蔻��

		HIT_ACTION_MAX
	};
public:
	// bead �֘A
	//------------------------------------
	// �e��������܂ł̃J�E���g�p�ϐ�
	float lifespan_count = NULL;

public:
	// ���ꂼ��̍U���_���[�W�̐ݒ�
	const int attack_damage[ATTACK_ANIM_MAX]
	{
		20,  // �������U��
		100,  // �ߋ����U���P
		30,  // �ߋ����U���Q
		10,  // �X���C�f�B���O
		150, // �K�E�Z
	};
	// �����Ŏg�p���邽�߂Ɉڂ�
	const int* m_damage = attack_damage;

	// �ߐڍU���ɂ̓����蔻��p�̍\����
	struct Hit_capsule_data
	{
		Vector3 hit_top;   // �g�b�v�̍��W
		Vector3 hit_under; // �A���_�[�̍��W
		float hit_r;       // ���a
		float hit_anim_frame;  // �A�j���[�V�����̃t���[��(�����ŏo��)
	};

	Hit_capsule_data hit_areas[HIT_ACTION_MAX] =
	{
		// �����A�N�V�����P
		{
			Vector3(8,   13, 8), // �g�b�v
		  Vector3(6, 12.7, 6), // �A���_�[
		  1.0f,   // ���a
		  0.000, // �t���[��}	
		},
		// �ߋ����U���P
	   {
		  Vector3(8,   13, 8), // �g�b�v
		  Vector3(6, 12.7, 6), // �A���_�[
		  1.0f,   // ���a
		  18.000, // �t���[��}	
	   },
	   //�K�[�h�A�N�V����
	   {  Vector3(5,  17, 3), // �g�b�v
		  Vector3(5,   5, 3), // �A���_�[
		  3.0f,   // ���a
		  0.0,    // �t���[��
	   },
	};

	Hit_capsule_data* now_hit_area;





};