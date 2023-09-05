#include "UIBase.h"

UIBase::UIBase()
{
	m_Pos = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Use = true;
}

UIBase::~UIBase()
{
}

void UIBase::Update()
{
}

void UIBase::Draw()
{
	if (!m_Use)	return;

	for (const auto& uiPair : m_pUIList)
	{
		uiPair.second->Draw();
	}
}
