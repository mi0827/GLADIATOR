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
	// �v���C���[�̏����󂯎��`�ɂ��܂�
	// ����̓v���C���[�̂����ɃJ�������������̏o
	// �v���C���[�̍��W�ƌ������󂯎���悤�ɂ��܂�
	void Update(Vector3* player_pos);		//	�X�V����
	void Draw();		//	�`�揈��
	void Exit();		//	�I������

	//---------------
	// �ϐ��̒�`
	//---------------
private:
	// �J������������W
	Vector3 m_look;

	// �}�E�X�̈ړ��ʗp�̕ϐ�
	float m_mouse_move_x; // X���W�̈ړ���
	float m_mouse_move_y; // Y���W�̈ړ���
};
