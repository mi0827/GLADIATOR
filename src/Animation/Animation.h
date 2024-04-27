#pragma once
#include <iostream>
/**
* @fule Animation.h
* @brief �A�j���[�V�����p�̃N���X
*/

/**
* �A�j���[�V�����p�̃N���X
*/
class Animation final
{
public:




	//! �R���X�g���N�^
	//! @param �A�j���[�V�����̍ő吔
	Animation(int anim_max);


	//1 �f�X�g���N�^
	virtual ~Animation();

	//! �ǂݍ��ݗp�֐�
	//! @param �t�@�C���̃p�X
	//! @param �A�j���[�V�����ԍ�
	void Load_Anim(const char file_path[256], int anim_no, int anim_index);



	//! �A�b�^�`
	//! @param �x�[�X�̃��f��
	//! @param �A�b�^�`���������f���ԍ�
	void Attach_Anim(Model* model, int anim_num);

	//! �f�^�b�`
	//! @param �x�[�X�̃��f��
	//! @param �f�^�b�`���������f���ԍ�
	void Detach_Anim(Model* model,int anim_num);

	//! �A�j���[�V�����̐؂�ւ��p�֐�




private:

	int          m_anim_max = 0;          //!< �A�j���[�V�����̍ő吔
public:


	//! �Đ����̃A�j���[�V�����̏��\����
	struct Context
	{
		bool  is_playering = false;         //!< �Đ������ǂ���
		bool  is_loop = false;              //!< ���[�v�Đ����ǂ���
		int   animation_index = -1;         //!< ���݂̍Đ����̔ԍ�
		int   animation_attach_index = -1;  //!< �A�^�b�`���ꂽ�X���b�g�ԍ�
		float m_blend_ratio = 0.0f;         //!< �u�����h��(0.0f�`1.0f)
		float animation_total_time = 0.0;   //!< ���Đ�����
		float play_time = 0.0f;             //!< ���ݍĐ����̎���
	};

	//! [0]���݂̃A�j���[�V����
	//! [1]���̃A�j���[�V����
	Context m_contexts[2];           //!< �\���̂̓A�j���[�V�����u�����h�̂���2�n��������
	

	float   m_blend_time = 1.0f;    //!< �u�����h�̕�Ԏ���
	struct Anim_
	{
		int handl = -1;     //! �A�j���[�V�����̓��ꕨ
		int index = -1;     //! �A�j���V�����̃C���f�b�N�X
	};
	Anim_* anim_handl;

	////---------------------------------------------------------------------------
	//// ���ʃA�j���[�V�����ǂݍ��ݗp�̔z��
	////---------------------------------------------------------------------------
	//
	//int*   m_anim_model = 0;    // �A�j���[�V�������f��
	//int*   m_anim_attach = 0;   // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	//float* m_anim_total = 0;  // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	//float* m_anim_rate = 0;	// ���ꂼ��̃A�j���[�V�����̃u�����h���i0.0f ~ 1.0f�j
	//float* m_anim_frame = 0;  // �A�j���[�V���������t���[���i��ł���̂�


	////---------------------------------------------------------------------------
	//// �U���A�j���[�V�����p�ϐ�
	////---------------------------------------------------------------------------
	//int* m_attack_anim_model = 0;    // �e�U���A�j���[�V�����A�j���[�V�����ǂݍ��ݗp�̔z��
	//int* m_attack_anim_attach = 0;   // ���f���ɍU���A�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	//float* m_attack_anim_total = 0;  // �U���A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	//float* m_attack_anim_rate = 0;   // ���ꂼ��̍U���A�j���[�V�����̃u�����h���i0.0f ~ 1.0f�j
	//float* m_attack_anim_frame = 0;  // �U���A�j���[�V���������t���[���i��ł���̂�


	////---------------------------------------------------------------------------
	//// �K�[�h�A�j���[�V�����p�ϐ�
	////---------------------------------------------------------------------------
	//int* m_block_anim_model = 0;         // �A�j���[�V�������f��
	//int* m_block_anim_attach = 0;        // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	//float* m_block_anim_total = 0;       // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	//float* m_block_anim_rate = 0;	       // ���ꂼ��̃A�j���[�V�����̃u�����h���i0.0f ~ 1.0f�j
	//float* m_block_anim_frame = 0;       // �A�j���[�V���������t���[���i��ł���̂�


	////---------------------------------------------------------------------------
	//// �_���[�W�i�󂯂����́j�A�j���[�V�����p�ϐ�
	////---------------------------------------------------------------------------
	//int* m_damage_anim_model = 0;    // �A�j���[�V�������f��
	//int* m_damage_anim_attach = 0;   // ���f���ɃA�j���[�V�������A�^�b�`����p�̔z��i�A�^�b�`�ԍ����擾����j
	//float* m_damage_anim_total = 0;  // �A�j���[�V���������t���[���Ȃ��擾�A�����ۑ�����p�̔z��
	//float* m_damage_anim_rate = 0;   // ���ꂼ��̃A�j���[�V�������ǂ̂��炤�̂�肠���ɂȂ邩�i0.0f ~ 1.0f�j
	//float* m_damage_anim_frame = 0;  // �A�j���[�V���������t���[���i��ł���̂�

};