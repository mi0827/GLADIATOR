#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

// �m�[�}���A�j���p�̕ϐ��̊m�ۗp�֐�
void Animation::Nomal_Anim_New
(int ANIM_MAX)
{
	m_anim_model = new int[ANIM_MAX];
	m_anim_attach = new int[ANIM_MAX];
	m_anim_total = new float[ANIM_MAX];
	m_anim_rate = new float[ANIM_MAX];
	m_anim_frame = new float[ANIM_MAX];

	//! �A�j���[�V�����t���[�����O����X�^�[�g�ɂ��Ă���
	for (int i = 0; i < ANIM_MAX; i++)
	{
		*m_anim_frame = 0.0f;
	}
}

// �A�^�b�N�A�j���[�V�����p�̕ϐ��̊m�ۗp�֐�
void Animation::Attack_Anim_New(int ANIM_MAX)
{
	m_attack_anim_model = new int[ANIM_MAX];   // �A�j���[�V�������f��
	m_attack_anim_attach = new int[ANIM_MAX];  // �A�^�b�`�p�ϐ�
	m_attack_anim_total = new float[ANIM_MAX]; // �A�j���[�V���������t���[�����邩
	m_attack_anim_rate = new float[ANIM_MAX];  // �A�j���[�V�����̃u�����h��
	m_attack_anim_frame = new float[ANIM_MAX]; // �A�j���[�V�����̐i�߂�t���[��
	// �A�j���[�V���������t���[���i��ł��邩�p�̕ϐ�
	// �ŏ��͂O����J�n
	for (int i = 0; i < ANIM_MAX; i++)
	{
		m_attack_anim_frame[i] = 0.0f;
	}

}

// �_���[�W�A�j���[�V�����p�̕ϐ��̊m�ۗp�֐�
void Animation::Damage_Anim_New(int ANIM_MAX)
{
	m_damage_anim_model = new int[ANIM_MAX];   // �A�j���[�V�������f��
	m_damage_anim_attach = new int[ANIM_MAX];   // �A�^�b�`�p�ϐ�
	m_damage_anim_total = new float[ANIM_MAX]; // �A�j���[�V���������t���[�����邩
	m_damage_anim_rate = new float[ANIM_MAX]; // �A�j���[�V�����̃u�����h��
	m_damage_anim_frame = new float[ANIM_MAX]; // �A�j���[�V�����̐i�߂�t���[��
	// �A�j���[�V���������t���[���i��ł��邩�p�̕ϐ�
	// �ŏ��͂O����J�n
	for (int i = 0; i < ANIM_MAX; i++)
	{
		m_damage_anim_frame[i] = 0.0f;
	}
}

// �K�[�h�A�j���[�V�����p�̕ϐ��̊m�ۗp�֐�
void Animation::Block_Anim_New(int ANIM_MAX)
{
	m_block_anim_model = new int[ANIM_MAX];   // �A�j���[�V�������f��
	m_block_anim_attach = new int[ANIM_MAX];   // �A�^�b�`�p�ϐ�
	m_block_anim_total = new float[ANIM_MAX]; // �A�j���[�V���������t���[�����邩
	m_block_anim_rate = new float[ANIM_MAX]; // �A�j���[�V�����̃u�����h��
	m_block_anim_frame = new float[ANIM_MAX]; // �A�j���[�V�����̐i�߂�t���[��
	// �A�j���[�V���������t���[���i��ł��邩�p�̕ϐ�
	// �ŏ��͂O����J�n
	for (int i = 0; i < ANIM_MAX; i++)
	{
		m_block_anim_frame[i] = 0.0f;
	}
}

void Animation::Anim_Delete()
{

	//! ���ʃA�j���[�V���� 
	delete[] m_anim_model;
	delete[] m_anim_attach;
	delete[] m_anim_total;
	delete[] m_anim_rate;
	delete[] m_anim_frame;

	//! �U���A�j���[�V����
	delete[] m_attack_anim_model;
	delete[] m_attack_anim_attach;
	delete[] m_attack_anim_total;
	delete[] m_attack_anim_rate;
	delete[] m_attack_anim_frame;

	//! �_���[�W�A�j���[�V����
	delete[] m_damage_anim_model;
	delete[] m_damage_anim_attach;
	delete[] m_damage_anim_total;
	delete[] m_damage_anim_rate;
	delete[] m_damage_anim_frame;

	//! �K�[�h�A�j���[�V����
	delete[] m_block_anim_model;
	delete[] m_block_anim_attach;
	delete[] m_block_anim_total;
	delete[] m_block_anim_rate;
	delete[] m_block_anim_frame;

}
