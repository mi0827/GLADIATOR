#pragma once

// �V�[���N���X�����̃x�[�X�N���X
class Scene_Base
{
public:


	// ��������
	virtual void Init() = 0;
	// �X�V����
	// ����
	// �P�FBGM�̃{�����[��
	// �Q�FSE�̃{�����[��
	virtual void Update(int bgm_volume, int se_volume) = 0;
	// �`�揈��
	virtual void Draw() = 0;
	// �I������
	virtual void Exit() = 0;

	//// ���̃V�[�����玟�̃V�[���ɐ؂�ւ���֐�
	//void Scene_Change_Judge(int* now_scene, int* next_scene);

	//// �t���[�����玞�Ԃɒu��������֐�
	//void Flame_Time_Update(int* flame, int* time);
public:
	const int FLAME_MAX = 60; // ��b���t���[����

	bool scene_change_judge ; // �V�[���̐؂�ւ����s���Ă����� (true�ɂȂ�����V�[���̐؂�ւ��\)

};