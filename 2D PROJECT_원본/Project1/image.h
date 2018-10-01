#pragma once
class animation;

class image
{
public:

	typedef struct tagImageInfo
	{
		HDC		hMemDC;	// ȭ�鿡 ��, ��, ���� ���� �׸� �� �ʿ��� ������ �����ϴ� ��ü
						// �׸��� �׸� �� �ʿ��� �޸� ���� �Ҵ�(��ȭ�� ����)
		HBITMAP	hBitmap;	// �̹������� �ε忡 ���Ǵ� ��ü
		HBITMAP hOldBitmap;
		int		nWidth;		// �̹��� �ʺ�
		int		nHeight;	// �̹��� ����

		// �ִϸ��̼��� ���� �߰�����
		float	fX;
		float	fY;
		int		nCurrFrameX;
		int		nCurrFrameY;
		int		nMaxFrameX;
		int		nMaxFrameY;
		int		nFrameWidth;
		int		nFrameHeight;

		tagImageInfo()
		{
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBitmap = NULL;
			nWidth = 0;
			nHeight = 0;

			fX = 0;
			fY = 0;
			nCurrFrameX = 0;
			nCurrFrameY = 0;
			nMaxFrameX = 0;
			nMaxFrameY = 0;
			nFrameWidth = 0;
			nFrameHeight = 0;
		}

		//void init();

		//~tagImageInfo() {}
	} IMAGE_INFO, *LPIMAGE_INFO;

	//tagImageInfo* pImage_info;
	//IMAGE_INFO image_info;
	//LPIMAGE_INFO image_info_1;

private:
	LPIMAGE_INFO	m_pImageInfo;
	bool			m_isTransparent;
	COLORREF		m_transColor;

	// ���� ����
	BLENDFUNCTION	m_blendFunc;	// ���� ���带 ���� ����
	LPIMAGE_INFO	m_pBlendImage;	// ���� ���带 ����ϱ� ���� �߰� �̹���

public:
	image();
	~image();

	HDC getMemDC() { return m_pImageInfo->hMemDC; }

	// �� ��Ʈ�ʰ����� �����Ѵ�
	HRESULT init(int width, int height);

	// �̹��� ����(���Ϸκ��� �о�´�)
	HRESULT init(const char* szFileName, int width, int height
	, bool trans = false, COLORREF transColor = 0);

	// �̹��� + ������ ���� �ʱ�ȭ
	HRESULT init(const char* szFileName, float x, float y, 
		int width, int height, int frameX, int frameY
		, bool trans = false, COLORREF transColor = 0);


	void release();

	// ����
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int scalar = 1);

	// ������ ����
	void frameRender(HDC hdc, int destX, int destY,
		int currFrameX, int currFrameY);

	// ���� ���� ����
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	// �ִϸ��̼� ����
	void aniRender(HDC hdc, int destX, int destY, animation* ani, int scalar = 1);

	void setTransColor(bool trans, COLORREF transColor);

	// getter, setter
	inline void setX(float x) { m_pImageInfo->fX = x; }
	inline float getX() { return m_pImageInfo->fX; }

	inline void setY(float y) { m_pImageInfo->fY = y; }
	inline float getY() { return m_pImageInfo->fY; }

	inline void setFrameX(int frame)
	{
		m_pImageInfo->nCurrFrameX = frame;
		if (m_pImageInfo->nCurrFrameX > m_pImageInfo->nMaxFrameX)
			m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	}
	inline int getFrameX() { return m_pImageInfo->nCurrFrameX; }

	inline void setFrameY(int frame)
	{
		m_pImageInfo->nCurrFrameY = frame;
		if (m_pImageInfo->nCurrFrameY > m_pImageInfo->nMaxFrameY)
			m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;
	}
	inline int getFrameY() { return m_pImageInfo->nCurrFrameY; }

	inline int getMaxFrameX() { return m_pImageInfo->nMaxFrameX; }
	inline int getMaxFrameY() { return m_pImageInfo->nMaxFrameY; }

	inline int getWidth()	{ return m_pImageInfo->nWidth; }
	inline int getHeight()	{ return m_pImageInfo->nHeight; }

	inline int getFrameWidth() { return m_pImageInfo->nFrameWidth; }
	inline int getFrameHeight() { return m_pImageInfo->nFrameHeight; }
};

