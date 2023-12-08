#include "WinMain.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Hit.h" // �����蔻��
#include "Base.h"
// �L�����N�^�[.h
#include "Character_Base.h"
#include "Player.h"
#include "Ninja.h"
// �I�u�W�F�N�g�N���X
#include "Object.h"
// �t�B�[���h.h
#include "Field.h"
// �J����.h
#include "Camera.h"

#include "Scene_Base.h"
#include "GameScene.h"
constexpr int PLAYER_MAX = 2; // �v���C���[�̐��A�J�����̐����ꏏ

// �e�N���X�̃I�u�W�F�N�g

CharacterBase* players[2]; // �L�����N�^�[�̓�l�Ăԗp�̔z�� 
Camera* camera[2];         // �L�����N�^�Ɠ�����

Field field;


constexpr int TIME_MAX = 90;  // �������� (������10�b)
constexpr int END_TIME_MAX = 3; // �G���h�̎��Ԑ���


//------------------------------------------
// �Q�[���J�n�̍ŏ��̐ݒ�
//------------------------------------------
GameScene::GameScene()
{	

}

//------------------------------------------------
// ��������(�e�N���X�̃R���X�g���N�^�ł��Ȃ�����)
//------------------------------------------------
void GameScene::Init()
{
	players[0] = new Player;
	players[1] = new Player;
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
	players[0]->SetPadNo(PAD_NO::PAD_NO1);//DX_INPUT_PAD1);
	players[1]->SetPadNo(PAD_NO::PAD_NO2);//DX_INPUT_PAD2);

	for (int i = 0; i < PLAYER_MAX; i++) {
		camera[i]->PlayField_Init();
	}
	// �Q�[���p�b�h�̐ݒ�
	camera[0]->SetPadNo(DX_INPUT_PAD1);
	camera[1]->SetPadNo(DX_INPUT_PAD2);

	// �ŏ��̓}�b�N�X�l����n�߂�
	time_count = TIME_MAX;      // �^�C�}�[�̐ݒ�
	flame_count = FLAME_MAX;    // �t���[���J�E���g�̐ݒ�
	end_count = END_TIME_MAX;   // �G���h�ɍs���܂ł̃J�E���g�_�E��
	scene_change_judge = false; // �ŏ��̓V�[���̐؂�ւ������Ă͂����Ȃ�
	status_flag = false;        // �ŏ��̓X�e�[�^�X�X�V�����Ăق����Ȃ�
	play_scene = Play_Tutorial; // �ŏ��̓`���[�g���A���V�[��

}

//----------------------------------------
// �X�V����
//----------------------------------------
void GameScene::Update()
{

	Character_Update(); // �L�����N�^�[�����̍X�V����

	// �e�N���X�̍X�V����
	field.Update();
	for (int i = 0; i < PLAYER_MAX; ++i)
	{
		camera[i]->Update(&players[i]->m_pos);
	}

	switch (play_scene)
	{
	case Play_Tutorial:
		status_flag = false;        // �X�e�[�^�X�X�V�����Ăق����Ȃ�
		Tutorial_Update();
		break;
	case Play_Main:
		status_flag = true;         // �X�e�[�^�X�X�V�����Ăق����Ȃ�
		PlayMain_Update();
		break;
	case Play_End:
		status_flag = false;        // �ŏ��̓X�e�[�^�X�X�V�����Ăق����Ȃ�
		PlayEnd_Update();
		break;
	};
}

//-------------------------------------
// �`�揈��
//-------------------------------------
void GameScene::Draw()
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

	switch (play_scene)
	{
	case Play_Tutorial:
		Tutorial_Draw();          
		break;
	case Play_Main:
		Time_Draw();               // �^�C�}�[��`�悷��̂̓v���C������
		break;
	case Play_End:
		End_Draw();
		break;
	};
	
}

//------------------------------------
// �`�揈��
//------------------------------------
void GameScene::Exit()
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

//------------------------------------
// �`���[�g���A���̍X�V����
//------------------------------------
void GameScene::Tutorial_Update()
{
	// �X�y�[�X�L�[�������ꂽ��
	if (CheckHitKey(KEY_INPUT_SPACE)) 
	{
		for (int i = 0; i < PLAYER_MAX; i++) 
		{
			players[i]->Reset_Status(); // �X�e�[�^�X�����Z�b�g���Ă���
		}

		play_scene = Play_Main; // �v���C���C���Ɉړ�
	}
}

