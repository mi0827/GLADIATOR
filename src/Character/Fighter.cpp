#include "src/WinMain.h"
#include "src/GameMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"
#include "src/System/InputPad.h"
#include "src/Base.h"
#include "src/System/Transform.h"
#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Character/Base/Character_Base.h"
#include "src/Effect/Effect.h"

#include "Fighter.h"

#define PANEL_SIZE	5.0f              // パネルの大きさ
#define PANEL_HALF	(PANEL_SIZE/2.0f) // パネルの半分の大きさ
#define ATTACK_ANIM_SPEED 1.4f

// SEクラスのオブジェクト
SE figher_se;
//Transform transform;
//Model model();
Animation anim;
//---------------------------------------------------------------------------
// コンストラクタ（初期化）
//---------------------------------------------------------------------------

Fighter::Fighter()
{
}

void Fighter::Init(int player_num)
{
	model.LoadModel("Data/Model/Player/Player.mv1");
	if (player_num == 0)
	{
		transform.pos.set(350.0f, 0.0f, 150.0f);           // 初期座標の設定
		transform.rot.set(0.0f, 0.0f, 0.0f);             // 向きの設定
	}
	else
	{
		transform.pos.set(350.0f, 0.0f, 450.0f);            // 初期座標の設定
		transform.rot.set(0.0f, 180.0f, 0.0f);			  // 向きの設定
	}
}

void Fighter::Animation_Init()
{
}

void Fighter::Update(Vector3* camera_rot, int SE_Volume)
{
}
void Fighter::Draw()
{
	model.DrawModel(&transform);
}

void Fighter::Exit()
{
}

void Fighter::SE_Init()
{
}
void Fighter::Move_Hit_Update()
{
}

void Fighter::Attack_PressButton_Update(Vector3* camera_rot)
{
}

void Fighter::Attack_Update()
{
}

void Fighter::Damage_Update(int* m_attack_damage)
{
}

void Fighter::Block_Update()
{
}
