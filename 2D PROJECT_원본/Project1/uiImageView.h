#pragma once
#include "uiObject.h"

//	UI �̹����� ����ϴ� Ŭ����
class uiImageView : public uiObject
{
private:
	image*	m_pImg;

public:
	HRESULT init(const char* szImageName, float x, float y);	// �θ�Ŭ������ ���� �Ŷ� ������� ��ġ��

	virtual void update() override;
	virtual void render(HDC hdc) override;

	uiImageView();
	virtual ~uiImageView();
};

