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
	// �ߐڍU���ɂ̓����蔻��p�̍\����
	struct Hit_capsule_data
	{
		Vector3 hit_top;   // �g�b�v�̍��W
		Vector3 hit_under; // �A���_�[�̍��W
		float hit_r;       // ���a
		float fit_anim_frame;  // �A�j���[�V�����̃t���[��(�����ŏo��)
	};

	Hit_capsule_data hit_areas[ATTACK_ANIM_MAX] =
	{
		 { Vector3(8, 1, 10), // �g�b�v
		   Vector3(8, 0, 10),     // �A���_�[
		   1.0f,   // ���a
		   18.000, // �t���[��
		 }	//���������ʍU��
		,{
			Vector3(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 1, m_pos.z + 10 * cosf(TO_RADIAN(m_rot.y))), // �g�b�v
		   Vector3(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y, m_pos.z + 10 * cosf(TO_RADIAN(m_rot.y))),     // �A���_�[
		   1.0f,   // ���a
		   18.000, // �t���[��}	// 
		}
		,{Vector3(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 1, m_pos.z + 10 * cosf(TO_RADIAN(m_rot.y))), // �g�b�v
		   Vector3(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y, m_pos.z + 10 * cosf(TO_RADIAN(m_rot.y))),     // �A���_�[
		   1.0f,   // ���a
		   18.000, // �t���[��} //
		}
		,{Vector3(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 1, m_pos.z + 10 * cosf(TO_RADIAN(m_rot.y))), // �g�b�v
		   Vector3(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y, m_pos.z + 10 * cosf(TO_RADIAN(m_rot.y))),     // �A���_�[
		   1.0f,   // ���a
		   18.000, // �t���[��} // 
		}
		,{Vector3(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y + 1, m_pos.z + 10 * cosf(TO_RADIAN(m_rot.y))), // �g�b�v
		   Vector3(m_pos.x + 8 * sinf(TO_RADIAN(m_rot.y)), m_pos.y, m_pos.z + 10 * cosf(TO_RADIAN(m_rot.y))),     // �A���_�[
		   1.0f,   // ���a
		   18.000, // �t���[��} //
		}
	};
	Hit_capsule_data now_hit_area;


		// �e�������ɂ���������
	bool bead_hit_judg;
	// �e�ϐ�
	Vector3* bead_pos = 0; // ���W
	float bead_r = 0;      // ���a

};