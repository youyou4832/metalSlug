#pragma once
class timer
{
private:
	bool	m_isHardware;
	__int64	m_periodFrequency;	// 시간 저장(정밀한 시간)
	__int64	m_currTime;			// 위의 변수와 하는 일은 같다(단위가 다르다)
	__int64	m_lastTime;
	float	m_timeElapsed;
	float	m_timeScale;

	unsigned long	m_frameRate;		// FPS
	unsigned long	m_fpsFrameCount;	// FPS 카운트
	// FPS 마지막 시간과 현재 시간의 경과량
	float			m_fpsTimeElapsed;	
	float			m_worldTime;		// 월드타임

public:
	HRESULT init();
	void tick(float lockFPS = 0.0f);

	inline float getElapsedTime() { return m_timeElapsed; }
	inline float getWorldTime() { return m_worldTime; }
	inline unsigned long getFrameRate() { return m_frameRate; }

	timer();
	~timer();
};

