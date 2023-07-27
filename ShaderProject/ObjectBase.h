#pragma once
#include "BaseProperty.h"
class ObjectBase : public BaseProperty
{
public:
	ObjectBase() {};
	~ObjectBase() {};
	virtual void Update() = 0;
	void Draw();
};

