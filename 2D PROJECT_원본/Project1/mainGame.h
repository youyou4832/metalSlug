#pragma once
class titleScene;
class introScene;
class pixelCollision;

class mainGame
{
private:
	// DC
	HDC hdc;

	// ¹é¹öÆÛ
	image *			m_pBackBuffer;
	void			setBackBuffer();

	char m_szText[128];
	// scene list
	titleScene*		m_pTitleScene;
	introScene*		m_pIntroScene;
	pixelCollision*	m_pPixelCollisionScene;

public:
	int m_nScene;
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame();
	~mainGame();
};

