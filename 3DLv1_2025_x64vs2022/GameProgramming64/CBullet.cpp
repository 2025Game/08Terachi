#include "CBullet.h"

#define VELOCITY 10.0f
// 幅と奥行きの設定
void CBullet::Set(float w, float d)
{
    mScale = CVector(1.0f, 1.0f, 1.0f);

    mT.Vertex(
        CVector(-w, 0.0f, 0.0f),
        CVector(w, 0.0f, 0.0f),
        CVector(0.0f, 0.0f, d)
    );

    mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

// 更新
void CBullet::Update()
{
 // 行列更新
 CTransform::Update();
 // 進行方向(Z方向)へ進む
 mPosition = mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
}

// 描画
void CBullet::Render()
{
    float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);

    glPushMatrix();
    glMultMatrixf(mMatrix.M());
    mT.Render();
    glPopMatrix();

    mCollider.Render();
}
