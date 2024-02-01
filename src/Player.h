#pragma once


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

	const float MOVE_SPEED = 1.5f; // ����p�̃X�s�[�h
	const float WARP = 50.0f;      // �L�����N�^�[�̃��[�v�����
	const float HIT_BODY_R = 3.0f; // ���̃L�����̑̂̓����蔻��̔��a
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
	void Update(Vector3* camera_rot, int SE_Volume/*, bool status_*/) override;  // �X�V����
	void Move_Hit_Update()override;           // �v���C���[�̈ړ��p�����蔻��X�V�����i�ǎC��j
	void Attack_PressButton_Update(Vector3* camera_rot)override; // �A�N�V�����Ɋւ���{�^�������p�̊֐��i���₷�����邽�߂̊֐��j
	void Attack_Update()override;   // �U�����s��ꂽ���ɍs��
	void Damage_Update(int* m_attack_damage)override;	// �_���[�W��H��������ɍs��
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
	float lifespan_count = NULL;

public:
	// ���ꂼ��̍U���_���[�W�̐ݒ�
	const int attack_damage[ATTACK_ANIM_MAX]
	{
		40,  // �������U��
		40,  // �p���`�P
		40,  // �p���`�Q
		50,  // �p���`�R
		70,  // �p���`�S
		20,  // �X���C�f�B���O
		400, // �K�E�Z
	};
	// �����Ŏg�p���邽�߂Ɉڂ�
	const int* m_damage = attack_damage;


	// �ߐڍU���ɂ̓����蔻��p�̍\����
	struct Hit_capsule_data
	{
		Vector3 hit_top = { 0.0f,0.0f,0.0f };   // �g�b�v�̍��W
		Vector3 hit_under = { 0.0f,0.0f,0.0f }; // �A���_�[�̍��W
		float hit_r = 0.0f;       // ���a
		float hit_anim_frame =0.0f;  // �A�j���[�V�����̃t���[��(�����ŏo��)
	};


	// �����蔻��̏ꏊ
	Hit_capsule_data hit_areas[HIT_ACTION_MAX] =
	{
		// �����A�N�V�����P
		{
		  Vector3(0, 0, 0), // �g�b�v
		  Vector3(0, 0, 0), // �A���_�[
		  2.0f,   // ���a
		  0.000, // �t���[��}	
		},
		// �p���`�U���P
		{
		  Vector3(8,   13, 8), // �g�b�v
		  Vector3(6, (float)12.7, 6), // �A���_�[
		  1.5f,   // ���a
		  15.000, // �t���[��}	
		},
		{ // �p���`�U���Q
		  Vector3(7.5,   12.5, 7.5), // �g�b�v
		  Vector3(6, 12, 6), // �A���_�[
		  1.5f,   // ���a
		  15.000, // �t���[��}	
		},
		{ // �p���`�U���R
		  Vector3(9,   13, 9), // �g�b�v
		  Vector3(5.5, (float)12.7, 5.5), // �A���_�[
		  1.5f,   // ���a
		  55.000, // �t���[��}	
		},
		{ // �p���`�U���S�i�p���`����Ȃ��ăL�b�N���o��j
		  Vector3(15,  14, 15), // �g�b�v
		  Vector3(7,   11,  7), // �A���_�[
		  1.5f,   // ���a
		  50.000, // �t���[��}	
		},
		// �K�[�h�A�N�V����
		{
		   Vector3(5,  17, 3), // �g�b�v
		   Vector3(5,   5, 3), // �A���_�[
		   3.0f,   // ���a
		   0.0,    // �t���[��
		},
		// �K�E�Z
		{
		   Vector3(0,  0, 0), // �g�b�v
		   Vector3(0,  0, 0), // �A���_�[
		  100.0f,   // ���a
		   0.0,    // �t���[��
		},
	};

	Hit_capsule_data* now_hit_area = 0;

	int m_player_num = 0; // 1p��2p���𔻒f����p�̕ϐ�
	COLOR_F m_color[2] = {0}; // ���̃L�����̐F
};