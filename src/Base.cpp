#include "System/WinMain.h"
#include "System/Vector3.h"
#include "System/Vector2.h"
#include "Base.h"

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Base::Base()
{
	m_pos.clear(); // 座標
	m_rot.clear(); // 回転
	m_radius = 0.0f; // 半径
}