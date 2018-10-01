#pragma once
class animation;

class image
{
public:

	typedef struct tagImageInfo
	{
		HDC		hMemDC;	// 화면에 점, 선, 도형 등을 그릴 때 필요한 정보를 저장하는 객체
						// 그림을 그릴 때 필요한 메모리 공간 할당(도화지 개념)
		HBITMAP	hBitmap;	// 이미지파일 로드에 사용되는 객체
		HBITMAP hOldBitmap;
		int		nWidth;		// 이미지 너비
		int		nHeight;	// 이미지 높이

		// 애니메이션을 위한 추가변수
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

	// 알파 블렌드
	BLENDFUNCTION	m_blendFunc;	// 알파 블렌드를 위한 정보
	LPIMAGE_INFO	m_pBlendImage;	// 알파 블렌드를 사용하기 위한 중간 이미지

public:
	image();
	~image();

	HDC getMemDC() { return m_pImageInfo->hMemDC; }

	// 빈 비트맵공간을 생성한다
	HRESULT init(int width, int height);

	// 이미지 설정(파일로부터 읽어온다)
	HRESULT init(const char* szFileName, int width, int height
	, bool trans = false, COLORREF transColor = 0);

	// 이미지 + 프레임 정보 초기화
	HRESULT init(const char* szFileName, float x, float y, 
		int width, int height, int frameX, int frameY
		, bool trans = false, COLORREF transColor = 0);


	void release();

	// 렌더
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int scalar = 1);

	// 프레임 렌더
	void frameRender(HDC hdc, int destX, int destY,
		int currFrameX, int currFrameY);

	// 알파 블렌드 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	// 애니메이션 렌더
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

