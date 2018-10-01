#pragma once

// commonMacroFunction

// ����Ʈ ���� �Լ�
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

// ������ �׷��ִ� �Լ�
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

// �׸� �׷��ִ� �Լ�
// 1��° ���� : left
// 2��° ���� : top
// 3��° ���� : �ʺ� (x + width)
// 4��° ���� : ���� (y + height)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

// �׸� �׷��ִ� �Լ� (���� ����)
// 1��° ���� : �߽� x ��ǥ
// 2��° ���� : �߽� y ��ǥ
// 3��° ���� : �ʺ�
// 4��° ���� : ����
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2,
		x + width / 2, y + height / 2 };
	return rc;
}

// ���� �׷��ִ� �Լ�
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// ���� �׷��ִ� �Լ� (���� ����)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2,
		x + width / 2, y + height / 2);
}