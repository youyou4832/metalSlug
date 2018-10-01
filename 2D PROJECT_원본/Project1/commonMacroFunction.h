#pragma once

// commonMacroFunction

// 포인트 생성 함수
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

// 라인을 그려주는 함수
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

// 네모를 그려주는 함수
// 1번째 인자 : left
// 2번째 인자 : top
// 3번째 인자 : 너비 (x + width)
// 4번째 인자 : 높이 (y + height)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

// 네모를 그려주는 함수 (원점 기준)
// 1번째 인자 : 중심 x 좌표
// 2번째 인자 : 중심 y 좌표
// 3번째 인자 : 너비
// 4번째 인자 : 높이
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2,
		x + width / 2, y + height / 2 };
	return rc;
}

// 원을 그려주는 함수
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// 원을 그려주는 함수 (원점 기준)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2,
		x + width / 2, y + height / 2);
}