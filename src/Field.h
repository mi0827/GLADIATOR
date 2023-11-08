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

	void Field_Init(); // �t�B�[���h�̃I�u�W�F�N�g�̏�����

	void Update();		//	�X�V����
	void Draw();		//	�`�揈��
	void Exit();		//	�I������



	//---------------
	// �ϐ��̒�`
	//---------------
public:
	
	const int field_size_x = 50; 
	const int field_size_y = 50;


	// �t�B�[���h�̃I�u�W�F�N�g��u�����W�p�̓񎟌��z��
	// int* MapData;

	// int* map_num; // map�f�[�^�ɉ��Ԃ������Ă����邩��m�邽�߂̕ϐ�


	
private:
	int m_model; // ���f���p�̕ϐ�
};
