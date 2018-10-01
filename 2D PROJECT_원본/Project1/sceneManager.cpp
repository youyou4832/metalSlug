#include "stdafx.h"
#include "sceneManager.h"
#include "scene.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	// ���� ���� �ʱ�ȭ�Ѵ�
	if (SUCCEEDED(sceneManager::m_pNextScene->init()))
	{
		sceneManager::m_pCurrScene = sceneManager::m_pNextScene;

		// �ε� ���� �����Ѵ�
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
	// ���� ��� ���Ҹ� ���鼭 Ȯ��
	for (m_iter = m_mapScenes.begin(); m_iter != m_mapScenes.end();)
	{
		// ������ value(scene*)�� ������
		if (m_iter->second != NULL)
		{
			// Ȯ���Ϸ��� ���� ���� ���̸� release ȣ��
			if (m_iter->second == m_pCurrScene)
				m_iter->second->release();

			// �޸� ����
			SAFE_DELETE(m_iter->second);

			// �� ���Ϳ��� ����
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
	// �ʿ��� �ٲٰ��� �ϴ� ���� ã�´�.
	m_iter = m_mapScenes.find(sceneName);

	// �ʿ��� �ٲٰ��� �ϴ� ���� ã�� ���ϸ�
	if (m_iter == m_mapScenes.end())	return E_FAIL;

	// �ʿ��� �ٲٰ��� �ϴ� ���� ���� ���̸�
	if (m_iter->second == m_pCurrScene) return S_OK;

	// �ٲٰ��� �ϴ� ���� ã���� �ʱ�ȭ
	if (SUCCEEDED(m_iter->second->init()))
	{
		// �ʱ�ȭ ���� �� ���� �� release
		if (m_pCurrScene)
			m_pCurrScene->release();

		// ���� ���� �ٲٰ��� �ϴ� ������ ��ü
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
	// �ʿ��� �ٲٰ��� �ϴ� ���� ã�´�.
	m_iter = m_mapScenes.find(nextSceneName);

	// �ʿ��� �ٲٰ��� �ϴ� ���� ã�� ���ϸ�
	if (m_iter == m_mapScenes.end())	return E_FAIL;

	// �ʿ��� �ٲٰ��� �ϴ� ���� ���� ���̸�
	if (m_iter->second == m_pCurrScene) return S_OK;

	// �ε� ���� ã��
	m_iterLoading = m_mapLoadingScenes.find(loadingSceneName);

	// �ε� ���� ��ã������ �Ϲ� �� ���
	if (m_iterLoading == m_mapLoadingScenes.end())
		return changeScene(nextSceneName);

	// �ε� ���� ã������ �ʱ�ȭ
	if (SUCCEEDED(m_iterLoading->second->init()))
	{
		// �ʱ�ȭ ���� �� ���� �� release
		if (m_pCurrScene)
			m_pCurrScene->release();

		// ���� ���� �ε� ������ ��ü
		m_pCurrScene = m_iterLoading->second;

		// ���� ���� �غ��Ѵ�.
		m_pNextScene = m_iter->second;

		// �����带 �߰� �����ؼ� ���ÿ� �ε��ϸ鼭 �ε�ȭ�鵵 �����Ѵ�. (������ �� �ϸ� ���ô� �ƴ�)
		// CreateThread��� �Լ��� ����Ѵ�. HANDLE�� ��ȯ������ handle���� ������ �ʿ�� ��� �ڵ� ���� �� ����.

		CloseHandle(CreateThread(
			NULL,				// ������ Ŀ�� ���� Ư��
			0,					// ������ ���� ũ�� ����
			loadingThread,		// ����� �Լ�
			NULL,				// ����� �Լ��� �Ѱ����� �Ű�����
			0,					// ������ ���� �÷��� (�츮�� ���� �ٲ� ���� ���� ���̴�.)
			NULL				// �������� ID (���� ���� �ʿ䰡 ����)
			// ������1�� main�Լ�, ������2�� ����Լ� ���� �����͸� �־�� ��
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
