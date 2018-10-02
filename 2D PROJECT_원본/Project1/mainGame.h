#pragma once
class titleScene;
class battleScene;
class bossScene;
class endScene;
class selectScene;
class gameoverScene;
class loadingScene;
class uiTestScene;
class pixelCollision;
class tileMap;

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
	battleScene*	m_pBattleScene;
	bossScene*		m_pBossScene;
	endScene*		m_pEndScene;
	selectScene*	m_pSelectScene;
	gameoverScene*	m_pGameoverScene;
	loadingScene*	m_pLoadingScene;
	uiTestScene*	m_pUiTestScene;
	pixelCollision*	m_pPixelCollisionScene;
	tileMap*		m_pTileMapScene;

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

