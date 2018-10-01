#pragma once

enum BUTTON_STATE
{
	IDLE,
	WAIT,
	UP,
	DOWN,
	NUM
};

class button
{
private:
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

	BUTTON_STATE m_state;

public:
	HRESULT init(const char* szImageName, int x, int y, POINT ptBtnDown, POINT ptBtnUp, POINT ptBtnWait, CALLBACK_FUNC cb);
	void release();
	void update();
	void render(HDC hdc);

	button();
	~button();
};

