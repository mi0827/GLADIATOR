#pragma once

#include "Base.h"
#include "Object.h"

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
	int Field_Init();   // �t�B�[���h��ɃI�u�W�F�N�g�̒u������Ԃ��֐�
	void Object_Init(); // �I�u�W�F�N�g�̍��W�A�T�C�Y�̏����ݒ�
	void Update();		//	�X�V����
	void Draw();		//	�`�揈��
	void Exit();		//	�I������



	//---------------
	// �ϐ��̒�`
	//---------------
public:
	//---------------
	// �}�b�v���̐ݒ�
	//---------------
	
	// ��̃}�X�̑傫��
	const int m_field_size = 100;   // �T�C�Y
	std::vector<Object*> objects;  // �I�u�W�F�N�g�N���X�^�̃|�C���^�͂��Ă�@
	int obj_max = 0;               // �I�u�W�F�N�g�̐�



private:
	


	int m_model; // ���f���p�̕ϐ�
};
