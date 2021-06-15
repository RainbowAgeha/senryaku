#ifndef __GAMESCENEMAIN_H_
#define __GAMESCENEMAIN_H_

#include "GameMain.h"

// GameMain.cpp�t�@�C�����̊֐��̂����A���̃t�@�C������Ăяo�����֐��̃v���g�^�C�v�錾���L�q����
BOOL InitGame(void);
void FrameMove();
void RenderScene(void);
void GameRelease(void);
void CollideCallback(int nSrc, int nTarget, int nCollideID);

//�P�V�[���ԍ����Ǘ�����񋓑�
//SCENE_NONE��SCENE_MAX�̊ԂɁA�K�v�ȃV�[���ԍ���ݒ肷��
typedef enum _SCENE_NO{
	SCENE_NONE = -1,		// �V�[���ԍ��̉����B�K������
	SCENE_MENU,			// ���j���[�V�[���̔ԍ�
	SCENE_GAME1,		// �Q�[���P�V�[���̔ԍ�
	SCENE_GAME2,		// �Q�[���Q�V�[���̔ԍ�
	SCENE_GAME3,		// �Q�[���R�V�[���̔ԍ�
	SCENE_MAX			// �V�[���ԍ��̏���B�K������
} SCENE_NO;

//�V�[����ύX����֐�
void changeScene(SCENE_NO no);

#endif