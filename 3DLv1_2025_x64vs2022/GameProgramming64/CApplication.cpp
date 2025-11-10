#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CModel.h"
#include "CMatrix.h"

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
    //カメラ初期位置
    mEye = CVector(1.0f, 5.0f, 20.0f); 
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
//モデル描画
    mModel.Render(CMatrix().Scale(0.5f, 0.5f, 0.5f));
   
    mBackGround.Render();

}
