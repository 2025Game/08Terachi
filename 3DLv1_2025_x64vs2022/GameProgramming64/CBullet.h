#pragma once
#ifndef CBULLET_H
#define CBULLET_H

#include "CCharacter3.h"
#include "CTriangle.h"
#include "CCollider.h"

/*
弾クラス
三角形を飛ばす
*/
class CBullet : public CCharacter3
{
public:
    CVector mDir;     // 進行方向
    float mSpeed;     // 速度
    bool mIsShot;     // 発射中フラグ
    bool mActive;     // 弾が生きているか

    CBullet(); 

    //幅と奥行きの設定
    void Set(float w, float d);
    //更新
    void Update();
    //描画
    void Render();
private:
    int mLife;        // 生存時間
    CTriangle mT;     // 三角形
    CCollider mCollider; 
};

#endif
