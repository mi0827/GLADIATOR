#include "WinMain.h"
#include "GameMain.h"
#include "object.h"
// �R���X�g���N�^�i�������j
// 

#define Vector3 BOX_SIZE{50.0f, 100.0f, 50.0f};

Object::Object()
{

}

//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void Object::Init(float* i)
{
	// �~���֌W
	/*m_cone_top_pos.set(0.0f, 30.0f, *i);
	m_cone_bottom_pos.set(0.0f, 0.0f, *i);
	m_cone_r = 5.0f;
	m_cone_color = GetColor(255, 255, 50);*/


	// �����̊֌W
	m_cube_size.set(50.0f, 100.0f, 50.0f);                                                   // �T�C�Y
	m_cube_size_half.set(m_cube_size.x / 2.0f, m_cube_size.y / 2.0f, m_cube_size.z / 2.0f);  // �T�C�Y�̔����̃T�C�Y
	m_cube_bottom_pos.set(0.0f, 0.0f, *i * 0);                                               // ���̈ʒu
	m_cube_top_pos.set(m_cube_bottom_pos.x + m_cube_size.x,                                  // ��̈ʒu
		m_cube_bottom_pos.y + m_cube_size.y,
		m_cube_bottom_pos.z + m_cube_size.z);
	m_cube_color = GetColor(255, 0, 0);                                     // �F
	m_cube_hit_pos.set(m_cube_bottom_pos.x + m_cube_size_half.x, m_cube_bottom_pos.y + m_cube_size_half.y, m_cube_bottom_pos.z + m_cube_size_half.z); // �����蔻��p�ɕ`��p�̗����̂̒��S�ɍ��W��u�����o�[�W����
}

void Object::GetScope(int* pos_x, int* pos_z)
{
	scope_pos.x = *pos_x;
	scope_pos.z = *pos_z;
}

void Object::SetPos()
{
	m_cube_bottom_pos.set(0.0f, 0.0f, *i * 0);
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
	// �����̂̕`��
	DrawCube3D(m_cube_top_pos.VGet(), m_cube_bottom_pos.VGet(), m_cube_color, m_cube_color, TRUE);
}

//---------------------------------------------------------------------------
// �I������
//---------------------------------------------------------------------------
void Object::Exit()
{
}
