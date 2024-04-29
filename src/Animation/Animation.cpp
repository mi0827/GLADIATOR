#include "src/WinMain.h"
#include "src/Model/Model.h"
#include "Animation.h"


using namespace std;

// コンストラクタ
Animation::Animation()
{

}


// デストラクタ
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

// 読み込み
void Animation::Load_Animation(const char file_path[256], int anim_no, int anim_index)
{
	// 読み込み
	anim_handle[anim_no]->handle = MV1LoadModel(file_path);
	// アニメションインデックス番号の保存
	anim_handle[anim_no]->index = anim_index;
}


// アニメーションのセット
void Animation::Attach_Animation(Model* model, int anim_num, bool loop)
{
	// アニメションのセット
	m_contexts[0].animation_attach_index = MV1AttachAnim
	(
		model->m_model,
		anim_handle[anim_num]->index,
		anim_handle[anim_num]->handle
	);


	// アニメーション総再生フレームの取得
	m_contexts[0].animation_total_time = MV1GetAttachAnimTotalTime
	(
		model->m_model,
		m_contexts[0].animation_attach_index
	);


	// ブレンド率の取得
	m_contexts[0].m_blend_ratio = MV1GetAttachAnimBlendRate
	(
		model->m_model,
		m_contexts[0].animation_attach_index
	);

	// ループするかどうか
	m_contexts[0].is_playering = loop;

}

// アニメーションの取り外し
void Animation::Detach_Animation(Model* model)
{
	// アニメーションをの取り外し
	m_contexts[1].animation_attach_index = MV1DetachAnim
	(model->m_model,
		m_contexts[1].animation_attach_index);
	// 取り外したアニメーションの情報をすべて初期化しておく
	m_contexts[1].is_playering = false;
	m_contexts[1].is_loop = false;
	m_contexts[1].animation_index = -1;
	m_contexts[1].animation_attach_index = -1;
	m_contexts[1].m_blend_ratio = 0.0f;
	m_contexts[1].animation_total_time = 0.0;
	m_contexts[1].play_time = 0.0f;
	
}


// アニメーション切り替え用関数
void Animation::Change_Animation(Model* model, int anim_num)
{
	// 中にはいている情報を入れ替える
	m_contexts[1] = m_contexts[0];
}


// アニメーションを再生させるための関数
void Animation::Play_Animation()
{

}


