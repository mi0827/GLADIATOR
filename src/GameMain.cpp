#include "WinMain.h"
#include "GameMain.h"
#include "Vector3.h"
#include "Hit.h" // �����蔻��

// �L�����N�^�[.h
#include "Player.h"
#include "Ninja.h"
// �t�B�[���h.h
#include "Field.h"

// �J����.h
#include "Camera.h"

// �I�u�W�F�N�g�N���X
#include "Object.h"

constexpr int PLAYER_MAX = 2; // �v���C���[�̐��A�J�����̐����ꏏ

// �e�N���X�̃I�u�W�F�N�g

CharacterBase* players[2]; // �L�����N�^�[�̓�l�Ăԗp�̔z�� 
Camera* camera[2];         // �L�����N�^�Ɠ�����

Field field;

// ��������(�e�N���X�̃R���X�g���N�^�ł��Ȃ�����)
void GameInit()
{
	players[0] = new Player;
	players[1] = new Ninja;
	camera[0] = new Camera;
	camera[1] = new Camera;
	// �e�N���X�̏����ݒ�
	field.Init();
	field.Field_Init();
	players[0]->Init(0);
	players[1]->Init(1);

	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->PlayField_Init();
	}

}

// �X�V����
void GameUpdate()
{
	// �L�����N�^�[�̈ړ��i�ǎC��j����
	for (int player = 0; player < PLAYER_MAX; player++) {
		players[player]->Update(&camera[player]->m_rot);
		// �����̂ƃv���C���[�̂����蔻��
		for (int i = 0; i < field.obj_max; i++) {
			if (CheckBoxHit3D(players[player]->m_pos, players[player]->m_move_hit_box_size, field.objects[i]->m_cube_hit_pos, field.objects[i]->m_cube_size_half))
			{
				players[player]->m_move_judge = true; // �ړ��Ɏx�Ⴊ�����Ture��Ԃ�
				players[player]->Get_other(&field.objects[i]->m_cube_hit_pos, &field.objects[i]->m_cube_size_half); // Player�ɓ�����������̏���n����
				players[player]->Move_Hit_Update(); // �ǎC��p�̊֐�
			}
			else {
				players[player]->m_move_judge = false;
			}
		}
	}
	// �v���C���[�ƃv���C���[�̈ړ������蔻��
	for (int i = 0; i < field.obj_max; i++) {
		if (CheckBoxHit3D(players[0]->m_pos, players[0]->m_move_hit_box_size, players[1]->m_pos, players[1]->m_move_hit_box_size))
		{
			players[0]->m_move_judge = true; // �ړ��Ɏx�Ⴊ�����Ture��Ԃ�
			players[0]->Get_other(&players[1]->m_pos, &players[1]->m_move_hit_box_size); // Player�ɓ�����������̏���n����
			players[0]->Move_Hit_Update(); // �ǎC��p�̊֐�
		}
		else {
			players[0]->m_move_judge = false;
		}
	}

	// �e�N���X�̍X�V����
	field.Update();	
	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		camera[i]->Update(&players[i]->m_pos);
	}
}

// �`�揈��
void GameDraw()
{
	// �e�N���X�̕`�揈��
	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->Draw_Set();       // �J�����̕`��O�ݒ�i �� �`�揈���̈�ԍŏ��ɂ��邱�Ɓj
		field.Draw();
		// �v���C���\��p�������邽�߂̔z��
		for (int j = 0; j < PLAYER_MAX; j++) {
			players[j]->Draw();
		}
		camera[i]->Draw(i); // �J�����̕`�揈���i �� �`�揈���̈�ԍŌ�ɂ��邱�Ɓj
	}
}

// �I������
void GameExit()
{
	// �e�N���X�̏I������
	for (int i = 0; i < PLAYER_MAX; i++) {
		players[i]->Exit();
		camera[i]->Exit();
	}
	field.Exit();
	// new���Ă����N���X�̉��
	delete[] players;
	delete[] camera;
}
