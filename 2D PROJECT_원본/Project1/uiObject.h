#pragma once
class uiButton;

class uiObject
{
protected:
	image * m_pImg;

	vector<uiObject*>	m_vecChild;
	vector<uiObject*>::iterator	m_iter;

	SYNTHESIZE(FPOINT, m_position, Position);
	SYNTHESIZE(uiObject*, m_pParent, Parent);
	SYNTHESIZE(bool, m_isHidden, IsHidden);
	SYNTHESIZE(int, m_nTag, Tag);

	RECT		m_rc;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void addChild(uiObject* pChild);

	virtual void OnClick(uiButton * pSender);

	//	virtual void setImage(const char* szImageName);

	uiObject();
	virtual ~uiObject();
};

