#include "WinMain.h"
#include "GameMain.h"
#include "object.h"
// コンストラクタ（初期化）
// 

Object::Object()
{

}

//---------------------------------------------------------------------------
// 初期処理
//---------------------------------------------------------------------------
void Object::Init()
{

}

//---------------------------------------------------------------------------
// フィールドに置くオブジェクトの初期処理(立方体関係)
//---------------------------------------------------------------------------
void Object::Field_Object_Init(const int m_field_size, int pos_z, int pos_x)
{
	Vector3 m_field_pos; // フィールド内の一つのスペースの座標を保存する変数

	//=================================
	// 立方体の描画が用座標の設定１(下の位置)
	//=================================
	Vector3 bottom_pos = Set_Cube_Bottom_Pos(m_field_size, pos_z, pos_x, &m_field_pos);
	m_cube_bottom_pos.set(bottom_pos);

	//=================================
	// サイズの設定
	//=================================
	Vector3 size = Rand_Size_Cube(m_field_size, m_field_pos.z, m_field_pos.x); // ランダムに作られたサイズを入れる変数
	m_cube_size.set(size);

	//=================================
	// 当たり判定用の半分のサイズの設定
	//=================================
	m_cube_size_half.set(m_cube_size.x / 2.0f, m_cube_size.y / 2.0f, m_cube_size.z / 2.0f);  // サイズの半分のサイズ

	//=================================
	// 立方体の描画が用座標の設定１(上の位置)
	//=================================
	m_cube_top_pos.set(m_cube_bottom_pos.x + m_cube_size.x, m_cube_bottom_pos.y + m_cube_size.y, m_cube_bottom_pos.z + m_cube_size.z);

	//=================================
	// 色の設定
	//=================================
	m_cube_color = GetColor(25, 25, 25);

	//=================================
	// 当たり判定用の座標の設定
	//=================================
	// 当たり判定用に描画用の立方体の中心に座標を置いたバージョン
	m_cube_hit_pos.set(m_cube_bottom_pos.x + m_cube_size_half.x, m_cube_bottom_pos.y + m_cube_size_half.y, m_cube_bottom_pos.z + m_cube_size_half.z);
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
	SetUseLighting(FALSE);
	// 立方体の描画
	DrawCube3D(m_cube_top_pos.VGet(), m_cube_bottom_pos.VGet(), m_cube_color, m_cube_color, TRUE);
	SetUseLighting(TRUE);
}

//---------------------------------------------------------------------------
// 終了処理
//---------------------------------------------------------------------------
void Object::Exit()
{
}

//---------------------------------------------------------------------------
// 立方体のサイズをランダムできめて返す
//---------------------------------------------------------------------------
Vector3 Object::Rand_Size_Cube(float m_field_size, float filed_pos_z, float filed_pos_x)
{
	Vector3 size; // サイズを一時保存する
	// ランダムで取ってくるサイズの最低の値と最高の値を計算しながらランダムの幅を決める
	size.x = GetRand(m_field_size + (filed_pos_x - 20)) + 20; // Xの幅
	size.y = GetRand(80) + 20;                // Yの高さ
	size.z = GetRand(m_field_size + (filed_pos_z - 20)) + 20; // Zの幅
	return size; // サイズを返す
}

//---------------------------------------------------------------------------
// 立方体のの下の座標（元の座標）を返す
//---------------------------------------------------------------------------
Vector3 Object::Set_Cube_Bottom_Pos(float m_field_size, int pos_z, int pos_x, Vector3* field_pos)
{
	Vector3 bottom_pos; // 座標を一時保存する
	//=====================================================
	// フィールド内の一つのスペースでのランダム座標の設定
	//=====================================================
	field_pos->x = GetRand(m_field_size); // X座標
	field_pos->y = 0.0f;                         // Y座標
	field_pos->z = GetRand(m_field_size); // Z座標

	//========================================================
	// 上でも止めた座標をワールド座標に戻す（全体のフィールド）
	//========================================================
	bottom_pos.x = field_pos->x + (m_field_size * pos_x); // X座標
	bottom_pos.y = 0.0f;								  // Y座標
	bottom_pos.z = field_pos->z + (m_field_size * pos_z); // Z座標

	return bottom_pos;
}
