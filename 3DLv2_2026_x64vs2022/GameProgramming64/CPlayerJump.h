#pragma once
#include "CState.h"
#include "CMatrix.h"
#include "CVector.h"
#include "CXCharacter.h"
class CPlayerJump : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
	//衝突処理
//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o) override;
private:
	CVector mJumpV; //ジャンプの速度
};