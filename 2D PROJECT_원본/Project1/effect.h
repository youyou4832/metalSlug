#pragma once
class animation;
class image;

class effect
{
private:
	int m_fElapsedTime;
	bool m_isAlive;
	image* m_pImg;
	animation* m_pAnimation;

	int		m_nX;
	int		m_nY;
public:
	HRESULT	init(image* effectImage, int frameWidth, int frameHeight, int fps, float elapsedTime);
	void	release();
	void	update();
	void	render(HDC hdc, int scalar = 1);

	void	startEffect(int x, int y);
	void	endEffect();

	inline bool getIsAlive() { return m_isAlive; }
	inline void setIsAlive(bool isAlive) { m_isAlive = isAlive; }

	effect();
	~effect();
};