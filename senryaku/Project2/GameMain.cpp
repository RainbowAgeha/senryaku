//���C���֐�
#include "GameMain.h"
#include "GameSceneMain.h"

//�O���[�o���ϐ�
int game_status = GAMETITLE;

int FrameStartTime;        // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ�

//���͏�� Input:�������ςȂ�
int Input;
//���͏�� EdgeInput:1��̂�
int EdgeInput;


//WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){

	//���s���O���o�͂��Ȃ�
	SetOutApplicationLogValidFlag(false);

	//�E�B���h�E�̐ݒ�
	//�E�B���h�E���[�h�̐ݒ� false:�S��ʐݒ�
	ChangeWindowMode(true);

	/*
	// �E�C���h�E���[�h�ŋN�����邩�m�F����
	if (MessageBox(NULL, "�E�C���h�E���[�h�ŋN�����܂����H", "��ʃ��[�h�m�F", MB_YESNO) == IDYES)
	{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	}
	*/

	//�E�B���h�E�̃��T�C�Y
	//Check:���s���ɉ�ʂ̑傫�����ύX�\��
	SetWindowSizeChangeEnableFlag(true);
	//�E�B���h�E�^�C�g��
	SetMainWindowText("�Q�[���e�X�g");

	//�w�i�F�̐ݒ�
	SetBackgroundColor(0, 0, 0);
	//DX���C�u��������������
	//check:-1(��O����)�������ꍇ�́A�Z�b�g�A�b�v�Ɏ��s����
	//�p�\�R���{�̂̋@��̊m�F�����Ă��炤(�����f�o�C�X���Ȃ����B)
	if (DxLib_Init() == -1)return -1;

	//�`������Ԍ��ɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	//���y�Đ��̏�����
	InitSoundMem();	//Dxlib


	// �Q�[�����[�v�O������
	InitGame();

	//���C�����[�v
	while (1){

		// ��ʂɕ`����Ă�����̂����S������
		ClearDrawScreen();

		// �P/�U�O�b���܂ő҂�
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}
		// ���݂̃J�E���g�l��ۑ�
		FrameStartTime = GetNowCount();
		// ���͏�Ԃ��X�V
		{
			int i;
			// �p�b�h�P�ƃL�[�{�[�h������͂𓾂�
			i = GetJoypadInputState(DX_INPUT_KEY_PAD1);
			// �G�b�W����������͂��Z�b�g
			EdgeInput = i & ~Input;
			// ���͏�Ԃ̕ۑ�
			Input = i;
		}

		//�Q�[���̍X�V����
		FrameMove();
		//�Q�[���̕`�揈��
		RenderScene();


        //��ʂ̕\��������Ԏ�O���甽�f����
		ScreenFlip();

		//windows�V�X�e�����痈�������������(��O������)
		if (ProcessMessage() == -1)break;

		//ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
	}

	//Dxlib�̊J��
	DxLib_End();

	// �Q�[���I�����̏�����
	GameRelease();

	//�Q�[�����I������
	return 0;
}