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
	m_model = MV1LoadModel("Data/Model/Field/ground.mv1");
	m_pos.clear(); // �`����W�̐ݒ�
	m_rot.clear(); // ��]�ʂ̐ݒ�
}

void Field::Init()
{
	// �����Ńt�B�[���h���f���̓ǂݍ��݂�����
	m_model = MV1LoadModel("Data/Model/Field/ground.mv1");
	int obj_max = Field_Init();
	
	// �I�u�W�F�N�g�̏�����
	for (int i = 0; i < obj_max; ++i) {
		// ������NEW����
		
		Object* p = new Object;

		// ����������� z_pos �������悤�Ɉ����ɃA�h���X��n��
		p->Init(&z_pos[i]);

		// �ǉ��o�^
		objects.push_back(p);
	}
}

int Field::Field_Init()
{
	// 1���ǂO�������Ȃ�
	// �t�B�[���h�̃I�u�W�F�N�g��u�����W�p�̓񎟌��z��
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

	// ���̃I�u�W�F�N�g���K�v��������
	int object_count=0;
	for (int h = 0; h < MAP_H; h++) {
		for (int w = 0; w < MAP_W; w++) {
			if (MapData[h][w] == 1) {
				object_count++;
			}
		}
	}
	return object_count;
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


