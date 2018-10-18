#pragma once
#include "scene.h"
class gameoverScene : public scene
{
private:
	image	*	m_pimgGameOverBG;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	gameoverScene();
	~gameoverScene();
};

