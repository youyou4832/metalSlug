#pragma once
#include "npc.h"

class npcManager
{
private:
	vector<npc*> m_vecNPC;
	vector<npc*>::iterator m_iter;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setNPC(const char * textName, float x, float y, int speed);

	inline vector<npc*> getVecNPC() { return m_vecNPC; }
	inline vector<npc*>::iterator getIterNPC() { return m_iter; }

	npcManager();
	~npcManager();
};

