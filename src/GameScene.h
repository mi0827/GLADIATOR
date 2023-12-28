#pragma once
// #include "Character_Base.h"


class GameScene :public Scene_Base
{
public:
	GameScene();
	// ~GameScene();
	// ��������
	void Init()override;

	// �X�V����
	void Update()override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

	// �`���[�g���A���̍X�V����
	void Tutorial_Update();
	// ���C���v���C�V�[���̍X�V����
	void PlayMain_Update();
	// �v���C�G���h�̍X�V����
	void PlayEnd_Update();
	// �G���h�V�[���ł̏��s�Ɋւ���֐�
	void Play_Victory_Draw(CharacterBase* character1, CharacterBase* character2); // ���҂����߂�֐�

	// �`��p�̕�����̃T�C�Y����
	void Draw_String_Size(float* w, float* h, const char* sting);

	// �L�����N�^�[�̍X�V�����i�ړ����̂��݂��̂����蔻��j
	void Character_Update();
	// �^�C�}�[�̍X�V����
	void Time_Update(int& time_count);
	// �^�C�}�[�̕`��
	void Time_Draw();
	// �`���[�g���A���ł̕`�揈��
	void Tutorial_Draw();
	// ����������`�悳���邾���̊֐�
	void Ready_Draw();
	// �G���h�ł̕`�揈��
	void End_Draw();

	// �U���̂����蔻����s���֐�
	void Attack_Hit(int player1, int player2);
	// �K�[�h�̓����蔻��
	void Block_Hit(int player1, int player2);
	// �L�����N�^�[�̃X�e�[�^�X�`�揈��
	void Draw_Status();

	enum play_scene
	{
		Play_Tutorial, // �`���[�g���A���V�[��
		Play_Main,     // �Q�[�����C���V�[��
		Play_End,      // �v���CEND�V�[��

		Play_Max       // �v���C�V�[���̍ő�
	};

private:

	int time_count;     // �t���[�����������̎��ԂŌv�Z����p�̕ϐ�
	int flame_count;    // �t���[�������J�E���g������ϐ�
	int play_scene;     // �`���[�g���A���̓r�����𔻕�
	int end_count;      // �G���h�V�[���̎���
	bool status_flag;   // �X�e�[�^�X�X�V�������Ă������̃t���O

	//-------------------------------------------
	// �`���[�g���A���Ŏg���ϐ�
	//-------------------------------------------
	const float BUTTON_COUNT_MAX = 180; // �R�b
	// ���������t���O
	bool ready_flag1 = false;
	bool ready_flag2 = false;
	// �{�^���̒��������J�E���g����p�̕ϐ�
    float button_count1 = 0;
	int button_count2 = 0;
};