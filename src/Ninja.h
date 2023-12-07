#pragma once



// Player�N���X
// CharacterBase�N���X���p��
class Ninja : public CharacterBase
{
	// �v���C���[���ǂ̃A�N�V���������Ă��邩�̔��f�p�̗񋓑�
	enum ActionMode
	{
		NORMAL_ACTION, // �A�C�h���⑖��A�j���[�V���������Ă���
		ATTACK_ACTION // �U���A�N�V����
	};


	//---------------
	// �萔
	//---------------
private:

	const float MOVE_SPEED = 3.0f; // ����p�̃X�s�[�h

public:
	//---------------
	// �֐��̒�`
	//---------------
	// �e�֐��̒�`
	Ninja(); // �R���X�g���N�^
	void Init(int player_num)override;        //�@��������
	void Animation_Init()override;              // �A�j���[�V�����p�̏�������
	// �J�����ɑ΂��đO�㍶�E�Ɉړ����邽��
	// �J�������ǂ̕����ɂ���̂������Ƃ��Ďg��
	void Update(Vector3* camera_rot/*,bool status_flag*/) override;		//	�X�V����
	void Move_Hit_Update()override;           // �v���C���[�̈ړ��p�����蔻��X�V�����i�ǎC��j
	void Attack_PressButton_Update(Vector3* camera_rot)override; // �A�N�V�����Ɋւ���{�^�������p�̊֐��i���₷�����邽�߂̊֐��j
	void Attack_Update()override;   // �U�����s��ꂽ���ɍs��
	void Damage_Update()override;	// �_���[�W��H��������ɍs��
	void Block_Update()override;	// �K�[�h���s��ꂽ���ɍs��
	void Draw()override;		//	�`�揈��
	void Exit()override;		//	�I������
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
		ATTACK_SLIDE_ANIM,          // �X���C�f�B���O
		ATTACK_SPECIAL_ANIM,        // �X�y�V����

		ATTACK_ANIM_MAX // �U���A�j���[�V�����̐�
	};


	// bead �֘A
	//------------------------------------
	// �e��������܂ł̃J�E���g�p�ϐ�
	float lifespan_count = 120.0f;

public:

	// �e�������ɂ���������
	bool bead_hit_judg;
	// �e�ϐ�
	Vector3* bead_pos = 0;

};