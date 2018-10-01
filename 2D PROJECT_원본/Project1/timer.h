#pragma once
class timer
{
private:
	bool	m_isHardware;
	__int64	m_periodFrequency;	// �ð� ����(������ �ð�)
	__int64	m_currTime;			// ���� ������ �ϴ� ���� ����(������ �ٸ���)
	__int64	m_lastTime;
	float	m_timeElapsed;
	float	m_timeScale;

	unsigned long	m_frameRate;		// FPS
	unsigned long	m_fpsFrameCount;	// FPS ī��Ʈ
	// FPS ������ �ð��� ���� �ð��� �����
	float			m_fpsTimeElapsed;	
	float			m_worldTime;		// ����Ÿ��

public:
	HRESULT init();
	void tick(float lockFPS = 0.0f);

	inline float getElapsedTime() { return m_timeElapsed; }
	inline float getWorldTime() { return m_worldTime; }
	inline unsigned long getFrameRate() { return m_frameRate; }

	timer();
	~timer();
};

