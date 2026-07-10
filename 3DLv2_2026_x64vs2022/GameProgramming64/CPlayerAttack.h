#pragma once
#include "CState.h"

class CPlayerAttack : public CState
{
public:
	void Start(CXCharacter* parent) override;
	void Update() override;
};