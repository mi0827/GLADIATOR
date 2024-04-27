#include "src/WinMain.h"
#include "Animation.h"


using namespace std;


Animation::Animation( int anim_max)
{
	anim_handl = new Anim_[anim_max];
}

Animation::~Animation()
{

	delete[] anim_handl;
	delete[] contexts_;
}

// �ǂݍ���
void Animation::Load_Anim(const char file_path[256],int anim_no, int anim_index)
{
	// �ǂݍ���
	anim_handl[anim_no].handl = MV1LoadModel(file_path);
	// �A�j���V�����C���f�b�N�X�ԍ��̕ۑ�
	anim_handl[anim_no].index = anim_index;
}

