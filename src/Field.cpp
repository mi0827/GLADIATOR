#include "WinMain.h"
#include "GameMain.h"
#include "Field.h"
#include "Object.h"

// フィールドのオブジェクトを置く座標 
constexpr int MAP_W = 10;  // 縦
constexpr int MAP_H = 10;  // 横

//	初期化処理
Field::Field()
{
	// ここでフィールドモデルの読み込みをする
	m_model =  MV1LoadModel("Data/Model/Field/ground.mv1");
	m_pos.clear(); // 描画座標の設定
	m_rot.clear(); // 回転量の設定
}

void Field::Init()
{
	// ここでフィールドモデルの読み込みをする
	m_model = MV1LoadModel("Data/Model/Field/ground.mv1");
}

void Field::Field_Init()
{
	// 1が壁０が何もない
	// フィールドのオブジェクトを置く座標用の二次元配列
	int MapData[MAP_H][MAP_W]
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,1,1,0,0,0,0,1 },
		{ 1,0,0,1,1,0,0,0,0,1 },
		{ 1,0,0,1,1,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
	};
}

//	更新処理
void Field::Update()
{
	
}

//	描画処理
void Field::Draw()
{
	// フィールドモデルの描画座標
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
	// フィールドの回転
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y), TO_RADIAN(m_rot.z)));
	// モデルの大きさ
	MV1SetScale(m_model, VGet(MODEL_SIZE, MODEL_SIZE, MODEL_SIZE));
	// モデルの描画
	MV1DrawModel(m_model);

	// 3D状に線の描画
	DrawLine3D(VGet(-50.0f, 0.0f, 0.0f), VGet(50.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(0.0f, 0.0f, -50.0f), VGet(0.0f, 0.0f, 50.0f), GetColor(0, 0, 255));
}

//	終了処理
void Field::Exit()
{
	// モデルデータの削除
	MV1DeleteModel(m_model);
}


