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


void Animation::Init_Animation(int anim_max)
{
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
	m_contexts[1].is_playering = false;
	m_contexts[1].is_loop = false;
	m_contexts[1].animation_index = -1;
	m_contexts[1].animation_attach_index = -1;
	m_contexts[1].m_blend_ratio = 0.0f;
	m_contexts[1].animation_total_time = 0.0;
	m_contexts[1].play_time = 0.0f;
	
}


// �A�j���[�V�����؂�ւ��p�֐�
void Animation::Change_Animation(Model* model, int anim_num)
{
	// ���ɂ͂��Ă���������ւ���
	m_contexts[1] = m_contexts[0];
}


// �A�j���[�V�������Đ������邽�߂̊֐�
void Animation::Play_Animation()
{

}


