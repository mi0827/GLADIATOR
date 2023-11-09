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

CharacterBase* player_objec[2];

Player player;
Player2 player2;
Field field;
Camera camera;
Camera camera_2;

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
	field.Field_Init();
	player.Init();
	player2.Init();

	camera.PlayField_Init();
	camera_2.PlayField_Init();



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
	// �����̂ƃv���C���[�̂����蔻��
	if (CheckBoxHit3D(player.m_pos, player.m_move_hit_box_size, object[0]->m_cube_hit_pos, object[0]->m_cube_size_half))
	{
		player.m_move_judge = true; // �ړ��Ɏx�Ⴊ����̂�true��Ԃ�
		player.Get_other(&object[0]->m_cube_hit_pos, &object[0]->m_cube_size_half); // Player�ɓ�����������̏���n����
		player.Move_Hit_Update(); // �ǎC��p�̊֐�
	}
	else {
		player.m_move_judge = false;
	}
	

	// �e�N���X�̍X�V����
	player2.Update(&camera.m_rot);
	field.Update();
	camera.Update(&player.m_pos);
	camera_2.Update(&player2.m_pos);
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Update();
	}
}

// �`�揈��
void GameDraw()
{
	// �e�N���X�̕`�揈��
	camera.Draw_Set(); // �J�����̕`��O�ݒ�i �� �`�揈���̈�ԍŏ��ɂ��邱�Ɓj
	field.Draw();
	player.Draw();
	player2.Draw();
	
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Draw();
	}
	camera.Draw(0); // �J�����̕`�揈���i �� �`�揈���̈�ԍŌ�ɂ��邱�Ɓj


	camera_2.Draw_Set();
	field.Draw();
	player.Draw();
	player2.Draw();
	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		object[i]->Draw();
	}

	camera_2.Draw(1);
}

// �I������
void GameExit()
{
	// �e�N���X�̏I������
	player.Exit();
	player2.Exit();
	field.Exit();
	camera.Exit();

	

	// ���������� new �����̂�
	// �����ŉ�����Ă���
	for (int i = 0; i < OBJECT_MAX; ++i) {
		delete object[i];
	}
}
