#pragma once
#include "src/System/Transform.h"
#include "src/Model/Model.h"
/**
* @fule Fighter.h
* @brief �L�����N�^�[�t�@�C�^�[�̃N���X
*/


/**
* �t�@�C�^�[�̃N���X
*/
class Fighter : public CharacterBase
{
	//public:
	//	//�R���X�g���N�^
	//	Fighter();
	//	// �f�X�g���N�^
	//	~Fighter();
	//
	//	/**
	//	* @fn
	//	* ���������p�̊֐�
	//	* @param ���Ԗڂ̃L������
	//	* @detail �R���X�g���N�^�łł��Ȃ��F�X�Ȃ��̂̏��������s���֐�
	//	*/
	//	void Init(int player_num)override;
	//
	//	/**
	//	* @fn
	//	* �A�j���[�V�����p�̏��������p�֐�
	//	*/
	//	void Animation_Init()override;              // �A�j���[�V�����p�̏�������
	//
	//	/**
	//	* @fn
	//	* �X�V�����p�̊֐�
	//	* @param �P�F�J�����̌���
	//	* @param �Q�FSE�̃{�����[��
	//	* @detail �L�����̍X�V���܂Ƃ߂�֐�
	//	* @detail �����̐���
	//	* @detail �J�����ɑ΂��đO�㍶�E�Ɉړ����邽�߃J�����̏�񂪕K�v
	//	* @detail SE�̃{�����[���̕ύX���g�����߂ɕK�v
	//	*/
	//	void Update(Vector3* camera_rot, int SE_Volume)override;
	//
	//	/**
	//	* @fn
	//	* �v���C���[�̈ړ��p�̓����蔻��X�V�����i�ǎC��j
	//	*/
	//	void Move_Hit_Update()override;
	//
	//	/**
	//	* @fn
	//	* �A�N�V�����Ɋւ���{�^���̉����p�̊֐�
	//	* @param �J�����̌���
	//	*/
	//	void Attack_PressButton_Update(Vector3* camera_rot)override;
	//
	//	void Attack_Update()override;   // �U�����s��ꂽ���ɍs��
	//	// �_���[�W��H��������ɍs���֐�
	//	// ����
	//	// ��������_���[�W
	//	void Damage_Update(int* m_attack_damage)override;
	//
	//	void Block_Update()override;	// �K�[�h���s��ꂽ���ɍs��
	//	void Draw() override;		// �`�揈��
	//	void Exit() override;		// �I������
	//	void SE_Init()override;     // SE�̏������֐�
	//
	//public:
	//	const float MOVE_SPEED = 1.5f; // ����p�̃X�s�[�h
	//	 
	//	static const int anim_max = 2;
	//	
	// Player�N���X
	// CharacterBase�N���X���p��
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

	const float MOVE_SPEED = 1.5f; // ����p�̃X�s�[�h
	const float WARP = 50.0f;      // �L�����N�^�[�̃��[�v�����
	const float HIT_BODY_R = 3.0f; // ���̃L�����̑̂̓����蔻��̔��a
public:

	//---------------
	// �֐��̒�`
	//---------------
	// �e�֐��̒�`
	Fighter(); // �R���X�g���N�^
	void Init(int player_num) override;         // ��������
	void Animation_Init()override;              // �A�j���[�V�����p�̏�������

	// �J�����ɑ΂��đO�㍶�E�Ɉړ����邽��
	// �J�������ǂ̕����ɂ���̂������Ƃ��Ďg��
	// �X�V����
	// ����
	// �P�F�J�����̌���
	// �Q�FSE�̃{�����[��
	void Update(Vector3* camera_rot, int SE_Volume/*, bool status_*/) override;  // �X�V����

	// �v���C���[�̈ړ��p�����蔻��X�V�����i�ǎC��j
	void Move_Hit_Update()override;

	// �A�N�V�����Ɋւ���{�^�������p�̊֐��i���₷�����邽�߂̊֐��j
	void Attack_PressButton_Update(Vector3* camera_rot)override;

	void Attack_Update()override;   // �U�����s��ꂽ���ɍs��
	// �_���[�W��H��������ɍs���֐�
	// ����
	// ��������_���[�W
	void Damage_Update(int* m_attack_damage)override;

	void Block_Update()override;	// �K�[�h���s��ꂽ���ɍs��
	void Draw() override;		// �`�揈��
	void Exit() override;		// �I������
	void SE_Init()override;     // SE�̏������֐�

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
		ATTACK_PUNCH_1_ANIM,        // �p���`�P
		ATTACK_PUNCH_2_ANIM,        // �p���`�Q
		ATTACK_PUNCH_3_ANIM,        // �p���`�R
		ATTACK_PUNCH_4_ANIM,        // �p���`�S�i�R���{�̍Ō�̋Z*�L�b�N�ɂȂ��Ă�j
		ATTACK_WARP_ANIM,          // �X���C�f�B���O
		ATTACK_SPECIAL_ANIM,        // �X�y�V����

		ATTACK_ANIM_MAX             // �U���A�j���[�V�����̐�
	};

	// SE�p�̗񋓑�
	enum SE
	{
		SE_LONG,    // �����Z
		SE_PUNCH_1, // �p���`�P
		SE_PUNCH_2, //	�p���`�Q
		SE_PUNCH_3, //	�p���`�R
		SE_KICK,	// �L�b�N
		SE_SPECIAL, // �K�E�Z 

		SE_MAX // SE�̍ő吔
	};

	// �A�N�V�����p�̓����蔻��p�̗񋓑�
	enum HIT_ACTION
	{
		THROW_ATTACK_HIT,          // ���������ʍU�������蔻��
		ATTACK_PUNCH_1_HIT,        // �p���`�U���P�p�̓����蔻��
		ATTACK_PUNCH_2_HIT,        // �p���`�U���Q�p�̓����蔻��
		ATTACK_PUNCH_3_HIT,        // �p���`�U���R�p�̓����蔻�� 
		ATTACK_PUNCH_4_HIT,        // �p���`�S�i�R���{�̍Ō�̋Z*�L�b�N�ɂȂ��Ă�j
		BLOCK_HIT,                 // �u���b�N�p�̓����蔻��
		SPECIAL_HIT,               // �K�E�Z�̓����蔻��

		HIT_ACTION_MAX             // �����蔻��̐�
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
		BLOCK_ANIM,  // �u���b�N�A�j���[�V����


		BLOCK_ANIM_MAX
	};

	// �G�t�F�N�g�̗񋓑�
	enum EFFECT
	{
		THROW_EFFECT,    // �������Z
		PUNCH_EFFECT,    // �p���`
		PUNCH2_EFFECT,   // �p���`�Q
		GUARD_EFFECT,    // �K�[�h�p
		SPECIAL_EFFECT,  // �K�E�Z�P
		SPECIAL2_EFFECT, // �K�E�Z�Q
		WARP_EFFECT,     // ���[�v

		EFFECT_MAX       // �G�t�F�N�g�̍ő吔
	};

public:
	//------------------------------------
	// bead �֘A
	//------------------------------------
	// �e��������܂ł̃J�E���g�p�ϐ�
	float m_lifespan_count = NULL;

public:
	//Transform transform;
	Model model;
};
