#pragma once
#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"
/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CCharacter3
{
public:
    CPlayer() : mShot(false) {}
    CPlayer(const CVector& pos, const CVector& rot, const CVector& scale);

    void Update();
    void Render();

private:
    CBullet bullet;
    CInput mInput;
    bool mShot;
    //CBullet bullet;
};

#endif
