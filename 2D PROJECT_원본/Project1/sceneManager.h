#pragma once
#include "singletonBase.h"
class scene;

class sceneManager : public singletonBase<sceneManager>
{
private:
	map<string, scene*>				m_mapScenes;
	map<string, scene*>				m_mapLoadingScenes;
	map<string, scene*>::iterator	m_iter;
	map<string, scene*>::iterator	m_iterLoading;

	// static은 해당 지역에서만 접근이 가능하다.
	// 
	static scene*	m_pCurrScene;		// 현재 씬
	static scene*	m_pNextScene;		// 전환 대기 중인 씬
	static scene*	m_pLoadingScene;	// 로딩 씬

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	// 일반 씬
	scene* addScene(string sceneName, scene* pScene);
	HRESULT changeScene(string sceneName, int selNum = 0);

	// 일반 + 로딩 씬
	scene* addLoadingScene(string loadingSceneName, scene* pScene);
	HRESULT changeScene(string nextSceneName, string loadingSceneName);

	// loading Thread에서 호출할 함수
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	scene * findScene(string sceneName, scene * pScene);

	sceneManager();
	~sceneManager();
};

