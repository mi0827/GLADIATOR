#include "src/WinMain.h"
#include "Animation.h"
#include "src/Model/Model.h"

using namespace std;


Animation::Animation(int anim_max)
{
	anim_handl = new Anim_[anim_max];
}

Animation::~Animation()
{

	delete[] anim_handl;
	delete[] m_contexts;
}

// 読み込み
void Animation::Load_Anim(const char file_path[256], int anim_no, int anim_index)
{
	// 読み込み
	anim_handl[anim_no].handl = MV1LoadModel(file_path);
	// アニメションインデックス番号の保存
	anim_handl[anim_no].index = anim_index;
}

void Animation::Attach_Anim(Model* model, int anim_num)
{
	m_contexts[0].animation_attach_index = MV1AttachAnim(model->m_model, anim_handl[anim_num].index, anim_handl[anim_num].handl);
		
}

void Animation::Detach_Anim(Model* model, int anim_num )
{
}

