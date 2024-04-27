#pragma once

/**
* @file Model.h
* @ brief ���f���p�̃N���X
*/
class Model :public Base
{
public:
	//-----------
	// �֐�
	//-----------

	Model();
	~Model();

	/**
	* @fn
	* @brief ���f���ǂݍ��ݗp�֐�
	* @param (data[256]) ���f���f�[�^�̃p�X
	* @detail ���f����ǂݍ��ނ��߂̊֐�
	*/
	void LoadModel(const char data[256]);

	/**
	* @fn
	* @brief ���f���`��p�̊֐�
	* @detail ���f����`�悷�邽�߂̊֐�
	*/
	void DrawModel();

	/**
	* @fn
	* @brief ���f���̍��W��������Ă���p�֐�
	* @return ���݂̃��f���̍��W
	* @detail ���݂̍��W�̃��f����m�邽�ߗp�֐�
	*/
	Vector3 GetModelPos();

	/**
	* @fn
	* @brief ���f���̍��W���Z�b�g����p�֐�
	* @param �Z�b�g���������W
	* @detail �Z�b�g���������W�����f�����ɃZ�b�g����p�֐�
	*/
	void SetModelPos(Vector3 pos);

	/**
	* @fn
	* @brief ���f���̌�����������Ă���p�̊֐�
	* @return ���݂ɂ̃��f���̌���
	* @detail ���݂̃��f���̌�����m�邽�߂̗p�̊֐�
	*/
	Vector3 GetModelRot();

	/**
	* @fn
	* @brief ���f���Ɍ������Z�b�g����p�֐�
	* @param �Z�b�g����������
	* @detail �Z�b�g���������������f�����ɃZ�b�g����p�֐�
	*/
	void SetModelRot(Vector3 rot);

	/**
	* @fn
	* @brief ���f���̃X�P�[�����Z�b�g����p�֐�
	* @param �Z�b�g�������X�P�[��
	* @detail �Z�b�g�������X�P�[�������f�����ɃZ�b�g����p�֐�
	*/
	void SetModelScale(Vector3 rot);

public:

	// �ϐ�

	//! ���f���p�̕ϐ�
	int m_model;

	/**
    * @struct transform
    * ���f���̍��W�A��]�A�X�P�[�����܂Ƃ߂�����
    */
	struct Transform
	{
		Vector3 pos{ 0.0f,0.0f,0.0f };
		Vector3 rot{ 0.0f,0.0f,0.0f };
		Vector3 scale{ 0.1f,0.1f,0.1f };
	};
	Transform transform;


	
};