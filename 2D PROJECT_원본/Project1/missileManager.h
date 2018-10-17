#pragma once
#include "missile.h"
class missileManager
{
private:
	std::vector<missile*>	m_vecMissile;
	std::vector<missile*>::iterator	m_iter;

	const char* m_szImageName;
	float		m_fRange;
	int m_nMaxCount;
public:
	HRESULT init(const char* szImageName, float range, int maxCount);
	HRESULT init(int maxCount);
	void release();
	void update();
	void render(HDC hdc, int charNum);

	void fire(float x, float y, float angle, float speed, int charNum);
	void fire(float x, float y, int charNum);
	void move();

	inline std::vector<missile*> getVecMissile()
	{
		return m_vecMissile;
	}

	// �̻����� �̹����� �ٲ��ִ� image Getter, Setter �Լ�
	inline const char * getImageName() { return m_szImageName; }
	inline void setImageName(const char * szImageName) { m_szImageName = szImageName; }

	//inline void setTarget(player* pTarget) { m_pTarget = pTarget; }

	missileManager();
	~missileManager();
};

