#include "stdafx.h"
#include "gameNode.h"



HRESULT gameNode::init()
{
	//HANDLE hTimer = (HANDLE)SetTimer(g_hWnd, 1, 10, NULL);
	//KEYMANAGER->init();
	//IMAGEMANAGER->init();

	////setBackBuffer();

	return S_OK;
}

void gameNode::release()
{
	//if (m_pBackBuffer)	delete m_pBackBuffer;

	//KillTimer(g_hWnd, 1);
	//KEYMANAGER->releaseSingleton();
	//IMAGEMANAGER->releaseSingleton();
}

void gameNode::update()
{
	InvalidateRect(g_hWnd, NULL, false);
}

void gameNode::render(HDC hdc)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}
