#pragma once
#include "Snene_Base.h"

class EndScene : public Scene_Base
{
public:
	// ��������
	void Init()override;

	// �X�V����
	void Update()override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

};