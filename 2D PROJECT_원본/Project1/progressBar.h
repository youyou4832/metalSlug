#pragma once

class progressBar
{
private:
	RECT	m_rc;
	float	m_fX, m_fY;
	float	m_fWidth;
	float	m_fHeight;

	image*	m_imgTop;
	image*	m_imgBottom;

public:
	HRESULT init(float x, float y, float width, float height);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void setGauge(float currGauge, float maxGauge);
	void setX(float x) { m_fX = x; }
	void setY(float y) { m_fY = y; }
	void setWidth(float fWidth) { m_fWidth = fWidth; }
	float getWidth() { return m_fWidth; }

	progressBar();
	~progressBar();
};

