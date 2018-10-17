#pragma once
class bossScene;
class introScene;
class fightScene;

struct enemyPos {
	POINT e_pos;
	int charNum;
};

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
	bossScene*		m_pBossScene;
	introScene*		m_pIntroScene;
	fightScene*		m_pFightScene;

	image*	m_pixel;
	enemyPos m_enemyPos[TOTAL_ENEMY];
	int m_enemyCount;
public:
	int m_nScene;
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void setEnemyPosition();

	inline enemyPos getEnemyPosition(int i) { return m_enemyPos[i]; }

	mainGame();
	~mainGame();
};

