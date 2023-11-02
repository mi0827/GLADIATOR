#include "WinMain.h"
#include "GameMain.h"
#include "Vector3.h"
#include "Hit.h" // �����蔻��

// �L�����N�^�[.h
#include "Player.h"
#include "Player2.h"
// �t�B�[���h.h
#include "Field.h"

// �J����.h
#include "Camera.h"

// �I�u�W�F�N�g�N���X
#include "Object.h"

// �e�N���X�̃I�u�W�F�N�g
Player player;
Player2 player2;
Field field;
Camera camera;

// �I�u�W�F�N�g�̐�
const int OBJECT_MAX = 1;

// �I�u�W�F�N�g�N���X�^�̃|�C���^�͂��Ă�@
Object* object[OBJECT_MAX];

// �I�u�W�F�N�g�̕`��ʒu������ɂ��炷���߂̔z��ϐ�
float z_pos[OBJECT_MAX];



// ��������(�e�N���X�̃R���X�g���N�^�ł��Ȃ�����)
void GameInit()
{
	// �e�N���X�̏����ݒ�
	field.Init();
	player.Init();
	player2.Init();

	// �ǂꂾ�����炷���̐ݒ�
	for (int i = 0; i < OBJECT_MAX; ++i) {
		z_pos[i] = i * 20.0f;
	}

	// �I�u�W�F�N�g�̏�����
	for (int i = 0; i < OBJECT_MAX; ++i) {
		// ������NEW����
		object[i] = new Object;
		// ����������� z_pos �������悤�Ɉ����ɃA�h���X��n��
		object[i]->Init(&z_pos[i]);
	}
}

// �X�V����
void GameUpdate()
{
	player.Update(&camera.m_rot);
	if (CheckBoxHit3D(player.m_pos, player.m_move_hit_box_size, object[0]->m_cube_hit_pos, object[0]->m_cube_size_half))
	{
		player.m_move_judge = true; // �ړ��Ɏx�Ⴊ����̂�true��Ԃ�
		player.Get_other(&object[0]->m_cube_hit_pos, &object[0]->m_cube_size_half); // Player�ɓ�����������̏���n����
	}
	else {
		player.m_move_judge = false;
	}

	// �e�N���X�̍X�V����
	player.move2(&camera.m_rot);
	player2.Update(&camera.m_rot);
	field.Update();
	camera.Update(&player.m_pos);
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Update();
	}

	// �����ł����蔻�������

	// �����̓��m�̓����蔻��( TRUE:�������Ă��� FALSE:�������Ă��Ȃ� )

	

	

	// �e�ƃJ�v�Z���̓����蔻��(���̓J�v�Z�����Ȃ�)
	//if (player.bead_pos != NULL) {
	//	if (HitCheck_Sphere_Capsule(player.bead_pos->VGet(), 2, VGet(50.0f, 10.0f, 0.0f), VGet(50.0f, 100.0f, 0.0f), 40.0f)) {
	//		player.bead_hit_judg = true; // ��������
	//	}
	//	else {
	//		player.bead_hit_judg = false; // �������ĂȂ�
	//	}
	//}
}

// �`�揈��
void GameDraw()
{
	// �e�N���X�̕`�揈��
	field.Draw();
	player.Draw();
	player2.Draw();
	camera.Draw();
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Draw();
	}
}

// �I������
void GameExit()
{
	// �e�N���X�̏I������
	player.Exit();
	player2.Exit();
	field.Exit();
	camera.Exit();

	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Exit();
	}

	// ���������� new �����̂�
	// �����ŉ�����Ă���
	for (int i = 0; i < OBJECT_MAX; ++i) {
		delete object[i];
	}
}
