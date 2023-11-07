#pragma once
#include"Base.h"

class Object : public Base
{
public:
	//---------------
	// �֐��̒�`
	//---------------
	// �e�֐��̒�`
	Object();// �R���X�g���N�^



	void Init(float* i);        //�@��������
	void Update();		//	�X�V����
	void CreateObjects(); // �I�u�W�F�N�g�����֐�
	void Draw();		//	�`�揈��
	void Exit();		//	�I������

	//---------------
	// �ϐ��̒�`
	//---------------
private:
	//-------------------------------------------------
	// �~���֘A
	Vector3 m_cone_top_pos;    // �~���̒��_���W
	Vector3 m_cone_bottom_pos; // �~���̒�ӂ̒��S���W
	float   m_cone_r;          // �~���̒��S���W
	float   m_cone_color;      // �F 

public:
	//--------------------------
	// �����̊֘A
	Vector3 m_cube_top_pos;     // �����̂̏�̍��W
	Vector3 m_cube_bottom_pos;  // �����̂̉��̍��W
	Vector3 m_cube_hit_pos;     // �����蔻��p�̍��W�icube�̒��S���瓖���蔻����Ƃ邽�߁j
	Vector3 m_cube_size;        // �T�C�Y
	Vector3 m_cube_size_half;   // �T�C�Y�̔����̃T�C�Y�icube�̒��S���瓖���蔻����Ƃ邽�߁j
	float   m_cube_color;       // �F
};