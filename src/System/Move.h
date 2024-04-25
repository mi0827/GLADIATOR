#pragma once

/**
* @file Move.h
* @ brief �L�����̈ړ��p�̃N���X
*/
class Move :public Base
{
public:

	Move();
	~Move();

	/**
	* @fn
	* @brief �X�V����
	* @param �P�F�������Ă������̕ϐ�
	* @param �Q�F�J�����̌���
	* @param �R�F�v���C���[�̌����Ă������
	* @param �S�F�ړ��X�s�[�h
	* @param �T�F�v���C���[�̍��W
	* @param �U�F�p�b�h�̔ԍ�
	* @param �V�F�X�e�B�b�N�̒l
	* @detail �ړ��Ɋւ�����̂̍X�V����
	*/
	void Update(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed, Vector3* player_pos, PAD_NO m_pad_no, Vector3 m_mov);

	/**
	* @fn
	* @brief �ړ��Ɋւ��铖���蔻��p�̊֐�
	* @param �P�F���� (�L����) �̍��W(���̍��W)
	* @param �Q�F�����i�L�����j�̍��W(�����蔻��O��)
	* @param �R�F�����i�L�����j�̓����蔻��̃T�C�Y�i���S���猩���T�C�Y�j
	* @param �S�F�ǂ̍��W
	* @param �T�F�ǂ̓����蔻��̃T�C�Y�i���S���猩���T�C�Y�j
	* @detail �ړ��̕ǎC��p�֐�
	*/
	void Move_Hit(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, Vector3* other_pos, Vector3* other_size);

	/**
	* @fn
	* @brief �Q�[���p�b�h�ł̈ړ��p�֐�
	* @param �P�F�����Ă����̂��̕ϐ�
	* @param �Q�F�X�e�B�b�N�̒l
	* @param �R�F�L�����̌����Ă������
�@�@* @param �S�F�L�����̍��W
	* @param �T�F�ړ��X�s�[�h
	* @detail �Q�[���p�b�h�ł̈ړ��p�֐�
	*/
	void Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

	/**
	* @fn
	* @brief �Q�[���p�b�h�ł̈ړ��p�֐�
	* @param �P�F�����Ă����̂��̕ϐ�
	* @param �Q�F�J�����̌���
	* @param �R�F�L�����̌����Ă������
	* @param �S�F�L�����̍��W
	* @param �T�F�ړ��X�s�[�h
	* @detail �Q�[���p�b�h�ł̈ړ��p�֐�
	*/
	void Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

	/**
	* @fn
	* @brief �Q�[���p�b�h�ł̈ړ��p�֐�
	* @param �P�F�����Ă����̂��̕ϐ�
	* @param �Q�F�J�����̌���
	* @param �R�F�L�����̌����Ă������
	* @param �S�F�ړ��X�s�[�h
	* @detail �Q�[���p�b�h�ł̈ړ��p�֐�
	*/
	void Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


	/**
	* @fn
	* @brief �Q�[���p�b�h�ł̈ړ��p�֐�
	* @param �P�F�����Ă����̂��̕ϐ�
	* @param �Q�F�J�����̌���
	* @param �R�F�L�����̌����Ă������
	* @param �S�F�ړ��X�s�[�h
	* @detail �Q�[���p�b�h�ł̈ړ��p�֐�
	*/
	void Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


	/**
	* @fn
	* @brief �Q�[���p�b�h�ł̈ړ��p�֐�
	* @param �P�F�����Ă����̂��̕ϐ�
	* @param �Q�F�J�����̌���
	* @param �R�F�L�����̌����Ă������
	* @param �S�F�ړ��X�s�[�h
	* @detail �Q�[���p�b�h�ł̈ړ��p�֐�
	*/
	void Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


public:
	//! �v���C���[�̍��W�����Ă�������
	Vector3 m_player_pos = { 0.0f,0.0f,0.0f };

	//! �v���C���[�̈ړ��X�s�[�h�����Ă�������
	// static const float player_mov_speed;

	//! �v���C���[�̌��������Ă�������
	Vector3 m_player_rot = { 0.0f,0.0f,0.0f };

	//! �J�����̌��������Ă�������
	Vector3 m_camera_rot = { 0.0f,0.0f,0.0f };
};