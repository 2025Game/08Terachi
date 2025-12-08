#include "CBullet.h"

void CBullet::Set(float w, float d)
{
    // 左、右、奥（先端）
    CVector v0(-w, 0.0f, 0.0f);   // 左
    CVector v1(w, 0.0f, 0.0f);   // 右
    CVector v2(0.0f, 0.0f, -d);  // 奥（先端）

    // 三角形の頂点設定
    mT.Vertex(v0, v1, v2);

    // 法線設定
    mT.Normal(CVector(0.0f, 1.0f, 0.0f));  // 上向き法線
}

void CBullet::Update()
{
    // 基底クラスの更新（行列更新）
    CTransform::Update();

    // 前方向(Z軸方向) に 0.2f 進める
    mPosition = mPosition + Z() * 0.2f;


}

void CBullet::Render()
{
    // 三角形描画
    //glBegin(GL_TRIANGLES);
    // DIFFUSE黄色設定
    float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
    mT.Render(mMatrix);

    //const CVector& v0 = mT.V0();
    //const CVector& v1 = mT.V1();
    //const CVector& v2 = mT.V2();

    //glVertex3f(v0.X(), v0.Y(), v0.Z());
    //glVertex3f(v1.X(), v1.Y(), v1.Z());
    //glVertex3f(v2.X(), v2.Y(), v2.Z());

    //glEnd();
}

