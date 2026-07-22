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
	//モデルデータインスタンス
	static CModel msModel;
	CColliderTriangle mCollider[2];
};