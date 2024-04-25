#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

// ノーマルアニメ用の変数の確保用関数
void Animation::Nomal_Anim_New
(int ANIM_MAX)
{
	m_anim_model = new int[ANIM_MAX];
	m_anim_attach = new int[ANIM_MAX];
	m_anim_total = new float[ANIM_MAX];
	m_anim_rate = new float[ANIM_MAX];
	m_anim_frame = new float[ANIM_MAX];

	//! アニメーションフレームを０からスタートにしておく
	for (int i = 0; i < ANIM_MAX; i++)
	{
		*m_anim_frame = 0.0f;
	}
}

// アタックアニメーション用の変数の確保用関数
void Animation::Attack_Anim_New(int ANIM_MAX)
{
	m_attack_anim_model = new int[ANIM_MAX];   // アニメーションモデル
	m_attack_anim_attach = new int[ANIM_MAX];  // アタッチ用変数
	m_attack_anim_total = new float[ANIM_MAX]; // アニメーションが何フレームあるか
	m_attack_anim_rate = new float[ANIM_MAX];  // アニメーションのブレンド率
	m_attack_anim_frame = new float[ANIM_MAX]; // アニメーションの進めるフレーム
	// アニメーションが何フレーム進んでいるか用の変数
	// 最初は０から開始
	for (int i = 0; i < ANIM_MAX; i++)
	{
		m_attack_anim_frame[i] = 0.0f;
	}

}

// ダメージアニメーション用の変数の確保用関数
void Animation::Damage_Anim_New(int ANIM_MAX)
{
	m_damage_anim_model = new int[ANIM_MAX];   // アニメーションモデル
	m_damage_anim_attach = new int[ANIM_MAX];   // アタッチ用変数
	m_damage_anim_total = new float[ANIM_MAX]; // アニメーションが何フレームあるか
	m_damage_anim_rate = new float[ANIM_MAX]; // アニメーションのブレンド率
	m_damage_anim_frame = new float[ANIM_MAX]; // アニメーションの進めるフレーム
	// アニメーションが何フレーム進んでいるか用の変数
	// 最初は０から開始
	for (int i = 0; i < ANIM_MAX; i++)
	{
		m_damage_anim_frame[i] = 0.0f;
	}
}

// ガードアニメーション用の変数の確保用関数
void Animation::Block_Anim_New(int ANIM_MAX)
{
	m_block_anim_model = new int[ANIM_MAX];   // アニメーションモデル
	m_block_anim_attach = new int[ANIM_MAX];   // アタッチ用変数
	m_block_anim_total = new float[ANIM_MAX]; // アニメーションが何フレームあるか
	m_block_anim_rate = new float[ANIM_MAX]; // アニメーションのブレンド率
	m_block_anim_frame = new float[ANIM_MAX]; // アニメーションの進めるフレーム
	// アニメーションが何フレーム進んでいるか用の変数
	// 最初は０から開始
	for (int i = 0; i < ANIM_MAX; i++)
	{
		m_block_anim_frame[i] = 0.0f;
	}
}

void Animation::Anim_Delete()
{

	//! 普通アニメーション 
	delete[] m_anim_model;
	delete[] m_anim_attach;
	delete[] m_anim_total;
	delete[] m_anim_rate;
	delete[] m_anim_frame;

	//! 攻撃アニメーション
	delete[] m_attack_anim_model;
	delete[] m_attack_anim_attach;
	delete[] m_attack_anim_total;
	delete[] m_attack_anim_rate;
	delete[] m_attack_anim_frame;

	//! ダメージアニメーション
	delete[] m_damage_anim_model;
	delete[] m_damage_anim_attach;
	delete[] m_damage_anim_total;
	delete[] m_damage_anim_rate;
	delete[] m_damage_anim_frame;

	//! ガードアニメーション
	delete[] m_block_anim_model;
	delete[] m_block_anim_attach;
	delete[] m_block_anim_total;
	delete[] m_block_anim_rate;
	delete[] m_block_anim_frame;

}
