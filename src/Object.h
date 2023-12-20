#pragma once


class Object : public Base
{
public:
	//---------------
	// �֐��̒�`
	//---------------
	// �e�֐��̒�`
	Object();// �R���X�g���N�^



	void Init(); //�@��������
	void Field_Object_Init(const int m_field_size, int pos_x, int pos_z);       // �t�B�[���h�ɒu���I�u�W�F�N�g�̏����ݒ�
	void Field_Wall_Object_Init(const int m_field_size, int pos_x, int pos_z);  // �t�B�[���h�̕ǂ̃I�u�W�F�N�g�̏����ݒ�
	void Update();		//	�X�V����
	//void CreateObjects(); // �I�u�W�F�N�g�����֐�
	void Draw();		//	�`�揈��
	void Exit();		//	�I������


	Vector3 Rand_Size_Cube(float m_field_size, float filed_pos_z, float filed_pos_x); // �����̂̃T�C�Y�������_���ł��߂ĕԂ��֐�
	Vector3 Set_Size_Cube(float field_Wall_size, float filed_pos_z, float filed_pos_x);  // �����̂̃T�C�Y��ݒ肷��
	Vector3 Set_Cube_Bottom_Pos( float field_Wall_size, int pos_z, int pos_x, Vector3* field_pos); // �����̂̉��̍��W�i���̍��W�j��Ԃ��֐�
	//---------------
	// �ϐ��̒�`
	//---------------
public:

	Vector3 scope_pos;


private:
	//-------------------------------------------------
	// �~���֘A
	Vector3 m_cone_top_pos;    // �~���̒��_���W
	Vector3 m_cone_bottom_pos; // �~���̒�ӂ̒��S���W
	float   m_cone_r;          // �~���̒��S���W
	int   m_cone_color;      // �F 

public:
	//--------------------------
	// �����̊֘A
	Vector3 m_cube_top_pos;     // �����̂̏�̍��W
	Vector3 m_cube_bottom_pos;  // �����̂̉��̍��W
	Vector3 m_cube_hit_pos;     // �����蔻��p�̍��W�icube�̒��S���瓖���蔻����Ƃ邽�߁j
	Vector3 m_cube_size;        // �T�C�Y
	Vector3 m_cube_size_half;   // �T�C�Y�̔����̃T�C�Y�icube�̒��S���瓖���蔻����Ƃ邽�߁j
	int   m_cube_color;         // �����̂̐F
	int   m_line_color;         // ���C���̐F
};