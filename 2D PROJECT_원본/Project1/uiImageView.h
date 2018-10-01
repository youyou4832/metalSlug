#pragma once
#include "uiObject.h"

//	UI 이미지를 출력하는 클래스
class uiImageView : public uiObject
{
private:
	image*	m_pImg;

public:
	HRESULT init(const char* szImageName, float x, float y);	// 부모클래스에 붙일 거라 상대적인 위치임

	virtual void update() override;
	virtual void render(HDC hdc) override;

	uiImageView();
	virtual ~uiImageView();
};

