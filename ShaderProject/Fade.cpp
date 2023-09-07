#include "Fade.h"
#include "GameUI.h"

#define FADE_FRAME (60.0f)

Fade::Fade()
{
	m_State = FadeState::FADE_STOP;
	m_Alpha = 0.0f;

	GameUI* bg = CreateUI<GameUI>("Fade");
	bg->SetSize(DirectX::XMFLOAT2(1280.0f, 720.0f));
	bg->CreateTex("Assets/Texture/ImageBase.png");
	bg->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_Alpha));
}

void Fade::Update()
{
	switch (m_State)
	{
	case Fade::FADE_STOP:
		break;
	case Fade::FADE_IN:
		m_Alpha += 1.0f / FADE_FRAME;
		if (m_Alpha >= 1.0f)
		{
			m_Alpha = 1.0f;
			m_State = FADE_END;
		}
		break;
	case Fade::FADE_OUT:
		m_Alpha -= 1.0f / FADE_FRAME;
		if (m_Alpha <= 0.0f)
		{
			m_Alpha = 0.0f;
			m_State = FADE_STOP;
		}
		break;
	case Fade::FADE_END:
		break;
	default:
		break;
	}

	GetUI<GameUI>("Fade")->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_Alpha));
}

void Fade::StartFade()
{
	m_State = FADE_IN;
}

void Fade::EndFade()
{
	m_State = FADE_OUT;
}

Fade::FadeState Fade::GetFadeState()
{
	return m_State;
}
