#include "stdafx.h"
#include "effect.h"
#include "animation.h"


HRESULT effect::init(image * effectImage, int frameWidth, int frameHeight, int fps, float elapsedTime)
{
	if (!effectImage)	return E_FAIL;

	m_fElapsedTime = elapsedTime;
	m_isAlive = false;
	m_pImg = effectImage;

	if (!m_pAnimation)
	{
		m_pAnimation = new animation;
	}
	m_pAnimation->init(m_pImg->getWidth(), m_pImg->getHeight(), frameWidth, frameHeight);
	m_pAnimation->setDefPlayFrame(false, false);
	m_pAnimation->setFPS(fps);
	m_pAnimation->stop();

	return S_OK;
}

void effect::release()
{
	SAFE_DELETE(m_pAnimation);
}

void effect::update()
{
	if (!m_isAlive) return;
	m_pAnimation->frameUpdate(m_fElapsedTime);

	if (!m_pAnimation->getIsPlaying())
	{
		//m_isAlive = false;
		endEffect();
	}
}

void effect::render(HDC hdc)
{
	if (!m_isAlive) return;

	if (m_pImg)
		m_pImg->aniRender(hdc, m_nX, m_nY, m_pAnimation);
}

void effect::startEffect(int x, int y)
{
	if (!m_pImg || !m_pAnimation) return;

	m_nX = x;
	m_nY = y;

	m_isAlive = true;
	m_pAnimation->start();
}

void effect::endEffect()
{
	if (!m_pAnimation) return;

	m_isAlive = false;
	m_pAnimation->stop();
}

effect::effect()
{
}


effect::~effect()
{
}
