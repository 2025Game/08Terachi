#include"CPlayerWalk.h"
#include "CMatrix.h"
#include "CVector.h"
#include "CXCharacter.h"
#define ROTATIONSPEED 2.0f
//移動速度
#define VELOCITY 0.1f
void CPlayerWalk::Update()
{
	if (mInput.Key('W'))
	{
		if (mInput.Key('D'))
		{
			CVector r = mpParent->Rotation() + CVector(0.0f, -ROTATIONSPEED, 0.0f);
			mpParent->Rotation(r);
		}
	
		if (mInput.Key('A'))
		{
			CVector r = mpParent->Rotation() + CVector(0.0f, ROTATIONSPEED, 0.0f);
			mpParent->Rotation(r);
		}
		CVector p = mpParent->Position();
		mpParent->Position(p + mpParent->MatrixRotate().VectorZ() * VELOCITY);
	}
	if (mInput.Key('I'))
	{
		mState = EState::EATTACK;
		return;
	}
	if (mInput.Key(VK_SPACE))
	{
		mState = EState::EJUMP;
		return;
	}
	else
	{
		mState = EState::EIDLE;
	}
}
void CPlayerWalk::Start(CXCharacter * parent)
{
	//親のポインタを保存
	mpParent = parent;
	//アニメーションの変更
	mpParent->ChangeAnimation(1, true, 60);
	mState = EState::EWALK; //状態の種類を歩くにする
	//mpParent = parent;	
	//mpParent->ChangeAnimation(7, false, 60);
	//mState = EState::EJUMP;
}