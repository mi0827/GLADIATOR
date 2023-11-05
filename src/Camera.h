#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�J�����N���X
// Base�N���X���p��
class Camera : public Base
{
public:
	//---------------
	// �֐��̒�`
	//---------------
	// �R���X�g���N�^
	Camera();

	void Init();        //�@��������

	void PlayField_Init(); // �v���C��ʂ̏����ݒ�

	// �v���C���[�̏����󂯎��`�ɂ��܂�
	// ����̓v���C���[�̂����ɃJ�������������̏o
	// �v���C���[�̍��W�ƌ������󂯎���悤�ɂ��܂�
	void Update(Vector3* player_pos);		//	�X�V����
	void Draw_Set();    // �`�揈���̑O�ɃJ�����A��ʂ̃Z�b�g
	void Draw(int camera_No);		//	�`�揈��
	void Exit();		//	�I������

	//---------------
	// �ϐ��̒�`
	//---------------
private:
	// �J������������W
	Vector3 m_look;

	//--------------------
	// ��ʕ����p�̕ϐ�
	int m_screen_field;   // �`�悷���ʂ�����摜�p�ϐ�
	Vector2 m_field_pos;  // �`�悷����W
	Vector2 m_field_size; // �`�悷��T�C�Y


	// �}�E�X�̈ړ��ʗp�̕ϐ�
	float m_mouse_move_x; // X���W�̈ړ���
	float m_mouse_move_y; // Y���W�̈ړ���
};
