#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CCharacter3.h"
#include "CTask.h"

#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav"  //ゲームオーバー音声ファイル
//モデルデータの指定
#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl" 
//背景モデルデータの指定
#define MODEL_BACKGROUND "res\\sky.obj", "res\\sky.mtl"
//敵輸送機モデル
#define MODEL_C5 "res\\c5.obj", "res\\c5.mtl"

CTaskManager CApplication::mTaskManager;
CTaskManager* CApplication::TaskManager()
{
    return &mTaskManager;
}
CCharacterManager CApplication::mCharacterManager;
CTexture CApplication::mTexture;

CTexture* CApplication::Texture()
{
    return &mTexture;
}

CCharacterManager* CApplication::CharacterManager()
{
    return &mCharacterManager;
}

void CApplication::Start()
{
    //C5モデルの読み込み
    mModelC5.Load(MODEL_C5);
     
    //敵機のインスタンス作成
    mpEnemy1 = new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -100.0f),
        CVector(), CVector(0.1f, 0.1f, 0.1f));

    mpEnemy2 = new CEnemy(&mModelC5,
        CVector(30.0f, 10.0f, -130.0f),
        CVector(), CVector(0.1f, 0.1f, 0.1f));

    

    mModel.Load(MODEL_OBJ);

    mPlayer.Model(&mModel);
    mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
    mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
    mPlayer.Rotation(CVector(0.0f, 180.0f, 0.0f));
    mPlayer.Update();

    //カメラ初期位置
    mEye = CVector(1.0f, 2.0f, 3.0f);
    //背景モデルの入力
    mBackGround.Load(MODEL_BACKGROUND);
    CMatrix matrix;
    matrix.Print();
    //mBullet.Set(0.2f, 0.5f);
    //mBullet.Position(CVector(0.0f, 0.0f, -3.0f));
    //mBullet.Rotation(CVector(0.0f, 0.0f, 0.0f));
}

void CApplication::Update()
{
    mPlayer.Update();
    //カメラのパラメータを作成する
    CVector e, c, u;//視点、注視点、上方向
    //視点を求める
    e = mPlayer.Position() + CVector(0, 1, -3) * mPlayer.MatrixRotate();
        //注視点を求める
        c = mPlayer.Position();
    //上方向を求める
        u = CVector(0, 1, 0) * mPlayer.MatrixRotate();
        //カメラの設定
        gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());

        if (mpEnemy1)
        {
            mpEnemy1->Update();
            mpEnemy1->Render();
        }

        if (mpEnemy2)
        {
            mpEnemy2->Update();
            mpEnemy2->Render();
        }
//モデル描画
    //CCharacter3 trans; //変換行列インスタンスの作成
    //trans.Position(CVector(0.5f, 1.8f, 0.5f)); //位置の設定
    //trans.Rotation(CVector(-10.0f, -20.0f, -30.0f)); //回転の設定
    //trans.Scale(CVector(0.1f, 0.1f, 0.1f)); //拡大縮小の設定
   
    //タスクマネージャの更新
    mTaskManager.Update();
    //タスクリストの削除
    mTaskManager.Delete();
    //タスクマネージャの描画
    mTaskManager.Render();
    mBackGround.Render();
}
