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

	int Field_Init(); // �t�B�[���h�̃I�u�W�F�N�g�̏�����

	void Update();		//	�X�V����
	void Draw();		//	�`�揈��
	void Exit();		//	�I������



	//---------------
	// �ϐ��̒�`
	//---------------
public:
	// ��̃}�X�̑傫��
	const int m_field_size = 0;        // �T�C�Y
	const int m_field_size_x = 50; // X�����ɂǂꂾ����
	const int m_field_size_y = 50; // Z�����ɂǂꂾ����

//	int m_field_obj_max = 0; // ���̃I�u�W�F�N�g���K�v��

	// �I�u�W�F�N�g�N���X�^�̃|�C���^�͂��Ă�@
	std::vector<Object*> objects;

	// �I�u�W�F�N�g�̕`��ʒu������ɂ��炷���߂̔z��ϐ�
	//float z_pos[OBJECT_MAX];

	// �t�B�[���h�̃I�u�W�F�N�g��u�����W�p�̓񎟌��z��
	// int* MapData;

	// int* map_num; // map�f�[�^�ɉ��Ԃ������Ă����邩��m�邽�߂̕ϐ�



private:
	int m_model; // ���f���p�̕ϐ�
};
