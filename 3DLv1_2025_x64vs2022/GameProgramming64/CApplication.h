#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CFont.h"
#include "CMiss.h"
#include "CCharacterManager.h"
#include "CGame.h"
#include "CVector.h"
#include "CModel.h"
#include "CTaskManager.h"

class CApplication
{
public:
	static CTaskManager* TaskManager();
	CModel mModel;
	CPlayer mPlayer;
	//CBullet mBullet;
	static CTexture* Texture();
	static CCharacterManager* CharacterManager();
	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー 
	};

	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
private:
	//C5モデル
	CModel mModelC5;
	static CTaskManager mTaskManager;
	CModel mBackGround; //背景モデル
	//モデルクラスのインスタンス
	CVector mEye;
	CSound mSoundBgm;
	CSound mSoundOver;
	CGame* mpGame;
	static CCharacterManager mCharacterManager;
	EState mState;
	CMiss* mpMiss;
	CInput mInput;
	CFont mFont;
	CPlayer* mpPlayer;
	CBullet* mpBullet;
	static CTexture mTexture;
	CEnemy* mpEnemy1;
	CEnemy* mpEnemy2;
};