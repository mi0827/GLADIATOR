#pragma once

/**
* @fule Fighter.h
* @brief �L�����N�^�[�t�@�C�^�[�̃N���X
*/


/**
* �t�@�C�^�[�̃N���X
*/
class Fighter : public CharacterBase 
{
public:
	//�R���X�g���N�^
	Fighter();
	// �f�X�g���N�^
	~Fighter();

	/**
	* @fn
	* ���������p�̊֐�
	* @param ���Ԗڂ̃L������
	* @detail �R���X�g���N�^�łł��Ȃ��F�X�Ȃ��̂̏��������s���֐�
	*/
	void Init(int player_num)override;

	/**
	* @fn
	* �A�j���[�V�����p�̏��������p�֐�
	*/
	void Animation_Init()override;              // �A�j���[�V�����p�̏�������

	/**
	* @fn
	* �X�V�����p�̊֐�
	* @param �P�F�J�����̌���
	* @param �Q�FSE�̃{�����[��
	* @detail �L�����̍X�V���܂Ƃ߂�֐�
	* @detail �����̐���
	* @detail �J�����ɑ΂��đO�㍶�E�Ɉړ����邽�߃J�����̏�񂪕K�v
	* @detail SE�̃{�����[���̕ύX���g�����߂ɕK�v
	*/
	void Update(Vector3* camera_rot, int SE_Volume)override;

	/**
	* @fn
	* �v���C���[�̈ړ��p�̓����蔻��X�V�����i�ǎC��j
	*/
	void Move_Hit_Update()override;

	/**
	* @fn
	* �A�N�V�����Ɋւ���{�^���̉����p�̊֐�
	* @param �J�����̌���
	*/
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

public:
	const float MOVE_SPEED = 1.5f; // ����p�̃X�s�[�h
};