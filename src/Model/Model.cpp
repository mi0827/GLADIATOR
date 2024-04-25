#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/Base.h"
#include "Model.h"
#include "src/Animation/Animation.h"


// コンストラクタ
Model::Model()
{
	m_model = 0;

}

// デストラクタ
Model::~Model()
{
	// モデルデータの削除
	MV1DeleteModel(m_model);
}

// モデル読み込み関数
void Model::LoadModel(const char data[256])
{
	// モデルの読み込み
	m_model = MV1LoadModel(data);
}

// 描画用関数
void Model::DrawModel()
{
	MV1SetPosition(m_model, VGet(transform.pos.x, transform.pos.y, transform.pos.z)); // 描画するプレイヤーモデルの座標の設定
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(transform.rot.x), TO_RADIAN(transform.rot.y + 180), TO_RADIAN(transform.rot.z))); // モデルの回転
	MV1SetScale(m_model, transform.scale.VGet()); // モデルの大きさ(10分の１のサイズ)
	MV1DrawModel(m_model); // モデルの描画
}

// モデルの座標をもらってくる用関数
Vector3 Model::GetModelPos()
{
	return transform.pos;
}

// モデルの座標をセットする用関数
void Model::SetModelPos(Vector3 pos)
{
	transform.pos.set(pos);
}

// モデルの向きをもらう用関数
Vector3 Model::GetModelRot()
{
	return transform.rot;
}

// モデルに向きをセットするため用関数
void Model::SetModelRot(Vector3 rot)
{
	transform.rot.set(rot);
}

// モデルのスケールを変更するための関数
void Model::SetModelScale(Vector3 scale)
{
	transform.scale.set(scale);
}
