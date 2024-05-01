#include "src/WinMain.h"
#include "src/Model/Model.h"
#include "Animation.h"


using namespace std;

// �R���X�g���N�^
Animation::Animation()
{

}


// �f�X�g���N�^
Animation::~Animation()
{

	anim_handle.clear();
	delete m_contexts;
}

// �A�j���[�V�����̏��̏������֐�
void Animation::Information_Init(int num)
{
	//�A�j���[�V�����̏������ׂď��������Ă���
	m_contexts[num].is_playering = false;
	m_contexts[num].is_loop = false;
	m_contexts[num].animation_index = -1;
	m_contexts[num].animation_attach_index = -1;
	m_contexts[num].m_blend_ratio = 0.0f;
	m_contexts[num].animation_total_time = 0.0;
	m_contexts[num].play_time = 0.0f;
}

// �A�j���[�V�����̏����ݒ�
void Animation::Init_Animation(int anim_max, int default_anim)
{
	// �f�t�H���g�A�j���[�V�����̐ݒ�
	m_default_anim = default_anim;
	// �A�j���[�V�����̓��ꕨ��z��Ŋm�ۂ���
	for (int i = 0; i < anim_max; i++)
	{
		AnimData* anim = new AnimData;
		anim_handle.push_back(anim);
	}
}

// �ǂݍ���
void Animation::Load_Animation(const char file_path[256], int anim_no, int anim_index)
{
	// �ǂݍ���
	anim_handle[anim_no]->handle = MV1LoadModel(file_path);
	// �A�j���V�����C���f�b�N�X�ԍ��̕ۑ�
	anim_handle[anim_no]->index = anim_index;
}


// �A�j���[�V�����̃Z�b�g
void Animation::Attach_Animation(Model* model, int anim_num, bool loop)
{
	// ���ꕨ�����������Ă���
	Information_Init(0);

	// �A�j���V�����̃Z�b�g
	m_contexts[0].animation_attach_index = MV1AttachAnim
	(
		model->m_model,
		anim_handle[anim_num]->index,
		anim_handle[anim_num]->handle
	);


	// �A�j���[�V�������Đ��t���[���̎擾
	m_contexts[0].animation_total_time = MV1GetAttachAnimTotalTime
	(
		model->m_model,
		m_contexts[0].animation_attach_index
	);


	// �u�����h���̎擾
	m_contexts[0].m_blend_ratio = MV1GetAttachAnimBlendRate
	(
		model->m_model,
		m_contexts[0].animation_attach_index
	);

	// ���[�v���邩�ǂ���
	m_contexts[0].is_playering = loop;
}

// �A�j���[�V�����̎��O��
void Animation::Detach_Animation(Model* model)
{
	// �A�j���[�V�������̎��O��
	m_contexts[1].animation_attach_index = MV1DetachAnim
	(model->m_model,
		m_contexts[1].animation_attach_index);
	// ���O�����A�j���[�V�����̏������ׂď��������Ă���
	Information_Init(1);
}


// �A�j���[�V�����؂�ւ��p�֐�
void Animation::Change_Animation(Model* model, int anim_num , bool loop)
{
	// �A�j���[�V���������ւ���O�ɂ��Ƃ��Ƃ��Ă��A�j���[�V���������O��
	Detach_Animation(model);
	// ���ɂ͂��Ă���������ւ���
	m_contexts[1] = m_contexts[0];

	// ���ɍs�������A�j���[�V����������
	Attach_Animation(model, anim_num, loop);

	// ���̃A�j���[�V�����̃u�����h�����グ��
	m_contexts[0].m_blend_ratio += 0.1f;
	// ����̐ݒ�
	if (m_contexts[0].m_blend_ratio > 1.0f)
	{
		m_contexts[0].m_blend_ratio = 1.0f;
	}
	// ���Ƃ��Ƃ̃A�j���[�V�����̃u�����h����������
	m_contexts[1].m_blend_ratio -= 0.1f;
	// �����̐ݒ�
	if (m_contexts[1].m_blend_ratio < 0)
	{
		m_contexts[1].m_blend_ratio = 0.0f;
	}
}

// �A�j���[�V�����؂�ւ��p�֐��i�A�j���[�V�������I���^�C�~���O�Ő؂�ւ���j
void Animation::Action_Change_Animation(Model* model, int anim_num, bool loop)
{
	// �A�j���[�V�������Ō�̃t���[���ɍ����|��������
	if (m_contexts[0].animation_total_time >= m_contexts[0].play_time)
	{
		Change_Animation(model, anim_num, loop);
	}
}

// �A�j���[�V�������Đ������邽�߂̊֐�
void Animation::Play_Animation(Model* model)
{

	m_contexts[0].play_time++;
	// ���[�v���邩�ǂ����ɂ���ď����̕ύX
	if (m_contexts[0].is_loop)
	{
		Loop_Animation();
	}
	else // ���[�v���Ȃ��ꍇ
	{
		Not_Loop(model);
	}

	// ���ꂼ��ɃA�j���[�V�����̊������Đ����܂�
	for (int i = 0; i < 2; i++)
	{
		MV1SetAttachAnimBlendRate(
			model->m_model,
			m_contexts[i].animation_attach_index,
			m_contexts[i].play_time);
	}
}

// �A�j���[�V���������[�v������
void Animation::Loop_Animation()
{

	// �A�j���[�V�����t���[�����Ō�܂ŉ������
	if (m_contexts[0].play_time > m_contexts[0].animation_total_time)
	{
		// �ŏ��Ƀ��Z�b�g����
		m_contexts[0].play_time = 0.0f;
	}

}

void Animation::Not_Loop(Model* model)
{
	// �A�j���[�V�����t���[�����Ō�܂ŉ������
	if (m_contexts[0].play_time >= m_contexts[0].animation_total_time)
	{
		// �f�t�H���g�̃A�j���[�V�����ɐݒ�
		Change_Animation(model, m_default_anim, true);
	}

}


