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
    CPlayer(const CVector& pos, const CVector& rot, const CVector& scale);

    void Update();
    void Render();
    CBullet bullet;
private:
    CInput mInput;
};

#endif
