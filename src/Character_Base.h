#pragma once

#include "Base.h"

// �L�����N�^�[�N���X
// Base�N���X���p��
class CharacterBase : public Base
{
public:

#define HP_MAX 350 // HP�̍ő�l
	//---------------
	// �֐��̒�`
	//---------------
	//virtual �� = 0 ���Ă������ƂŔh���N���X�ŃI�[�o�[���[�h�ł���
	CharacterBase();
	virtual void Init(int player_num) = 0;        // ��������
	// �J�����ɑ΂��đO�㍶�E�Ɉړ����邽��
	// �J�������ǂ̕����ɂ���̂������Ƃ��Ďg��
	virtual void Update(Vector3* camera_rot) = 0;		// �X�V����
	virtual void Move_Hit_Update() = 0; // �ǎC��p�̊֐�
	
	virtual void Draw() = 0;		    // �`�揈��
	virtual void Exit() = 0;		    // �I������

	//---------------------------------------------------------------------------
	// �ړ��p�֐�
	// ����
	// �P�F�������Ă����̂�
	// �Q�F���܂͈ړ����Ă����Ă������̔��f
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

	// �A�j���[�V�����ϐ���delete����p�̊֐�
	void Anim_Delete(int ANIM_MAX, int ATTACK_ANIM_MAX);

	// �U���ɂ������A�j���[�V����������֐�
	void Attack_Action(int index);


	// �����蔻��̂������Ƃ�������������̏����Ƃ��Ă���֐�
	void Get_other(float* hit_other_x, float* hit_other_z, float* hit_other_r); // �J�v�Z���A�~

	void Get_other(Vector3* hit_other_1, Vector3* hit_other_2);               // ������
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
	int* anim_attach;   //���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	float* anim_total;  //�A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
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
	int attack_anim_pick;     // �ǂ̃A�j���[�V���������Ă���̂��𔻒f����p

public:
	//---------------------------------------------------------------------------
	// �e�L�����̓����蔻��p�ϐ�
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	// �����蔻�肪�������Ƃ��̊e�����̔��f�p�ϐ�
	//---------------------------------------------------------------------------
	bool m_move_judge;         // ���܂͈ړ����Ă����Ă������̔��f
	bool m_attack_judge;       // ���U�����Ȃ̂��̔��f 
	Vector3 m_hit_other_pos;   // �����蔻�肪����������̍��W������
	Vector3 m_hit_other_size;  // �����蔻�肪����������̃T�C�Y������i�����̂̏ꍇ�j

	//---------------------------------------------------------------------------
	// �J�v�Z���^�̓����蔻��p�ϐ�
	//---------------------------------------------------------------------------
	Vector3 m_hit_body_pos_top;     // �J�v�Z���̏㑤 
	Vector3 m_hit_body_pos_under;   // ����
	float m_hit_body_r = 0;         // ���a

	//---------------------------------------------------------------------------
	// �ړ��p�����蔻��i�{�b�N�X�j
	//---------------------------------------------------------------------------
	Vector3 m_move_hit_box_pos;  // �L�����̑��̉��Ƀp�l���̂悤�ɂ��Ďg��
	Vector3 m_move_hit_box_size; // �p�l���T�C�Y
	Vector3 m_character_size;    // �v���C���[���{�b�N�X�Ƃ����Ƃ��̑傫��(���S���W����PANEL_HAL)

	//---------------------------------------------------------------------------
	// �U�����̓����蔻��p�ϐ��i�J�v�Z���j
	//---------------------------------------------------------------------------
	Vector3 m_hit_attack_pos_top;     // �J�v�Z���̏㑤 
	Vector3 m_hit_attack_pos_under;   // ����
	float m_hit_attack_r = 0;         // ���a
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
	Vector2 m_hp_pos; // �`����W
	Vector2 m_hp_count; // �v�Z�p
};