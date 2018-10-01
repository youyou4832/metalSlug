#pragma once

class scene
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	scene();
	virtual ~scene();
};

