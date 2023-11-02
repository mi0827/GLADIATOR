#pragma once

#include "Character_Base.h"

// Player�N���X
// CharacterBase�N���X���p��
class Player2 : public CharacterBase
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
	
	const float DASH_SPEED = 3.0f; // ����p�̃X�s�[�h

public:
	//---------------
	// �֐��̒�`
	//---------------
	// �e�֐��̒�`
	Player2(); // �R���X�g���N�^
	void Init()override;        //�@��������
	// �J�����ɑ΂��đO�㍶�E�Ɉړ����邽��
	// �J�������ǂ̕����ɂ���̂������Ƃ��Ďg��
	void Update(Vector3* camera_rot) override;		//	�X�V����
	void Move_Hit_Update()override;
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
	// ���ʃA�j���[�V�����ǂݍ��ݗp�̔z��
	int anim_model[ANIM_MAX];
	//���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	int anim_attach[ANIM_MAX];
	//�A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float anim_total[ANIM_MAX];
	// ���ꂼ��̃A�j���[�V�������ǂ̂��炤�̂�肠���ɂȂ邩�i0.0f ~ 1.0f�j
	float anim_rate[ANIM_MAX];
	// �A�j���[�V���������t���[���i��ł���̂�
	float anim_frame[ANIM_MAX];

	// �U���A�j���[�V�����p�̗񋓑�
	enum ATTACK_ANIM
	{
		ATTACK_LONG_NORMAL_ANIM, // // ���������ʍU��

		ATTACK_ANIM_MAX // �U���A�j���[�V�����̐�
	};
	// �e�U���A�j���[�V�����A�j���[�V�����ǂݍ��ݗp�̔z��
	int attack_anim_model[ATTACK_ANIM_MAX];
	// ���f���ɍU���A�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	int attack_anim_attach[ATTACK_ANIM_MAX];
	// �U���A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	float  attack_anim_total[ATTACK_ANIM_MAX];
	// ���ꂼ��̍U���A�j���[�V�������ǂ̂��炤�̂�肠���ɂȂ邩�i0.0f ~ 1.0f�j
	float attack_anim_rate[ATTACK_ANIM_MAX];
	// �U���A�j���[�V���������t���[���i��ł���̂�
	float attack_anim_frame[ATTACK_ANIM_MAX];
	// �ǂ̃A�j���[�V���������Ă���̂��𔻒f����p
	int attack_anim_pick;

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