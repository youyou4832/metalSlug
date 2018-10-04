#pragma once
#include <vector>

class animation
{
private:
	int		m_nFrameNum;					// 프레임 수
	std::vector<POINT>	m_vecFrameList;		// 프레임 x, y
	std::vector<int>	m_vecPlayList;		// 프레임 플레이 리스트 (프레임 순서)

	int		m_nFrameWidth;
	int		m_nFrameHeight;

	bool	m_isLoop;						// 반복 실행 여부
	float	m_fFrameUpdateSec;				// 프레임 업데이트 시간
	float	m_fElapsedSec;					// 누적 시간 (프레임 업데이트 시간과 비교해서 다음 프레임으로 넘어가기 위한 시간)
	
	int		m_nNowPlayIdx;					// 현재 플레이 되고 있는 인덱스 (m_vecPlayList 값을 참조)

	bool	m_isPlaying;					// 현재 플레이 여부

public:
	HRESULT	init(int totalWidth, int totalHeight, int frameWidth, int frameHeight);

	HRESULT init(int totalWidth, int totalHeight, int frameWidth, int frameHeight, int startY);

	// 세팅
	void setDefPlayFrame(bool reverse = false, bool loop = false);		// 기본 세팅
	void setPlayFrame(int* arrPlay, int arrLen, bool loop = false);		//
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	void setFPS(int fps);	// 초당 갱신 횟수 설정

	// 업데이트
	void frameUpdate(float elapsedTime);	// 프레임 업데이트

	void start();
	void stop();
	void pause();
	void resume();

	inline POINT getFramePos() { return m_vecFrameList[m_vecPlayList[m_nNowPlayIdx]]; }

	//m_vecFrameList[0];		// 가져오고 싶은 프레임의 인덱스를 넣는다
	// 플레이 리스트 원소 : 9, 10, 11, 0, 1, 2 
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

