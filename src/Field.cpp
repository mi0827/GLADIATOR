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
	for (int h = 0; h < MAP_H; h++) {
		for (int w = 0; w < MAP_W; w++) {
			map_num = MapData[h][w]; // マップデータに入っていいる番号の取得
			if (map_num != 0) { 

			}
		}
	}
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


