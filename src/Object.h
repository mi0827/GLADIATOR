#pragma once


class Object : public Base
{
public:
	//---------------
	// 関数の定義
	//---------------
	// 各関数の定義
	Object();// コンストラクタ



	void Init(); //　初期処理
	void Field_Object_Init(const int m_field_size, int pos_x, int pos_z);       // フィールドに置くオブジェクトの初期設定
	void Field_Wall_Object_Init(const int m_field_size, int pos_x, int pos_z);  // フィールドの壁のオブジェクトの初期設定
	void Update();		//	更新処理
	//void CreateObjects(); // オブジェクトを作る関数
	void Draw();		//	描画処理
	void Exit();		//	終了処理


	Vector3 Rand_Size_Cube(float m_field_size, float filed_pos_z, float filed_pos_x); // 立方体のサイズをランダムできめて返す関数
	Vector3 Set_Size_Cube(float field_Wall_size, float filed_pos_z, float filed_pos_x);  // 立方体のサイズを設定する
	Vector3 Set_Cube_Bottom_Pos( float field_Wall_size, int pos_z, int pos_x, Vector3* field_pos); // 立方体の下の座標（元の座標）を返す関数
	//---------------
	// 変数の定義
	//---------------
public:

	Vector3 scope_pos;


private:
	//-------------------------------------------------
	// 円錐関連
	Vector3 m_cone_top_pos;    // 円錐の頂点座標
	Vector3 m_cone_bottom_pos; // 円錐の底辺の中心座標
	float   m_cone_r;          // 円錐の中心座標
	int   m_cone_color;      // 色 

public:
	//--------------------------
	// 立方体関連
	Vector3 m_cube_top_pos;     // 立方体の上の座標
	Vector3 m_cube_bottom_pos;  // 立方体の下の座標
	Vector3 m_cube_hit_pos;     // 当たり判定用の座標（cubeの中心から当たり判定をとるため）
	Vector3 m_cube_size;        // サイズ
	Vector3 m_cube_size_half;   // サイズの半分のサイズ（cubeの中心から当たり判定をとるため）
	int   m_cube_color;         // 立方体の色
	int   m_line_color;         // ラインの色
};