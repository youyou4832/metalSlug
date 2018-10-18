#include "stdafx.h"
#include "image.h"
#include "animation.h"

#pragma comment (lib, "msimg32.lib")

image::image()
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, 
		WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char * szFileName, int width, int height, bool trans /*= false*/, COLORREF transColor)
{
	if (szFileName == NULL) return E_FAIL;

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// ���� �÷� ����
	m_isTransparent = trans;
	m_transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char * szFileName, float x, float y,
	int width, int height, int frameX, int frameY,
	bool trans, COLORREF transColor)
{
	if (szFileName == NULL) return E_FAIL;

	HDC hdc = GetDC(g_hWnd);

	m_pImageInfo = new IMAGE_INFO;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pImageInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pImageInfo->hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		szFileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pImageInfo->hOldBitmap = (HBITMAP)SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hBitmap);

	m_pImageInfo->fX = x;
	m_pImageInfo->fY = y;
	m_pImageInfo->nCurrFrameX = 0;
	m_pImageInfo->nCurrFrameY = 0;
	m_pImageInfo->nWidth = width;
	m_pImageInfo->nHeight = height;
	m_pImageInfo->nFrameWidth = width / frameX;
	m_pImageInfo->nFrameHeight = height / frameY;
	m_pImageInfo->nMaxFrameX = frameX - 1;
	m_pImageInfo->nMaxFrameY = frameY - 1;

	// ���� ����
	// �ɼ�
	m_blendFunc.AlphaFormat = 0;
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.BlendOp = AC_SRC_OVER;

	// ���� ���� ����� ���� �߰� �̹���
	m_pBlendImage = new IMAGE_INFO;
	m_pBlendImage->hMemDC = CreateCompatibleDC(hdc);
	m_pBlendImage->hBitmap = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	m_pBlendImage->hOldBitmap = (HBITMAP)SelectObject(
		m_pBlendImage->hMemDC, m_pBlendImage->hBitmap);
	m_pBlendImage->nWidth = WINSIZEX;
	m_pBlendImage->nHeight = WINSIZEY;

	// ���� �÷� ����
	m_isTransparent = trans;
	m_transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (m_pImageInfo->hBitmap == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void image::release()
{
	if (m_pBlendImage)
	{
		SelectObject(m_pBlendImage->hMemDC, m_pBlendImage->hOldBitmap);
		DeleteObject(m_pBlendImage->hBitmap);
		DeleteDC(m_pBlendImage->hMemDC);

		delete m_pBlendImage;
	}

	if (m_pImageInfo)
	{
		SelectObject(m_pImageInfo->hMemDC, m_pImageInfo->hOldBitmap);
		DeleteObject(m_pImageInfo->hBitmap);
		DeleteDC(m_pImageInfo->hMemDC);

		delete m_pImageInfo;
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// ������
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// ����� ũ��
			
			// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			0, 0,					// ����� ���� ������ǥ
			m_pImageInfo->nWidth,
			m_pImageInfo->nHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		// hdc : ����� ������ DC
		// destX : ����� ������ x ��ǥ
		// destY : ����� ������ y ��ǥ
		// cx : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// cy : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// hdcSrc : ������ ������ �����ϴ� DC
		// x1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// y1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// rop : �����ϴ� �ɼ� (SRCCOPY)
		BitBlt(
			hdc, 
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, 
	int sourX, int sourY, int sourWidth, int sourHeight, int scalar, bool reverse /*false*/)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// ������
			hdc,					// ����� ������ DC
			destX, destY,			// ����� ��ǥ ������
			sourWidth * scalar, 
			sourHeight * scalar,	// ����� ũ��

									// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			sourX, sourY,			// ����� ���� ������ǥ
			sourWidth,
			sourHeight,				// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		// hdc : ����� ������ DC
		// destX : ����� ������ x ��ǥ
		// destY : ����� ������ y ��ǥ
		// cx : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// cy : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// hdcSrc : ������ ������ �����ϴ� DC
		// x1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// y1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// rop : �����ϴ� �ɼ� (SRCCOPY)
		// rop : ������ : DSTINVERT

		if (reverse == false)
		{
			BitBlt(
				hdc,
				destX, destY,
				m_pImageInfo->nWidth, m_pImageInfo->nHeight,
				m_pImageInfo->hMemDC,
				0, 0, SRCCOPY);
		}
		else if (reverse == true)
		{
			BitBlt(
				hdc,
				destX, destY,
				m_pImageInfo->nWidth, m_pImageInfo->nHeight,
				m_pImageInfo->hMemDC,
				0, 0, NOTSRCCOPY);
		}
	}
}

void image::render(HDC hdc, float destX, int destY,
	int sourX, int sourY, int sourWidth, int sourHeight, int scalar)
{
	if (m_isTransparent)
	{
		GdiTransparentBlt(
			// ������
			hdc,					// ����� ������ DC
			destX, destY,			// ����� ��ǥ ������
			sourWidth * scalar,
			sourHeight * scalar,	// ����� ũ��

									// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			sourX, sourY,			// ����� ���� ������ǥ
			sourWidth,
			sourHeight,				// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		// hdc : ����� ������ DC
		// destX : ����� ������ x ��ǥ
		// destY : ����� ������ y ��ǥ
		// cx : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// cy : ����� �̹����� ����������� ����� ���ΰ��� ���ΰ�
		// hdcSrc : ������ ������ �����ϴ� DC
		// x1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// y1 : �̹����� �������� �߶� ���ΰ��� ���ΰ�
		// rop : �����ϴ� �ɼ� (SRCCOPY)
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY)
{
	m_pImageInfo->nCurrFrameX = currFrameX;
	m_pImageInfo->nCurrFrameY = currFrameY;

	if (currFrameX > m_pImageInfo->nMaxFrameX)
		m_pImageInfo->nCurrFrameX = m_pImageInfo->nMaxFrameX;
	if (currFrameY > m_pImageInfo->nMaxFrameY)
		m_pImageInfo->nCurrFrameY = m_pImageInfo->nMaxFrameY;

	if (m_isTransparent)
	{
		GdiTransparentBlt(
			hdc,	// ����� ������ DC
			destX, destY,		// ����� ��ǥ ������
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� ũ��

									// ���
			m_pImageInfo->hMemDC,	// ������ ��� DC
			m_pImageInfo->nFrameWidth * m_pImageInfo->nCurrFrameX,
			m_pImageInfo->nFrameHeight * m_pImageInfo->nCurrFrameY,					// ����� ���� ������ǥ
			m_pImageInfo->nFrameWidth,
			m_pImageInfo->nFrameHeight,	// ����� �������� ��ǥ

			m_transColor);			// ���翡�� ������ ����
	}
	else
	{
		BitBlt(
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. ����ؾߵǴ� DC�� �׷����ִ� ������ blendImage�� ����
		BitBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			SRCCOPY);

		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC�� ����ؾߵǴ� DC�� ����
		AlphaBlend(hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			m_pImageInfo->fX, m_pImageInfo->fY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ������ ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. ����ؾߵǴ� DC�� �׷����ִ� ������ blendImage�� ����
		BitBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);
		// 3. blendDC�� ����ؾߵǴ� DC�� ����
		AlphaBlend(
			// ������
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			destX, destY,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			// ������ ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int scalar, BYTE alpha)
{
	m_blendFunc.SourceConstantAlpha = alpha;

	if (m_isTransparent)
	{
		// 1. ����ؾߵǴ� DC�� �׷����ִ� ������ blendImage�� ����
		BitBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			hdc,
			destX, destY,
			SRCCOPY);

		// 2. ����� �̹����� blendImage�� ����
		GdiTransparentBlt(
			// ������
			m_pBlendImage->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,

			// ���
			m_pImageInfo->hMemDC,
			0, 0,
			m_pImageInfo->nWidth, m_pImageInfo->nHeight,
			m_transColor);

		// 3. blendDC�� ����ؾߵǴ� DC�� ����
		AlphaBlend(
			// ������
			hdc,
			destX, destY,
			sourWidth * scalar,
			sourHeight * scalar,

			// ���
			m_pBlendImage->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			m_blendFunc);
	}
	else
	{
		AlphaBlend(
			// ������ ��ǥ
			hdc,
			destX, destY,
			sourWidth * scalar, sourHeight * scalar,
			// ������ ���
			m_pImageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			m_blendFunc);
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani, int scalar, bool reverse /*false*/, int alpha /*0*/)
{
	// ���İ��� �����Ѵٸ� ���ķ��� ����

	if (alpha != 0)
		alphaRender(hdc, destX, destY,
			ani->getFramePos().x, ani->getFramePos().y,
			ani->getFrameWidth(), ani->getFrameHeight(), scalar, alpha);

	else
	render(hdc, destX, destY,
		ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight(), scalar, reverse);
}

void image::setTransColor(bool trans, COLORREF transColor)
{
	m_isTransparent = trans;
	m_transColor = transColor;
}
