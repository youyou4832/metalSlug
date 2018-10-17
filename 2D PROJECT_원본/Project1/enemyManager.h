#pragma once
#include "enemy.h"
class player;
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
	
	void setSniper(const char * textName, float x, float y, int speed, int charNum, player* player);
	void setCannon(const char * textName, float x, float y, int speed, int charNum, player* player, int enemyNumber);
	void setNormal(const char * textName, float x, float y, int speed, int charNum, player* player, int enemyNumber);
	void setTank(const char * textName, float x, float y, int speed, int charNum, player* player, int enemyNumber);

	inline std::vector<enemy*>	getVecEnemy() { return m_vecEnemy; }
	inline std::vector<enemy*>::iterator getIterEnemy() { return m_iter; }

	enemyManager();
	~enemyManager();
};

