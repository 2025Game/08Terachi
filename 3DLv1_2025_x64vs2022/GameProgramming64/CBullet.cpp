#include "CBullet.h"

void CBullet::Set(float w, float d)
{
    mScale = CVector(1.0f, 1.0f, 1.0f);
    CVector v0(-w * 0.5f, 0.0f, 0.0f);
    CVector v1(w * 0.5f, 0.0f, 0.0f);
    CVector v2(0.0f, 0.0f, -d);

    mT.Vertex(v0, v1, v2);
    mT.Normal(CVector(0.0f, 1.0f, 0.0f));
    mDir = CVector(0.0f, 0.0f, 1.0f);
    mSpeed = 0.5f;
}


void CBullet::Update()
{
    if (!mActive) return;
    // 前方向(Z方向)へ進む
    mPosition = mPosition + (mDir * mSpeed) * mMatrixRotate;

    // 行列更新
    CTransform::Update();
    if (mPosition.Z() > 50.0f || mPosition.Z() < -50.0f)
    {
        mActive = false;
    }
}


void CBullet::Render()
{
    if (!mActive) return;
    // 三角形描画
    //glBegin(GL_TRIANGLES);
    // DIFFUSE黄色設定
    float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
    mT.Render(mMatrix);
    glPushMatrix();
    glPopMatrix();

    //const CVector& v0 = mT.V0();
    //const CVector& v1 = mT.V1();
    //const CVector& v2 = mT.V2();

    //glVertex3f(v0.X(), v0.Y(), v0.Z());
    //glVertex3f(v1.X(), v1.Y(), v1.Z());
    //glVertex3f(v2.X(), v2.Y(), v2.Z());

    //glEnd();
}

