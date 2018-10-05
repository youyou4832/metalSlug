#pragma once
#include "enemy.h"
class enemyManager
{
private:
	std::vector<enemy*>	m_vecEnemy;
	std::vector<enemy*>::iterator	m_iter;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void setEnemy(int enemyNum, int speed, const char * textName, int charNum);

	inline std::vector<enemy*>	getVecEnemy() { return m_vecEnemy; }
	inline std::vector<enemy*>::iterator getIterEnemy() { return m_iter; }
	enemyManager();
	~enemyManager();
};

