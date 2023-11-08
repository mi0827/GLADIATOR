#include "WinMain.h"
#include "GameMain.h"
#include "object.h"
// コンストラクタ（初期化）
// 

#define Vector3 BOX_SIZE{50.0f, 100.0f, 50.0f};

Object::Object()
{

}

//---------------------------------------------------------------------------
// 初期処理
//---------------------------------------------------------------------------
void Object::Init(float* i)
{
	// 円錐関係
	/*m_cone_top_pos.set(0.0f, 30.0f, *i);
	m_cone_bottom_pos.set(0.0f, 0.0f, *i);
	m_cone_r = 5.0f;
	m_cone_color = GetColor(255, 255, 50);*/


	// 立方体関係
	m_cube_size.set(50.0f, 100.0f, 50.0f);                                                   // サイズ
	m_cube_size_half.set(m_cube_size.x / 2.0f, m_cube_size.y / 2.0f, m_cube_size.z / 2.0f);  // サイズの半分のサイズ
	m_cube_bottom_pos.set(0.0f, 0.0f, *i * 0);                                               // 元の位置
	m_cube_top_pos.set(m_cube_bottom_pos.x + m_cube_size.x,                                  // 上の位置
		m_cube_bottom_pos.y + m_cube_size.y,
		m_cube_bottom_pos.z + m_cube_size.z);
	m_cube_color = GetColor(255, 0, 0);                                     // 色
	m_cube_hit_pos.set(m_cube_bottom_pos.x + m_cube_size_half.x, m_cube_bottom_pos.y + m_cube_size_half.y, m_cube_bottom_pos.z + m_cube_size_half.z); // 当たり判定用に描画用の立方体の中心に座標を置いたバージョン
}

void Object::GetScope(int* pos_x, int* pos_z)
{
	scope_pos.x = *pos_x;
	scope_pos.z = *pos_z;
}

void Object::SetPos()
{
	m_cube_bottom_pos.set(0.0f, 0.0f, *i * 0);
}

//---------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------
void Object::Update()
{

}
void Object::CreateObjects()
{

	void CreateObjects(); // オブジェクトを作る関数
}

//---------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------
void Object::Draw()
{
	// 立方体の描画
	DrawCube3D(m_cube_top_pos.VGet(), m_cube_bottom_pos.VGet(), m_cube_color, m_cube_color, TRUE);
}

//---------------------------------------------------------------------------
// 終了処理
//---------------------------------------------------------------------------
void Object::Exit()
{
}
