#include "WinMain.h"
#include "GameMain.h"
#include "Field.h"
#include "Object.h"

// �t�B�[���h�̃I�u�W�F�N�g��u�����W 
constexpr int MAP_W = 10;  // �c
constexpr int MAP_H = 10;  // ��

//	����������
Field::Field()
{
	// �����Ńt�B�[���h���f���̓ǂݍ��݂�����
	m_model =  MV1LoadModel("Data/Model/Field/ground.mv1");
	m_pos.clear(); // �`����W�̐ݒ�
	m_rot.clear(); // ��]�ʂ̐ݒ�
}

void Field::Init()
{
	// �����Ńt�B�[���h���f���̓ǂݍ��݂�����
	m_model = MV1LoadModel("Data/Model/Field/ground.mv1");
}

void Field::Field_Init()
{
	for (int h = 0; h < MAP_H; h++) {
		for (int w = 0; w < MAP_W; w++) {
			map_num = MapData[h][w]; // �}�b�v�f�[�^�ɓ����Ă�����ԍ��̎擾
			if (map_num != 0) { 

			}
		}
	}
}

//	�X�V����
void Field::Update()
{
	
}

//	�`�揈��
void Field::Draw()
{
	// �t�B�[���h���f���̕`����W
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
	// �t�B�[���h�̉�]
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y), TO_RADIAN(m_rot.z)));
	// ���f���̑傫��
	MV1SetScale(m_model, VGet(MODEL_SIZE, MODEL_SIZE, MODEL_SIZE));
	// ���f���̕`��
	MV1DrawModel(m_model);

	// 3D��ɐ��̕`��
	DrawLine3D(VGet(-50.0f, 0.0f, 0.0f), VGet(50.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(0.0f, 0.0f, -50.0f), VGet(0.0f, 0.0f, 50.0f), GetColor(0, 0, 255));
}

//	�I������
void Field::Exit()
{
	// ���f���f�[�^�̍폜
	MV1DeleteModel(m_model);
}


