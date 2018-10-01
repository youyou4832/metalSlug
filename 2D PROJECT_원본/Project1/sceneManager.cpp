#include "stdafx.h"
#include "sceneManager.h"
#include "scene.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	// 다음 씬을 초기화한다
	if (SUCCEEDED(sceneManager::m_pNextScene->init()))
	{
		sceneManager::m_pCurrScene = sceneManager::m_pNextScene;

		// 로딩 씬을 해제한다
		if (sceneManager::m_pLoadingScene)
		{
			sceneManager::m_pLoadingScene->release();
			sceneManager::m_pLoadingScene = NULL;
		}
	}

	return 0;
}

scene* sceneManager::m_pCurrScene = NULL;
scene* sceneManager::m_pNextScene = NULL;
scene* sceneManager::m_pLoadingScene = NULL;

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	// 맵의 모든 원소를 돌면서 확인
	for (m_iter = m_mapScenes.begin(); m_iter != m_mapScenes.end();)
	{
		// 원소의 value(scene*)가 있으면
		if (m_iter->second != NULL)
		{
			// 확인하려는 씬이 현재 씬이면 release 호출
			if (m_iter->second == m_pCurrScene)
				m_iter->second->release();

			// 메모리 해제
			SAFE_DELETE(m_iter->second);

			// 맵 벡터에서 삭제
			m_iter = m_mapScenes.erase(m_iter);
		}
		else
		{
			m_iter++;
		}
	}

	m_mapScenes.clear();
}

void sceneManager::update()
{
	if (m_pCurrScene)
		m_pCurrScene->update();
}

void sceneManager::render(HDC hdc)
{
	if (m_pCurrScene)
		m_pCurrScene->render(hdc);
}

scene * sceneManager::addScene(string sceneName, scene * pScene)
{
	if (!pScene) return NULL;

	m_mapScenes.insert(pair<string, scene*>(sceneName, pScene));
	//m_mapScenes.insert(make_pair(sceneName, pScene));

	return pScene;
}

HRESULT sceneManager::changeScene(string sceneName, int selNum)
{
	// 맵에서 바꾸고자 하는 씬을 찾는다.
	m_iter = m_mapScenes.find(sceneName);

	// 맵에서 바꾸고자 하는 씬을 찾지 못하면
	if (m_iter == m_mapScenes.end())	return E_FAIL;

	// 맵에서 바꾸고자 하는 씬이 현재 씬이면
	if (m_iter->second == m_pCurrScene) return S_OK;

	// 바꾸고자 하는 씬을 찾으면 초기화
	if (SUCCEEDED(m_iter->second->init()))
	{
		// 초기화 성공 시 현재 씬 release
		if (m_pCurrScene)
			m_pCurrScene->release();

		// 현재 씬을 바꾸고자 하는 씬으로 교체
		m_pCurrScene = m_iter->second;

		return S_OK;
	}

	return E_FAIL;
}

scene * sceneManager::addLoadingScene(string loadingSceneName, scene * pScene)
{
	if (!pScene) return NULL;

	m_mapLoadingScenes.insert(pair<string, scene*>(loadingSceneName, pScene));
	//m_mapScenes.insert(make_pair(sceneName, pScene));

	return pScene;
}

HRESULT sceneManager::changeScene(string nextSceneName, string loadingSceneName)
{
	// 맵에서 바꾸고자 하는 씬을 찾는다.
	m_iter = m_mapScenes.find(nextSceneName);

	// 맵에서 바꾸고자 하는 씬을 찾지 못하면
	if (m_iter == m_mapScenes.end())	return E_FAIL;

	// 맵에서 바꾸고자 하는 씬이 현재 씬이면
	if (m_iter->second == m_pCurrScene) return S_OK;

	// 로딩 씬을 찾고
	m_iterLoading = m_mapLoadingScenes.find(loadingSceneName);

	// 로딩 씬을 못찾았으면 일반 씬 출력
	if (m_iterLoading == m_mapLoadingScenes.end())
		return changeScene(nextSceneName);

	// 로딩 씬을 찾았으면 초기화
	if (SUCCEEDED(m_iterLoading->second->init()))
	{
		// 초기화 성공 시 현재 씬 release
		if (m_pCurrScene)
			m_pCurrScene->release();

		// 현재 씬을 로딩 씬으로 교체
		m_pCurrScene = m_iterLoading->second;

		// 다음 씬을 준비한다.
		m_pNextScene = m_iter->second;

		// 쓰레드를 추가 생성해서 동시에 로드하면서 로딩화면도 갱신한다. (엄연히 말 하면 동시는 아님)
		// CreateThread라는 함수를 사용한다. HANDLE을 반환하지만 handle값을 저장할 필요는 없어서 핸들 생성 안 했음.

		CloseHandle(CreateThread(
			NULL,				// 스레드 커널 보안 특성
			0,					// 스레드 스택 크기 설정
			loadingThread,		// 실행될 함수
			NULL,				// 실행될 함수에 넘겨지는 매개변수
			0,					// 스레드 제어 플래그 (우리가 직접 바꿀 일은 없을 것이다.)
			NULL				// 스레드의 ID (굳이 받을 필요가 없음)
			// 쓰레드1번 main함수, 스레드2번 펑션함수 등의 포인터를 넣어야 함
		));

		return S_OK;
	}

	return E_FAIL;
}

scene * sceneManager::findScene(string sceneName, scene * pScene)
{
	if (!pScene) return NULL;

	m_iter = m_mapScenes.find(sceneName);

	pScene = m_iter->second;

	return pScene;
}

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}
