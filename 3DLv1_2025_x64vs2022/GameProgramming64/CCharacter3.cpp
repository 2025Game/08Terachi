#include "CCharacter3.h"
#include "CTransform.h"
#include "CMatrix.h"
#include "CApplication.h"
CCharacter3::CCharacter3()
    :mpModel(nullptr)
{
    //タスクリストに追加
    CApplication::TaskManager()->Add(this);
}

CCharacter3::~CCharacter3() 
{
    //タスクリストから削除
    CApplication::TaskManager()->Remove(this);
}

void CCharacter3::Model(CModel* m)
{
    mpModel = m;
}

void CCharacter3::Render()
{
    mpModel->Render(mMatrix);
}

CVector CCharacter3::Z() const
{
    // (0,0,1) を回転行列で変換 → 前方向ベクトル
    return CVector(0.0f, 0.0f, 1.0f) * mRotationMatrix;
}
