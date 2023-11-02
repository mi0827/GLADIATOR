#include "WinMain.h"
#include "GameMain.h"
#include "Camera.h"

// �v���C���[����J�����܂ł̋���
#define CAMERA_LENGTH 40.0f
// �J�����̉�]�X�s�[�h
#define MOUSE_CAMERA_ROT_SPEED	0.2f // �}�E�X�p
#define PAD_CAMERA_ROT_SPEED 3.0f    // �p�b�h�p
// �J�����̏�A���O���̍ő�
const float UP_ANGLE_MAX = 30.0f;
// �J�����̉��A���O���̍Œ�i�n�ʂɖ��܂�Ȃ����x�j
const float LOWER_ANGLE = -10.0f;

// �R���X�g���N�^(������)
Camera::Camera()
{
	// �J�������W�̏����ݒ�
	m_pos.set(0.0f, 0.0f, -20.0f);
	// �J�����̌����͑S���O�x�ŊJ�n
	m_rot.set(0.0f, 0.0f, 0.0f);
	// �J������������W
	m_look.set(0.0f, 0.0f, 0.0f); // ���ׂĂO�D�O���ŏ�����

	// �}�E�X�̈ړ��ʂ̏������ŏ���0.0f����
	m_mouse_move_x = 0.0f;
	m_mouse_move_y = 0.0f;
}

// ��������
void Camera::Init()
{

}


//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Camera::Update(Vector3* player_pos)
{
	// �v���C���[�̌��ɕt���ē���
	m_look.set(player_pos->x, player_pos->y + 10.0f, player_pos->z);
	// �}�E�X�̈ړ���
	m_mouse_move_x = GetMouseMoveX();
	m_mouse_move_y = GetMouseMoveY();

	// �J�����̌�����ς���
	// �i�QD�̃}�E�X�̈ړ��ʂ����̂܂܊p�x�ɓn���Ƒ傫���̂ŏ������������Ă��܂��j
	m_rot.x += m_mouse_move_y * MOUSE_CAMERA_ROT_SPEED;
	m_rot.y += m_mouse_move_x * MOUSE_CAMERA_ROT_SPEED;

	// �J�������n�ʂɖ��܂�Ȃ��悤�ɂ��Ă���
	if (m_rot.x <= LOWER_ANGLE) {
		m_rot.x = LOWER_ANGLE;
	}

	// �J�������^��ɂ����Ȃ��悤�ɂ��Ă���
	if (m_rot.x >= UP_ANGLE_MAX) {
		m_rot.x = UP_ANGLE_MAX;
	}

	//	�Q�[���p�b�h�̉E�X�e�B�b�N�̒l���g���Č����ϐ��i m_rot �j�̒l��ύX
	// ���X�e�b�N�Ńv���C���[�̌�������W�̍X�V
	// �Q�[���p�b�h�̏����擾�iXINPUT �̏��j
	XINPUT_STATE input;
	// �Q�[���p�b�h�̏����ۂ��Ǝ擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	// �ړ��p�x�N�g���p�ϐ�
	Vector3 rot;
	// ���X�e�B�b�N�̒l��ݒ�
	rot.y = input.ThumbRX;
	rot.x = input.ThumbRY;
	// -32768 �` 32767 ��-1.0f�@�`�@1.0f�ɂ��܂�
	rot /= 32768.0f;
	// ���̈ړ��p�x�N�g���̑傫����������x�傫���������ړ������悤�Ǝv���܂�
	if (rot.GetLength() > 0.5f) {	
		m_rot += rot * PAD_CAMERA_ROT_SPEED;  // ���̈ړ��x�N�g�������W�ړ�
	}

	// �܂��͉�]�O�̃x�N�g����p�ӂ��܂�
	// �J����������v���C���[�����̃x�N�g�����쐬���܂�
	VECTOR base_dir = VGet(0.0f, 0.0f, -CAMERA_LENGTH);

	// �s���p�ӂ��܂�
	// X����]�s��
	MATRIX mat_x = MGetRotX(TO_RADIAN(m_rot.x));
	// Y����]�s��
	MATRIX mat_y = MGetRotY(TO_RADIAN(m_rot.y));

	// X����]��Y����]�����������̂łQ�̍s����P�ɂ܂Ƃ߂܂�
	MATRIX mat = MMult(mat_x, mat_y);
	// ���̃x�N�g�����w����]�Ƃx����]�����܂�
	// �ȒP�Ɍ���������̋����̖_������Ă���
	VECTOR change_dir = VTransform(base_dir, mat);

	// �J�����̈ʒu�����Ă�����W������̈ʒu�ɍĐݒ�
	m_pos = m_look + change_dir;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Camera::Draw()
{
	// ���W�ƌ�����n���ăJ�����̐ݒ�
	// SetCameraPositionAndAngle(m_pos.VGet(), m_rot.x, m_rot.y, m_rot.z);

	// �J�������W�ƌ�����W��n���ăJ�����̐ݒ�
	SetCameraPositionAndTarget_UpVecY(m_pos.VGet(), m_look.VGet());

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
