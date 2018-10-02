#pragma once
#include "scene.h"
class button;

class titleScene : public scene
{
private:
	image * m_pBG;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	titleScene();
	~titleScene();
};
