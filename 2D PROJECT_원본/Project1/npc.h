#pragma once

struct n_tagState
{
	int index = 0;
	int count = 0;
	bool isState = false;
};

class npc
{
private:
	image * m_pImg;
	image * m_itemImg;
	RECT m_rc;
	RECT m_itemRC;
	
	n_tagState m_hang;
	n_tagState m_ropeHit;
	n_tagState m_fall;
	n_tagState m_move;
	n_tagState m_giveItem;
	n_tagState m_yesSir;//°æ·Ê
	n_tagState m_runAway;
	n_tagState m_item;
	SYNTHESIZE(float, m_fY, NPCPosY);
	SYNTHESIZE(float, m_fX, NPCPosX);
	int m_speed;
	int m_charNum;
	bool m_isAlive;
	bool m_checkRotation = false;

public:
	HRESULT init(const char* szFileName, float x, float y, int speed, int charNum);
	void release();
	void update();
	void render(HDC hdc);

	void npcAnimation();
	void itemAnimation();
	void move();

	inline bool getHangState() { return m_hang.isState; }
	inline void setMoveState(bool isMove) { m_move.isState = isMove; }
	inline bool getMoveState() { return m_move.isState; }
	inline void setFallState(bool isFall) { m_fall.isState = isFall; }
	inline bool getIsAlive() { return m_isAlive; }
	npc();
	~npc();
};

