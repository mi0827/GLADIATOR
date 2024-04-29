#include "src/WinMain.h"
#include "src/Model/Model.h"
#include "Animation.h"


using namespace std;


Animation::Animation()
{
	
}

Animation::~Animation()
{

	anim_handle.clear();
	//delete[] m_contexts;
}


void Animation::Init(int anim_max)
{
	for (int i = 0; i < anim_max; i++)
	{
		AnimData* anim = new AnimData;
		anim_handle.push_back(anim);
	}
}

// �ǂݍ���
void Animation::Load_Anim(const char file_path[256], int anim_no, int anim_index)
{
	// �ǂݍ���
	anim_handle[anim_no]->handle = MV1LoadModel(file_path);
	// �A�j���V�����C���f�b�N�X�ԍ��̕ۑ�
	anim_handle[anim_no]->index = anim_index;
}



void Animation::Attach_Anim(Model* model, int anim_num)
{
	m_contexts[0].animation_attach_index = MV1AttachAnim
	(model->m_model,
		anim_handle[anim_num]->index,
		anim_handle[anim_num]->handle);

}

void Animation::Detach_Anim(Model* model, int anim_num)
{
}


