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
	SYNTHESIZE(bool, m_isGive, IsGive);
	float m_itemX;
	float m_itemY;
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
	inline bool getFallState() { return m_fall.isState; }
	inline bool getIsAlive() { return m_isAlive; }
	inline RECT getRect() { return m_rc; }
	inline void setIsGiveItem(bool isGiveItem) { m_giveItem.isState = isGiveItem; }
	inline bool getIsGiveItem() { return m_giveItem.isState; }
	inline void setItemState(bool state) { m_item.isState = state; }
	inline bool getItemState() { return m_item.isState; }
	inline RECT getItemRect() { return m_itemRC; }
	inline void setRopeHitState(bool state) { m_ropeHit.isState = state; }
	inline bool getRopeHitState() { return m_ropeHit.isState; }
	
	npc();
	~npc();
};

