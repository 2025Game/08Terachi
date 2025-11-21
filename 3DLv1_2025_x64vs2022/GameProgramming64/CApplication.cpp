#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CCharacter3.h"

#define SOUND_BGM "res\\mario.wav" //BGM音声ファイル
#define SOUND_OVER "res\\mdai.wav"  //ゲームオーバー音声ファイル
//モデルデータの指定
#define MODEL_OBJ "res\\f14.obj", "res\\f14.mtl" 
//背景モデルデータの指定
#define MODEL_BACKGROUND "res\\sky.obj", "res\\sky.mtl"

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
    mModel.Load("model.obj", "model.mtl");
    mCharacter.Model(&mModel);
    mCharacter.Scale(CVector(0.1f, 0.1f, 0.1f));

    mPlayer.Model(&mModel);
    mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
    mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
    mPlayer.Rotation(CVector(0.0f, 180.0f, 0.0f));
    mPlayer.Update();

    //カメラ初期位置
    mEye = CVector(1.0f, 2.0f, 3.0f);
    //モデルファイルの入力
    mModel.Load(MODEL_OBJ);
    //背景モデルの入力
    mBackGround.Load(MODEL_BACKGROUND);
    CMatrix matrix;
    matrix.Print();
}

void CApplication::Update()
{

    //視点の設定
    gluLookAt
    (
        mEye.X(), mEye.Y(), mEye.Z(),
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );
    mCharacter.Update();
    mPlayer.Update();
    mCharacter.Render();

//モデル描画
    CTransform trans; //変換行列インスタンスの作成
    trans.Position(CVector(0.5f, 1.8f, 0.5f)); //位置の設定
    trans.Rotation(CVector(-10.0f, -20.0f, -30.0f)); //回転の設定
    trans.Scale(CVector(0.1f, 0.1f, 0.1f)); //拡大縮小の設定
    trans.Update(); //行列の更新
    mPlayer.Render();
   
    mBackGround.Render();
}
 