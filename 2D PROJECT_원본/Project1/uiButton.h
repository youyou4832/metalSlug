#pragma once
#include "uiObject.h"
class uiButton;

class iButtonDelegate
{
public:
	virtual void OnClick(uiButton* pSender) = 0;
};

class uiButton : public uiObject
{
private:
	enum ButtonState
	{
		IDLE,
		WAIT,
		UP,
		DOWN,
		NUM
	};

	string		m_strImgName;
	image*		m_pImg;
	RECT		m_rc;
	float		m_fX;
	float		m_fY;
	POINT		m_ptBtnDown;
	POINT		m_ptBtnUp;
	POINT		m_ptBtnWait;

	typedef void(*CALLBACK_FUNC)(void);

	CALLBACK_FUNC	m_callbackFunction;

	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);
	ButtonState			m_state;

public:
	HRESULT init(const char* szImageName, int x, int y, POINT ptBtnDown, POINT ptBtnUp, POINT ptBtnWait);
	void release();
	virtual void update() override;
	virtual void render(HDC hdc) override;

	uiButton();
	~uiButton();
};

