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

// アニメーションの情報の初期化関数
void Animation::Information_Init(int num)
{
	//アニメーションの情報をすべて初期化しておく
	m_contexts[num].is_playering = false;
	m_contexts[num].is_loop = false;
	m_contexts[num].animation_index = -1;
	m_contexts[num].animation_attach_index = -1;
	m_contexts[num].m_blend_ratio = 0.0f;
	m_contexts[num].animation_total_time = 0.0;
	m_contexts[num].play_time = 0.0f;
}

// アニメーションの初期設定
void Animation::Init_Animation(int anim_max, int default_anim)
{
	// デフォルトアニメーションの設定
	m_default_anim = default_anim;
	// アニメーションの入れ物を配列で確保する
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
	// 入れ物を初期化しておく
	Information_Init(0);

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
	Information_Init(1);
}


// アニメーション切り替え用関数
void Animation::Change_Animation(Model* model, int anim_num , bool loop)
{
	// アニメーションを入れ替える前にもともとついていアニメーションを取り外す
	Detach_Animation(model);
	// 中にはいている情報を入れ替える
	m_contexts[1] = m_contexts[0];

	// 次に行いたいアニメーションをつける
	Attach_Animation(model, anim_num, loop);

	// 次のアニメーションのブレンド率を上げる
	m_contexts[0].m_blend_ratio += 0.1f;
	// 上限の設定
	if (m_contexts[0].m_blend_ratio > 1.0f)
	{
		m_contexts[0].m_blend_ratio = 1.0f;
	}
	// もともとのアニメーションのブレンド率を下げる
	m_contexts[1].m_blend_ratio -= 0.1f;
	// 下限の設定
	if (m_contexts[1].m_blend_ratio < 0)
	{
		m_contexts[1].m_blend_ratio = 0.0f;
	}
}

// アニメーション切り替え用関数（アニメーションが終わるタイミングで切り替える）
void Animation::Action_Change_Animation(Model* model, int anim_num, bool loop)
{
	// アニメーションが最後のフレームに差し掛かったら
	if (m_contexts[0].animation_total_time >= m_contexts[0].play_time)
	{
		Change_Animation(model, anim_num, loop);
	}
}

// アニメーションを再生させるための関数
void Animation::Play_Animation(Model* model)
{

	m_contexts[0].play_time++;
	// ループするかどうかによって処理の変更
	if (m_contexts[0].is_loop)
	{
		Loop_Animation();
	}
	else // ループしない場合
	{
		Not_Loop(model);
	}

	// それぞれにアニメーションの割合分再生します
	for (int i = 0; i < 2; i++)
	{
		MV1SetAttachAnimBlendRate(
			model->m_model,
			m_contexts[i].animation_attach_index,
			m_contexts[i].play_time);
	}
}

// アニメーションをループさせる
void Animation::Loop_Animation()
{

	// アニメーションフレームが最後まで回ったら
	if (m_contexts[0].play_time > m_contexts[0].animation_total_time)
	{
		// 最初にリセットする
		m_contexts[0].play_time = 0.0f;
	}

}

void Animation::Not_Loop(Model* model)
{
	// アニメーションフレームが最後まで回ったら
	if (m_contexts[0].play_time >= m_contexts[0].animation_total_time)
	{
		// デフォルトのアニメーションに設定
		Change_Animation(model, m_default_anim, true);
	}

}


