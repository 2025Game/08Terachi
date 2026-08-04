#include "CGameScene.h"
#include "CCharacter3.h"
#include "CTaskManager.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CCollisionManager.h"
#include "CCube.h"
#include "CCamera.h"
//背景モデルデータの指定
#define MODEL_BACKGROUND "res\\sky.obj", "res\\sky.mtl"
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
{
}
void CGameScene::Load()
{
	CCharacter3* cube = new CCube();
	cube->Position(CVector(0.0f, 0.0f, -9.0f));
	cube->Scale(CVector(10.0f, 0.5f, 10.0f));
	mPlayer.Load(MODEL_FILE);
	CXCharacter* xchar = new CXPlayer();
	xchar->Init(&mPlayer);
	//課題 背景モデルデータの読み込み
	mBackGround.Load(MODEL_BACKGROUND);
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	//キャラクタのインスタンス作成
	CCharacter3* character = new CCharacter3();
	//キャラクタのモデルの設定
	character->Model(&mBackGround);
	CCamera::Instance()->Scale(CVector(0.0f, 1.0f, -7.0f));
}
void CGameScene::Update()
{
	//全キャラクタの更新
	CTaskManager::Instance()->Update();
	//衝突処理の呼び出し
	CTaskManager::Instance()->Collision();
	CCamera::Instance()->Update();
	CTaskManager::Instance()->Render();
	//課題 全キャラクタの描画S
	//コライダの描画
	CCollisionManager::Instance()->Render();
}