#include "WinMain.h"
#include "GameMain.h"
#include "object.h"
// �R���X�g���N�^�i�������j
// 

Object::Object()
{

}

//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void Object::Init()
{

}

//---------------------------------------------------------------------------
// �t�B�[���h�ɒu���I�u�W�F�N�g�̏�������(�����̊֌W)
//---------------------------------------------------------------------------
void Object::Field_Object_Init(const int m_field_size, int pos_z, int pos_x)
{
	Vector3 m_field_pos; // �t�B�[���h���̈�̃X�y�[�X�̍��W��ۑ�����ϐ�

	//=================================
	// �����̂̕`�悪�p���W�̐ݒ�P(���̈ʒu)
	//=================================
	Vector3 bottom_pos = Set_Cube_Bottom_Pos(m_field_size, pos_z, pos_x, &m_field_pos);
	m_cube_bottom_pos.set(bottom_pos);

	//=================================
	// �T�C�Y�̐ݒ�
	//=================================
	Vector3 size = Rand_Size_Cube(m_field_size, m_field_pos.z, m_field_pos.x); // �����_���ɍ��ꂽ�T�C�Y������ϐ�
	m_cube_size.set(size);

	//=================================
	// �����蔻��p�̔����̃T�C�Y�̐ݒ�
	//=================================
	m_cube_size_half.set(m_cube_size.x / 2.0f, m_cube_size.y / 2.0f, m_cube_size.z / 2.0f);  // �T�C�Y�̔����̃T�C�Y

	//=================================
	// �����̂̕`�悪�p���W�̐ݒ�P(��̈ʒu)
	//=================================
	m_cube_top_pos.set(m_cube_bottom_pos.x + m_cube_size.x, m_cube_bottom_pos.y + m_cube_size.y, m_cube_bottom_pos.z + m_cube_size.z);

	//=================================
	// �F�̐ݒ�
	//=================================
	m_cube_color = GetColor(25, 25, 25);

	//=================================
	// �����蔻��p�̍��W�̐ݒ�
	//=================================
	// �����蔻��p�ɕ`��p�̗����̂̒��S�ɍ��W��u�����o�[�W����
	m_cube_hit_pos.set(m_cube_bottom_pos.x + m_cube_size_half.x, m_cube_bottom_pos.y + m_cube_size_half.y, m_cube_bottom_pos.z + m_cube_size_half.z);
}

//---------------------------------------------------------------------------
// �X�V����
//---------------------------------------------------------------------------
void Object::Update()
{

}
void Object::CreateObjects()
{

	void CreateObjects(); // �I�u�W�F�N�g�����֐�
}

//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void Object::Draw()
{
	SetUseLighting(FALSE);
	// �����̂̕`��
	DrawCube3D(m_cube_top_pos.VGet(), m_cube_bottom_pos.VGet(), m_cube_color, m_cube_color, TRUE);
	SetUseLighting(TRUE);
}

//---------------------------------------------------------------------------
// �I������
//---------------------------------------------------------------------------
void Object::Exit()
{
}

//---------------------------------------------------------------------------
// �����̂̃T�C�Y�������_���ł��߂ĕԂ�
//---------------------------------------------------------------------------
Vector3 Object::Rand_Size_Cube(float m_field_size, float filed_pos_z, float filed_pos_x)
{
	Vector3 size; // �T�C�Y���ꎞ�ۑ�����
	// �����_���Ŏ���Ă���T�C�Y�̍Œ�̒l�ƍō��̒l���v�Z���Ȃ��烉���_���̕������߂�
	size.x = GetRand(m_field_size + (filed_pos_x - 20)) + 20; // X�̕�
	size.y = GetRand(80) + 20;                // Y�̍���
	size.z = GetRand(m_field_size + (filed_pos_z - 20)) + 20; // Z�̕�
	return size; // �T�C�Y��Ԃ�
}

//---------------------------------------------------------------------------
// �����̂̂̉��̍��W�i���̍��W�j��Ԃ�
//---------------------------------------------------------------------------
Vector3 Object::Set_Cube_Bottom_Pos(float m_field_size, int pos_z, int pos_x, Vector3* field_pos)
{
	Vector3 bottom_pos; // ���W���ꎞ�ۑ�����
	//=====================================================
	// �t�B�[���h���̈�̃X�y�[�X�ł̃����_�����W�̐ݒ�
	//=====================================================
	field_pos->x = GetRand(m_field_size); // X���W
	field_pos->y = 0.0f;                         // Y���W
	field_pos->z = GetRand(m_field_size); // Z���W

	//========================================================
	// ��ł��~�߂����W�����[���h���W�ɖ߂��i�S�̂̃t�B�[���h�j
	//========================================================
	bottom_pos.x = field_pos->x + (m_field_size * pos_x); // X���W
	bottom_pos.y = 0.0f;								  // Y���W
	bottom_pos.z = field_pos->z + (m_field_size * pos_z); // Z���W

	return bottom_pos;
}