//------------------------------------
// ���C���v���C�V�[���̍X�V����
//------------------------------------
void GameScene::PlayMain_Update()
{
	int player1 = 0;
	int player2 = 1;
	bool is_both_no_guard =	// �����Ƃ��U����
		(
			players[player1]->block_flag == false &&
			players[player2]->block_flag == false
			);
	bool is_player1_guard =	// �v���C���[1���K�[�h��
		(
			players[player1]->block_flag == true &&
			players[player2]->attack_flag == true
			);
	bool is_player2_guard =	// �v���C���[2���K�[�h��
		(
			players[player1]->attack_flag == true &&
			players[player2]->block_flag == true
			);

	// �v���C���[1�̍U���ƃv���C���[2�̍U��
	if (is_both_no_guard == true)
	{
		// �ʏ�̓����蔻����s��
		Attack_Hit(player1, player2);
		Attack_Hit(player2, player1);
	}
	// �v���C���[1�̃K�[�h�ƃv���C���[2�̍U��
	else if (is_player1_guard == true)
	{
		Block_Hit(player1, player2);
	}
	// �v���C���[1�̍U���ƃv���C���[2�̃K�[�h
	else if (is_player2_guard)
	{
		Block_Hit(player2, player1);
	}

	Time_Update(time_count); // �^�C�}�[�̍X�V
	// �^�C�}�[���O�ɂȂ�����
	if (time_count == 0) {
		play_scene = Play_End; // �v���C�G���h�ɐi��
	}
}

//------------------------------------
// �v���C�G���h�̍X�V����
//------------------------------------
void GameScene::PlayEnd_Update()
{
	Time_Update(end_count);

	Play_Victory(players[0],players[1]);

	if (end_count <= 0) 
	{
		end_count = 0;
		// �^�C�}�[���I�������
		scene_change_judge = true; // �V�[���̐؂�ւ���������
	}
}

//---------------------------------------------------------------------------
// ���҂����߂�֐�
//---------------------------------------------------------------------------
void GameScene::Play_Victory(CharacterBase* character1, CharacterBase* character2)
{
	// hp���킩��₷���悤�ɂ���
	float hp1 = character1->m_now_hp;
	float hp2 = character2->m_now_hp;

	if (hp1 == hp2) {
		// �c��hp�������Ȃ�
	}
	if (hp1 > hp2)
	{
		// hp1�̂ق����c��hp���������ꍇ
	}
	if(hp2 > hp1)
	{
		// hp2�̂ق����c��hp���������ꍇ
	}
}

