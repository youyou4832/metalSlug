#pragma once
#include "singletonBase.h"
class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	typedef vector<effect*>			vecEffect;
	//map<string, vector<effect*>>	m_mapEffects;		// �̰Ͱ�
	map<string, vecEffect>	m_mapEffects;				// �̰��� ����. (typedef => type define)
	map<string, vecEffect>::iterator m_iter;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc, int scalar = 1);

	void addEffect(string effectName, const char* imageName,
		int imageWidth, int imageHeight,
		int frameWidth, int frameHeight,
		int fps, float elapsedTime, int bufferCount);

	void play(string effectName, int x, int y);

	effectManager();
	~effectManager();
};

