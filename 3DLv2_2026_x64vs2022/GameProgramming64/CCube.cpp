#include "CCube.h"
#include "CCollisionManager.h"
#define MODEL_CUBE "res\\cube.obj", "res\\cube.mtl"
CModel CCube::msModel;

CCube::CCube()
{
	if (msModel.Triangles().empty())
	{
		msModel.Load(MODEL_CUBE);
	}
	mpModel = &msModel;

	mCollider[0].Set
	(
		this,
		&mMatrix,
		msModel.Triangles()[0].V0(),
		msModel.Triangles()[0].V1(),
		msModel.Triangles()[0].V2()
	);

	mCollider[1].Set
	(
		this,
		&mMatrix,
		msModel.Triangles()[1].V0(),
		msModel.Triangles()[1].V1(),
		msModel.Triangles()[1].V2()
	);

}

void CCube::Update()
{
	CTransform::Update();

	CCollisionManager::Instance()->Collision(&mCollider[0], 50);
	CCollisionManager::Instance()->Collision(&mCollider[1], 50);
}
void CCube::Collision(CCollider* m, CCollider* o)
{
}