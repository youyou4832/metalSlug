#pragma once
#include <vector>

class animation
{
private:
	int		m_nFrameNum;					// ������ ��
	std::vector<POINT>	m_vecFrameList;		// ������ x, y
	std::vector<int>	m_vecPlayList;		// ������ �÷��� ����Ʈ (������ ����)

	int		m_nFrameWidth;
	int		m_nFrameHeight;

	bool	m_isLoop;						// �ݺ� ���� ����
	float	m_fFrameUpdateSec;				// ������ ������Ʈ �ð�
	float	m_fElapsedSec;					// ���� �ð� (������ ������Ʈ �ð��� ���ؼ� ���� ���������� �Ѿ�� ���� �ð�)
	
	int		m_nNowPlayIdx;					// ���� �÷��� �ǰ� �ִ� �ε��� (m_vecPlayList ���� ����)

	bool	m_isPlaying;					// ���� �÷��� ����

public:
	HRESULT	init(int totalWidth, int totalHeight, int frameWidth, int frameHeight);

	HRESULT init(int totalWidth, int totalHeight, int frameWidth, int frameHeight, int startY);

	// ����
	void setDefPlayFrame(bool reverse = false, bool loop = false);		// �⺻ ����
	void setPlayFrame(int* arrPlay, int arrLen, bool loop = false);		//
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	void setFPS(int fps);	// �ʴ� ���� Ƚ�� ����

	// ������Ʈ
	void frameUpdate(float elapsedTime);	// ������ ������Ʈ

	void start();
	void stop();
	void pause();
	void resume();

	inline POINT getFramePos() { return m_vecFrameList[m_vecPlayList[m_nNowPlayIdx]]; }

	//m_vecFrameList[0];		// �������� ���� �������� �ε����� �ִ´�
	// �÷��� ����Ʈ ���� : 9, 10, 11, 0, 1, 2 
	// m_nNowPlayIdx == 0 => 9 
	// m_nNowPlayIdx == 1 => 10
	// 0 == m_vecPlayList[m_nNowPlayIdx];

	inline int getFrameWidth() { return m_nFrameWidth; }
	inline void setFrameWidth(int frameWidth) { m_nFrameWidth = frameWidth; }	

	inline int getFrameHeight() { return m_nFrameHeight; }
	inline void setFrameHeight( int frameHeight ) { m_nFrameHeight = frameHeight; }

	inline float getFrameUpdateSec() { return m_fFrameUpdateSec; }
	inline void setFrameUpdateSec(float frameUpdateSec) { m_fFrameUpdateSec = frameUpdateSec; }

	inline bool getIsPlaying() { return m_isPlaying; }

	animation();
	~animation();
};

