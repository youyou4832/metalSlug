#pragma once

#define BRUDEGE_NUM 19

struct  bridgeInfo{
	image * m_pimgBridege;
	image * m_pimgPixels;
	bool m_isAilve;
};

class bridge
{
private:

	bridgeInfo m_bridge[BRUDEGE_NUM];
	image* m_maxBridge;
	image* m_maxBridge2;
	
	/*image * m_pimgBridege[BRUDEGE_NUM];
	image * m_pimgSubBridege;*/
	image * m_pimgPixels;
	RECT rc;
	RECT rc2;

	float m_bridgeDestX[BRUDEGE_NUM];
	float m_bridgeDestY;

	int m_bridgeSourX[BRUDEGE_NUM];

	int m_bridgeSourY;

	int m_bridgeWidth;
	int m_bridgeHeight;



	float m_PosX;

	int m_Scalar;
	int m_Destruction;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual image * getImgPixels(int i) { return m_bridge[i].m_pimgPixels; }

	bridge();
	~bridge();
};

