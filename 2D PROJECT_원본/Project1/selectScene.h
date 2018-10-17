#pragma once
#include "scene.h"

class selectScene : public scene
{
private:
	image * m_pSelectBG;
	image * m_pimgSelectUi;
public:
	int m_PlayerUIfX1;
	int m_PlayerUIfY1;

	int m_PlayerUIfX2;
	int m_PlayerUIfY2;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	selectScene();
	~selectScene();
};

