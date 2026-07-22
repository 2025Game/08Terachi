#pragma once
#include "CCharacter3.h"
#include "CColliderTriangle.h"
class CCube : public CCharacter3
{
public:
	CCube();
	void Update();
	void Collision(CCollider* m, CCollider* o) override;
private:
	//モデルデータ?インスタンス
	static CModel msModel;
	//コライダ?上面??付?る
	CColliderTriangle mCollider[2];
};