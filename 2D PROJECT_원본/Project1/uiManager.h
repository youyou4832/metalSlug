#pragma once
#include "singletonBase.h"
#include "uiButton.h"
class uiObject;

class uiManager : public singletonBase<uiManager>, iButtonDelegate
{
private:
	vector<uiObject*>	m_vecUIObjects;
	vector<uiObject*>::iterator	m_iter;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addUIObject(uiObject* pUI);

	virtual void OnClick(uiButton* pSender) override;

	uiManager();
	~uiManager();
};

