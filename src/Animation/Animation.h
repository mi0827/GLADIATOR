#pragma once

/**
* @fule Animation.h
* @brief �A�j���[�V�����p�̃N���X
*/

/**
* �A�j���[�V�����p�̃N���X
*/
class Animation
{
public:
	
	//!@brief �R���X�g���N�^
	//!@param �A�j���[�V�����̍ő吔
	Animation();

	
	//!@brief �f�X�g���N�^
	virtual ~Animation();

	//! �A�j���[�V�����̃f�[�^�p�̍\����
	struct AnimData
	{
		int handle = -1;     //! �A�j���[�V�����̓��ꕨ
		int index = -1;     //! �A�j���V�����̃C���f�b�N�X
	};
	std::vector<AnimData*> anim_handle;

	//! �Đ����̃A�j���[�V�����̏��\����
	struct Information
	{
		bool  is_playering = false;         //!< �Đ������ǂ���
		bool  is_loop = false;              //!< ���[�v�Đ����ǂ���
		int   animation_index = -1;         //!< ���݂̍Đ����̔ԍ�
		int   animation_attach_index = -1;  //!< �A�^�b�`���ꂽ�X���b�g�ԍ�
		float m_blend_ratio = 0.0f;         //!< �u�����h��(0.0f�`1.0f)
		float animation_total_time = 0.0;   //!< ���Đ�����
		float play_time = 0.0f;             //!< ���ݍĐ����̎���
	};
	//! �\���̂̓A�j���[�V�����u�����h�̂���2�n��������
	//! [0]���݂̃A�j���[�V����
	//! [1]�O�̃A�j���[�V����
	Information m_contexts[2];          

	//! @brief �A�j���[�V�����̏��̏������֐�
	//! @param �ǂ���̍\���̂����������邩�̔ԍ�
	void Information_Init(int num);

	//! @brief �A�j���[�V�����̏����ݒ�
	//! @param �A�j���[�V�����̐�
	//! @param �f�t�H���g�ݒ肵�����A�j���[�V�����̔ԍ�
	//! @detail �f�t�H���g�A�j���[�V�����̃Z�b�g�A�A�j���[�V�����̓��ꕨ�̊m��
	void Init_Animation(int anim_max, int default_anim);

	
	//! @brief�ǂݍ��ݗp�֐�
	//! @param �t�@�C���̃p�X
	//! @param �A�j���[�V�����ԍ�
	void Load_Animation(const char file_path[256], int anim_no, int anim_index);


	//! @brief�A�j���[�V�������Z�b�g����֐�
	//! @param �x�[�X�̃��f��
	//! @param �A�b�^�`���������f���ԍ�
	//! @param ���[�v�Đ������邩�ǂ���
	void Attach_Animation(Model* model, int anim_num, bool loop);


	//! @brief���Ă���A�j���[�V���������O���悤�̊֐�
	//! @param �x�[�X�̃��f��
	//! @param �f�^�b�`���������f���ԍ�
	void Detach_Animation(Model* model);


	//! @brief�A�j���[�V�����̐؂�ւ��p�֐�
	//! @param �x�[�X�̃��f��
	//! @param ���ɃZ�b�g�������A�j���[�V�����ԍ�
	//! @param �A�j���[�V���������[�v�����邩�ǂ���
	void Change_Animation(Model* model, int anim_num, bool loop);

	//! @brief �A�j���[�V�����̐؂�ւ��p�֐�
	//! @param �x�[�X�̃��f��
	//! @param ���ɃZ�b�g�������A�j���[�V�����ԍ�
	//! @param �A�j���[�V���������[�v�����邩�ǂ�
	//! @detail �A�j���[�V�������I���^�C�~���O�Ő؂�ւ����Change_Animation���Ăт������p�̊֐�
	void Action_Change_Animation(Model* model, int anim_num, bool loop);

	//! @brief�A�j���[�V�����̍Đ�
	//! @param �x�[�X�̃��f��
	void Play_Animation(Model* model);


	//! @brief�A�j���[�V���������[�v������
	void Loop_Animation();

	//! @brief���[�v�����Ȃ��ꍇ
    //! @param �x�[�X�̃��f��
	void Not_Loop(Model* model);



private:

	int m_anim_max = 0;          //!< �A�j���[�V�����̍ő吔
	int m_default_anim = -1;     //!< �f�t�H���g�ŃZ�b�g�����A�j���[�V�����ԍ��p�̕ϐ�

};