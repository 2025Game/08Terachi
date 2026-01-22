#include "CBullet.h"

void CBullet::Set(float w, float d)
{
    // スケール設定
    mScale = CVector(1.0f, 1.0f, 1.0f);

    // 三角形の頂点設定
    CVector v0(0.0f, 0.0f, -d);
    CVector v1(-w, 0.0f, 0.0f);
    CVector v2(w, 0.0f, 0.0f);
    mT.Vertex(v0, v1, v2);

    // 法線
    mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

void CBullet::Update()
{
    //生存時間の判定
    if (mLife-- > 0)
    {
        CTransform::Update();
        //位置更新
        mPosition = mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;;
    }
    else
    {
        //無効にする
        mEnabled = false;
    }
}

void CBullet::Render()
{
    // 黄色
    float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);

    // 三角形描画
    mT.Render(mMatrix);
    mCollider.Render();
}
//const CVector& v0 = mT.V0();
//const CVector& v1 = mT.V1();
//const CVector& v2 = mT.V2();

//glVertex3f(v0.X(), v0.Y(), v0.Z());
//glVertex3f(v1.X(), v1.Y(), v1.Z());
//glVertex3f(v2.X(), v2.Y(), v2.Z());

//glEnd();

