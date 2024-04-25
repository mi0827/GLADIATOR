#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/Base.h"
#include "Model.h"
#include "src/Animation/Animation.h"


// �R���X�g���N�^
Model::Model()
{
	m_model = 0;

}

// �f�X�g���N�^
Model::~Model()
{
	// ���f���f�[�^�̍폜
	MV1DeleteModel(m_model);
}

// ���f���ǂݍ��݊֐�
void Model::LoadModel(const char data[256])
{
	// ���f���̓ǂݍ���
	m_model = MV1LoadModel(data);
}

// �`��p�֐�
void Model::DrawModel()
{
	MV1SetPosition(m_model, VGet(transform.pos.x, transform.pos.y, transform.pos.z)); // �`�悷��v���C���[���f���̍��W�̐ݒ�
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(transform.rot.x), TO_RADIAN(transform.rot.y + 180), TO_RADIAN(transform.rot.z))); // ���f���̉�]
	MV1SetScale(m_model, transform.scale.VGet()); // ���f���̑傫��(10���̂P�̃T�C�Y)
	MV1DrawModel(m_model); // ���f���̕`��
}

// ���f���̍��W��������Ă���p�֐�
Vector3 Model::GetModelPos()
{
	return transform.pos;
}

// ���f���̍��W���Z�b�g����p�֐�
void Model::SetModelPos(Vector3 pos)
{
	transform.pos.set(pos);
}

// ���f���̌��������炤�p�֐�
Vector3 Model::GetModelRot()
{
	return transform.rot;
}

// ���f���Ɍ������Z�b�g���邽�ߗp�֐�
void Model::SetModelRot(Vector3 rot)
{
	transform.rot.set(rot);
}

// ���f���̃X�P�[����ύX���邽�߂̊֐�
void Model::SetModelScale(Vector3 scale)
{
	transform.scale.set(scale);
}