//---------------------------------------------------------------------------
// �L�����N�^�[�̍X�V�����i�ړ����̂��݂��̂����蔻��j
//---------------------------------------------------------------------------
void GameScene::Character_Update()
{
	// �L�����N�^�[�̈ړ��i�ǎC��j����
	for (int player = 0; player < PLAYER_MAX; player++) {
		players[player]->Update(&camera[player]->m_rot/*, status_flag*/);
		// �����̂ƃv���C���[�̂����蔻��
		for (int i = 0; i < field.obj_max; i++) {
			if (CheckBoxHit3D(players[player]->m_pos, players[player]->m_move_hit_box_size, field.objects[i]->m_cube_hit_pos, field.objects[i]->m_cube_size_half))
			{
				players[player]->m_move_judge = true; // �ړ��Ɏx�Ⴊ�����Ture��Ԃ�
				players[player]->Get_other(&field.objects[i]->m_cube_hit_pos, &field.objects[i]->m_cube_size_half); // Player�ɓ�����������̏���n����
				players[player]->Move_Hit_Update();   // �ǎC��p�̊֐�
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
		players[0]->Move_Hit_Update();   // �ǎC��p�̊֐�
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
		players[1]->m_move_judge = false;
	}
}

//---------------------------------------------------------------------------
// �^�C�}�[�̍X�V����
//---------------------------------------------------------------------------
void GameScene::Time_Update(int& time_count)
{
	flame_count--;               // �t���[���J�E���g�����炷
	if (flame_count < 0) {       // �t���[���J�E���g���O�ɂȂ�����
		time_count--;            // �^�C�}�[�����炷
		flame_count = FLAME_MAX; // �t���[���J�E���g��ݒ肵�Ȃ���
	}

	// �^�C�}�[���[���ɂȂ�����
	if (time_count <= 0) {
		time_count = 0; // �[���Ŏ~�߂�
	}
}

//---------------------------------------------------------------------------
// �^�C�}�[�̕`�揈��
//---------------------------------------------------------------------------
void GameScene::Time_Draw()
{
	// ������̕`��ƕ`�敝�̎擾��2��g���̂ł����Œ�`���Ƃ��܂�
	const char* name = "[%2d]";
	// �`�敝�̎擾
	float w = GetDrawStringWidth(name, -1);
	// ������̍����擾
	float h = GetFontSize();

	SetFontSize(28); // �t�H���g�T�C�Y�̕ύX
	// �`��
	DrawFormatStringF(SCREEN_W / 2 + 16 - w, h - 16, GetColor(255, 255, 0), name, time_count);
	SetFontSize(18); // �t�H���g�T�C�Y��߂�
}

//---------------------------------------------------------------------------
// �`���[�g���A���ł̕`�揈��
//---------------------------------------------------------------------------
void GameScene::Tutorial_Draw()
{
	// ������̕`��ƕ`�敝�̎擾��2��g���̂ł����Œ�`���Ƃ��܂�
	const char* name = "�`���[�g���A��";
	// �`�敝�̎擾
	float w = GetDrawStringWidth(name, -1);
	// ������̍����擾
	float h = GetFontSize();

	SetFontSize(28); // �t�H���g�T�C�Y�̕ύX
	// �`��
	DrawFormatStringF(SCREEN_W / 2 + 16 - w, h - 16, GetColor(255, 255, 0), name, time_count);
	SetFontSize(18); // �t�H���g�T�C�Y��߂�
}

//---------------------------------------------------------------------------
// �G���h�ł̕`�揈��
//---------------------------------------------------------------------------
void GameScene::End_Draw()
{
	// ������̕`��ƕ`�敝�̎擾��2��g���̂ł����Œ�`���Ƃ��܂�
	const char* name = "end";
	// �`�敝�̎擾
	float w = GetDrawStringWidth(name, -1);
	// ������̍����擾
	float h = GetFontSize();
	
	SetFontSize(28); // �t�H���g�T�C�Y�̕ύX
	// �`��
	DrawFormatStringF(SCREEN_W / 2 + 16 - w, h - 16, GetColor(255, 255, 0), name, time_count);
	SetFontSize(18); // �t�H���g�T�C�Y��߂�
}


//---------------------------------------------------------------------------
// �U���̂����蔻����Ƃ�֐�
//---------------------------------------------------------------------------
void GameScene::Attack_Hit(int player1, int player2)
{
	// �����蔻�������Ă����Ƃ��ɓ������Ă�����_���[�W������
	// (�����蔻��ƍU���t���O�������Ă�����)
	if (players[player1]->cd_hit_flag && players[player1]->attack_flag) {
		if (HitCheck_Capsule_Capsule(players[player1]->m_hit_cd_pos_top.VGet(), players[player1]->m_hit_cd_pos_under.VGet(), players[player1]->m_hit_cd_r,
			players[player2]->m_hit_body_pos_top.VGet(), players[player2]->m_hit_body_pos_under.VGet(), players[player2]->m_hit_body_r))
		{
			players[player2]->m_hp_count.x -= players[player1]->m_attack_damage[players[player1]->attack_anim_pick]; // �_���[�W������
			players[player2]->damage_flag = true;
		}
	}
}


// �����蔻��p�̍\���́i�킩��₷���悤�Ɂj
struct Capsule
{
	VECTOR top_pos;
	VECTOR bottom_pos;
	float   r;
};

// �J�v�Z�����u�̂����蔻����g���₷����������
bool HitCheck_Capsule_Capsule(const Capsule& cp1, const Capsule& cp2)
{
	//float angle = atan2f(cp2.bottom_pos.y - cp1.bottom_pos.y, cp2.bottom_pos.x - cp1.bottom_pos.x);
	//float dgree = TO_DEGREE(angle);
	return HitCheck_Capsule_Capsule(cp1.top_pos,
		cp1.bottom_pos,
		cp1.r,
		cp2.top_pos,
		cp2.bottom_pos,
		cp2.r) == 1;
}

//---------------------------------------------------------------------------
// �K�[�h�̂����蔻����Ƃ�֐�
//---------------------------------------------------------------------------
void GameScene::Block_Hit(int player1, int player2)
{
	//�@�v���C���[�P�����x�N�g��(�����)
	Vector3 vec1 = players[0]->m_rot - players[1]->m_pos;
	// �v���C���[�Q�̕����x�N�g���i��������j
	Vector3 vec2 = players[1]->m_rot;
	// ����ł��܂������Ă���͂�
	float vec = GetVector3Dot(vec1, vec2);
	
	// ������ �O���牣��Ɛ����l�@��납�牣����}�C�i�X�l���Ԃ��Ă���
	// �����牣���Ƃւ�

	// �����蔻�������Ă����Ƃ��ɓ������Ă�����_���[�W������
	// �v���C���[�O�̍U������ƃv���C���[1�̃K�[�h�̔���
	

	// �U���p�J�v�Z��
	Capsule player2_hit_cp =
	{
		players[player2]->m_hit_cd_pos_top.VGet(),
		players[player2]->m_hit_cd_pos_under.VGet(),
		players[player2]->m_hit_cd_r
	};
	// �K�[�h���Ă���Ƃ�
	Capsule player1_cp =
	{
		players[player1]->m_block_top.VGet(),
		players[player1]->m_block_under.VGet(),
		players[player1]->m_block_r
	};
	// �K�[�h���Ă��Ȃ��Ƃ�
	Capsule player1_no_cp =
	{
		players[player1]->m_hit_body_pos_top.VGet(),
		players[player1]->m_hit_body_pos_under.VGet(),
		players[player1]->m_hit_body_r
	};

	// ------------------------------------------------
	//	�K�[�h���Ă���l�ɑ΂��Ă̓����蔻����s�����ǂ���
	// ------------------------------------------------
	// �����蔻������Ă������ǂ���
	bool can_check_hit = players[player1]->cd_hit_flag && players[player1]->block_flag;

	if (can_check_hit)
	{

		// �ǂ̕�������K�[�h�J�v�Z���ɍU�������������̂��𒲂ׂ�
		// ���̕������K�[�h�J�v�Z�����ł���΁A�h�������Ȃ��h
		// ��������Ȃ���΁A�h�_���[�W�����h


		if (HitCheck_Capsule_Capsule(player1_cp, player2_hit_cp))
		{
			// player1�̃K�[�h�p�J�v�Z����player2�̍U���p�J�v�Z�������������Ƃ�

		}
		else if (HitCheck_Capsule_Capsule(player1_no_cp, player2_hit_cp))
		{
			// player1�̖{�̗p�̃J�v�Z����player2�̍U���p�J�v�Z�������������Ƃ�
			players[player1]->m_hp_count.x -= players[player2]->m_attack_damage[players[player2]->attack_anim_pick]; // �_���[�W������
			players[player1]->damage_flag = true;
		}
	}


	// �p�b�h�̒�����
	if (IsPadRepeat(PAD_ID::PAD_A, players[0]->GetPadNo()))
	{

	}
}

//---------------------------------------------------------------------------
// �L�����N�^�[�̃X�e�[�^�X�`�揈��
//---------------------------------------------------------------------------
void GameScene::Draw_Status()
{
	DrawBox(players[0]->m_hp_pos.x, players[0]->m_hp_pos.y, players[0]->m_hp_count.x, players[0]->m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(players[0]->m_hp_pos.x, players[0]->m_hp_pos.y, HP_MAX, players[0]->m_hp_count.y, GetColor(255, 255, 255));

	DrawBox(SCREEN_W / 2 + players[1]->m_hp_pos.x, players[1]->m_hp_pos.y, SCREEN_W / 2 + players[1]->m_hp_count.x, players[1]->m_hp_count.y, GetColor(0, 255, 0), TRUE);
	DrawLineBox(SCREEN_W / 2 + players[1]->m_hp_pos.x, players[1]->m_hp_pos.y, SCREEN_W / 2 + HP_MAX, players[1]->m_hp_count.y, GetColor(255, 255, 255));
}
