#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	deleteImageAll();
}

image * imageManager::addImage(std::string strKey, int width, int height)
{
	image* img = findImage(strKey);
	if (img)	return img;

	img = new image;

	if (FAILED(img->init(width, height)))
	{
		delete img;
		return NULL;
	}

	m_map.insert(std::make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(std::string strKey, 
	const char * szFileName, int width, int height, 
	bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	if (img)	return img;

	img = new image;

	if (FAILED(img->init(
		szFileName, width, height, trans, transColor)))
	{
		delete img;
		return NULL;
	}

	m_map.insert(std::make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(std::string strKey, 
	const char * szFileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);
	if (img)	return img;

	img = new image;

	if (FAILED(img->init(
		szFileName, 0, 0, width, height,
		frameX, frameY, trans, transColor)))
	{
		delete img;
		return NULL;
	}

	m_map.insert(std::make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(std::string strKey)
{
	// 찾으면 해당 원소의 주소가 리턴, 없으면 m_map.end()가 리턴
	m_iter = m_map.find(strKey);

	if (m_iter != m_map.end())
	{
		// iterator -> first : key ( string )
		// iterator -> second : value ( image* )
		return m_iter->second;
	}

	return NULL;
}

bool imageManager::deleteImage(std::string strKey)
{
	m_iter = m_map.find(strKey);

	if (m_iter != m_map.end())
	{
		// 이미지 삭제
		m_iter->second->release();
		// 메모리 해제
		delete m_iter->second;

		m_map.erase(strKey);

		return true;
	}

	return false;
}

bool imageManager::deleteImageAll()
{
	m_iter = m_map.begin();

	for (; m_iter != m_map.end(); )
	{
		if (m_iter->second != NULL)
		{
			delete m_iter->second;
			m_iter = m_map.erase(m_iter);
		}
		else
		{
			m_iter++;
		}
	}

	m_map.clear();

	return true;
}
