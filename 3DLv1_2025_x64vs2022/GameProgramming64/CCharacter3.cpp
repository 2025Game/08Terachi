#include "CCharacter3.h"
#include "CTransform.h"
#include "CMatrix.h"
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
