#pragma once

#include "Base.h"


//	Field(�t�B�[���h)�N���X
// Base�N���X���p��
class Field : public Base
{
	//---------------
	// �萔
	//---------------
private:
	const float MODEL_SIZE = 50.0f; // ���f���T�C�Y


public:
	//---------------
	// �֐��̒�`
	//---------------
	// �R���X�g���N�^
	Field();	//	����������
	void Init();        //�@��������
	void Update();		//	�X�V����
	void Draw();		//	�`�揈��
	void Exit();		//	�I������



	//---------------
	// �ϐ��̒�`
	//---------------
private:
	int m_model; // ���f���p�̕ϐ�
};
