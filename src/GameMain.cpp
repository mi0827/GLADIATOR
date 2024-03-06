#include "WinMain.h"
#include "System/Vector3.h"
#include "System/Vector2.h"
#include "Hit/Hit.h" // �����蔻��
#include "Base.h"
#include "System/InputPad.h"
#include "System/Option.h"
// �L�����N�^�[.h
#include "Character/Base/Character_Base.h"
#include "Character/Player.h"
#include "Character/Ninja.h"
// �I�u�W�F�N�g�N���X
#include "Object/Object.h"
// �t�B�[���h.h
#include "Field/Field.h"
// �J����.h
#include "Camera.h"

#include "Scene/Base/Scene_Base.h"
#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"
#include "Scene/EndScene.h"
#include "GameMain.h"

Option option;

Scene_Base* scene;
// �e�V�[���̃I�u�W�F�N�g
TiteleScene titel_scene; // �^�C�g��
GameScene play_scene;    // �Q�[���v���C�V�[��
EndScene end_scene;      // �G���h


int scene_num; // ���ǂ̃V�[�����̂�����p�̕ϐ�
// �e�V�[���ł̎g�����������邽�߂̃V�[���̗񋓑�
enum Scene
{
	Titele, // �^�C�g��
	Play,  // ���C���̃v���C�V�[��
	End,   // �G���h

	Scene_Max // �V�[���̍ő吔
};

// ��������
void GameInit()
{
	// �ŏ��̓^�C�g���V�[������n�߂�
	scene = new TiteleScene;
	scene->Init(); // �^�C�g���V�[���̏�����

	scene_num = Titele; // �ŏ��̓^�C�g���V�[������n�߂�
	 
	option.Init(); 
	option.m_option_flag = false; // �ŏ��͊J���Ȃ�

}

// �X�V����
void GameUpdate()
{
	// �T�E���h�ύX�p�֐�
	option.Update();
	switch (scene_num)
	{
	case Titele: // �^�C�g���V�[��

		scene->Update(option.m_BGM_Volume, option.m_SE_Volume);
		if (scene->m_scene_change_judge) {                             // �V�[���̐؂�ւ��̋���������
			scene->Exit();                                           // dekete�O�ɏI����������
			Scene_Change_Judge(scene_num, Play);                     // �V�[���̐؂�ւ�
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new GameScene;                                   // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;

	case Play:  // �v���C�V�[��
		scene->Update(option.m_BGM_Volume, option.m_SE_Volume);
		if (scene->m_scene_change_judge) {                              // �V�[���̐؂�ւ��̋���������
			scene->Exit();                                            // dekete�O�ɏI����������
			Scene_Change_Judge(scene_num, End);  // �V�[���̐؂�ւ�	                                                        
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new EndScene;                                    // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;
	case End:  // �G���h�V�[��
		scene->Update(option.m_BGM_Volume, option.m_SE_Volume);
		if (scene->m_scene_change_judge) {                             // �V�[���̐؂�ւ��̋���������
			scene->Exit();                                           // dekete�O�ɏI����������
			Scene_Change_Judge(scene_num, Titele);                   // �V�[���̐؂�ւ�
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new TiteleScene;                                 // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;
	}

}

// �`�揈��
void GameDraw()
{
	
	scene->Draw(); // �e�V�[��
	option.Draw(); // �I�v�V�������
}

// �I������
void GameExit()
{
	scene->Exit();
}


//----------------------------------------------
// ���̃V�[�����玟�̃V�[���ɐ؂�ւ���֐�
//----------------------------------------------
void Scene_Change_Judge(int& now_scene, const int& next_scene)
{
	// ���̃V�[���ԍ��Ɏ��s�������V�[���ԍ�������
	now_scene = next_scene;
}
