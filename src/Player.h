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
	Player(); // �R���X�g���N�^
	void Init(int player_num) override;         // ��������
	// �J�����ɑ΂��đO�㍶�E�Ɉړ����邽��
	// �J�������ǂ̕����ɂ���̂������Ƃ��Ďg��
	void Update(Vector3* camera_rot) override;  // �X�V����
	void Move_Hit_Update()override;

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


public:
	// bead �֘A
	//------------------------------------
	// �e��������܂ł̃J�E���g�p�ϐ�
	float lifespan_count = NULL;

public:
	// ���ꂼ��̍U���_���[�W�̐ݒ�
	int attack_damage[ATTACK_ANIM_MAX]
	{
		20,  // �������U��
		30,  // �ߋ����U���P
		30,  // �ߋ����U���Q
		10,  // �X���C�f�B���O
		150, // �K�E�Z
	};



	// �ߐڍU���ɂ̓����蔻��p�̍\����
	struct Hit_capsule_data
	{
		Vector3 hit_top;   // �g�b�v�̍��W
		Vector3 hit_under; // �A���_�[�̍��W
		float hit_r;       // ���a
		float hit_anim_frame;  // �A�j���[�V�����̃t���[��(�����ŏo��)
	};

	Hit_capsule_data hit_areas[ATTACK_ANIM_MAX] =
	{
		//���������ʍU��
		 { Vector3(0,0,0), // �g�b�v
		   Vector3(0,0,0), // �A���_�[
		   0.0f,   // ���a
		   0.0,    // �t���[��
		 }
		 // �ߋ����U���P
		,{
		   Vector3(8,   13, 8), // �g�b�v
		   Vector3(6, 12.7, 6), // �A���_�[
		   1.0f,   // ���a
		   18.000, // �t���[��}	
		}
		// �ߋ����U��2
		,{
		   Vector3(0,0,0), // �g�b�v
		   Vector3(0,0,0), // �A���_�[
		   0.0f,   // ���a
		   0.000, // �t���[��} //
		}
		// �X���C�f�B���O
		,{
		   Vector3(8,1,10), // �g�b�v
		   Vector3(8,0,10),     // �A���_�[
		   1.0f,   // ���a
		   0.000, // �t���[��} // 
		}
		// �K�E�Z
		,{
		   Vector3(0,0,0), // �g�b�v
		   Vector3(0,0,0),     // �A���_�[
		   1.0f,   // ���a
		   18.000, // �t���[��} //
		}

	};
	Hit_capsule_data* now_hit_area;



	// �e�������ɂ���������
	bool bead_hit_judg;
	// �e�ϐ�
	Vector3* bead_pos = 0; // ���W
	float bead_r = 0;      // ���a

};