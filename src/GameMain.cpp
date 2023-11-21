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
	// �v���C���[�O�ɃJ�����O������
	// �v���C���[�P�ɃJ�����P������
	camera[0] = new Camera;
	camera[1] = new Camera;
	// �e�N���X�̏����ݒ�
	field.Init();
	field.Field_Init();
	players[0]->Init(0);
	players[1]->Init(1);
	// �Q�[���p�b�h�̐ݒ�
	players[0]->SetPadNo(DX_INPUT_PAD1);
	players[1]->SetPadNo(DX_INPUT_PAD2);


	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->PlayField_Init();
	}
	// �Q�[���p�b�h�̐ݒ�
	camera[0]->SetPadNo(DX_INPUT_PAD1);
	camera[1]->SetPadNo(DX_INPUT_PAD2);
}

// �X�V����
void GameUpdate()
{
	
	Move_Hit(); // �L�����N�^�[�̈ړ����̂����蔻����s�p
	Attack_Hit(); // �����蔻�������֐�

	// �e�N���X�̍X�V����
	field.Update();
	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		camera[i]->Update(&players[i]->m_pos);
		
	}
	/*for (int i = 0; i < PLAYER_MAX; ++i)
	{
		for (int j = 0; j < field.obj_max; j++) {
			camera[i]->Hit_Object(&field.objects[j]->m_cube_hit_pos, &field.objects[j]->m_cube_size_half);
		}

	}*/
}

// �`�揈��
void GameDraw()
{
	// �e�N���X�̕`�揈��
	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->Draw_Set();       // �J�����̕`��O�ݒ�i �� �`�揈���̈�ԍŏ��ɂ��邱�Ɓj
		field.Draw();
		
		// �v���C���\��`�悳���邽�߂̔z��
		for (int j = 0; j < PLAYER_MAX; j++) {
			players[j]->Draw();
		}
		players[i]->Draw_Status();
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
	for (int i = 0; i < PLAYER_MAX; i++) {
		delete players[i];
		players[i] = nullptr;
		delete camera[i];
		camera[i] = nullptr;
	}
	
}


//---------------------------------------------------------------------------
// �L�����N�^�[�̈ړ������蔻����s�p�֐�
//---------------------------------------------------------------------------
void Move_Hit()
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
	if (CheckBoxHit3D(players[0]->m_pos, players[0]->m_move_hit_box_size, players[1]->m_pos, players[1]->m_move_hit_box_size))
	{
		players[0]->m_move_judge = true; // �ړ��Ɏx�Ⴊ�����Ture��Ԃ�
		players[0]->Get_other(&players[1]->m_pos, &players[1]->m_move_hit_box_size); // Player�ɓ�����������̏���n����
		players[0]->Move_Hit_Update(); // �ǎC��p�̊֐�
	}
	else {
		players[0]->m_move_judge = false;
	}
	// �v���C���[�ƃv���C���[�̈ړ������蔻��
	if (CheckBoxHit3D(players[1]->m_pos, players[1]->m_move_hit_box_size, players[0]->m_pos, players[0]->m_move_hit_box_size))
	{
		players[1]->m_move_judge = true; // �ړ��Ɏx�Ⴊ�����Ture��Ԃ�
		players[1]->Get_other(&players[0]->m_pos, &players[0]->m_move_hit_box_size); // Player�ɓ�����������̏���n����
		players[1]->Move_Hit_Update(); // �ǎC��p�̊֐�
	}
	else {
		players[0]->m_move_judge = false;
	}

}
//---------------------------------------------------------------------------
// �U���̂����蔻����Ƃ�֐�
//---------------------------------------------------------------------------
void Attack_Hit()
{
	if (players[0]->cd_hit_flag) {
		if (HitCheck_Capsule_Capsule(players[0]->m_hit_cd_pos_top.VGet(), players[0]->m_hit_body_pos_under.VGet(), players[0]->m_hit_cd_r,
			players[1]->m_hit_body_pos_top.VGet(), players[1]->m_hit_body_pos_under.VGet(), players[1]->m_hit_body_r))
		{
			players[1]->m_pos.z += 5;
			players[1]->m_hp_count.x -= 50;//players[0]->attack_damage[players[0]->];
		}
	}
}

//---------------------------------------------------------------------------
// �L�����N�^�[�̃X�e�[�^�X�`�揈��
//---------------------------------------------------------------------------
void Draw_Status()
{
	DrawBox(players[0]->m_hp_pos.x, players[0]->m_hp_pos.y, players[0]->m_hp_count.x, players[0]->m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(players[0]->m_hp_pos.x, players[0]->m_hp_pos.y, HP_MAX, players[0]->m_hp_count.y, GetColor(255, 255, 255));

	DrawBox(SCREEN_W / 2 + players[1]->m_hp_pos.x, players[1]->m_hp_pos.y, SCREEN_W / 2 + players[1]->m_hp_count.x, players[1]->m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(SCREEN_W / 2 + players[1]->m_hp_pos.x, players[1]->m_hp_pos.y, SCREEN_W / 2 + HP_MAX, players[1]->m_hp_count.y, GetColor(255, 255, 255));
}