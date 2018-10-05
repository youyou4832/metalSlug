#pragma once
#include "singletonBase.h"
#include "image.h"

#include <map>
#include <string>

// key와 value를 pair형태로 선언한다
// key는 map에서 유일한 값이다

class imageManager : public singletonBase<imageManager>
{
public:

	std::map<std::string, image*>	m_map;
	std::map<std::string, image*>::iterator m_iter;

public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	image* addImage(std::string strKey, int width, int height);
	image* addImage(std::string strKey, const char* szFileName,
		int width, int height, bool trans, COLORREF transColor);
	image* addImage(std::string strKey, const char* szFileName, 
		int width, int height, int frameX, int frameY,
		bool trans, COLORREF transColor);
	image* addImage(std::string strKey, const char* szFileName, float x, float y,
		int width, int height, int frameX, int frameY,
		bool trans, COLORREF transColor);
	image* findImage(std::string strKey);
	bool deleteImage(std::string strKey);
	bool deleteImageAll();
};

