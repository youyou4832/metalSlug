#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{
}

void txtData::txtSave(const char * saveFileName, std::vector<std::string> vecStr)
{
	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vecStr), 126);

	HANDLE hFile;
	hFile = CreateFile(saveFileName,	// 세이브할 파일 경로 / 파일이름
		GENERIC_WRITE,			// 접근 방식 지정
		0,						// 파일 공유 방식 지정 (0) : 공유 안함
								// FILE_SHARE_DELETE : 삭제 접근 요청시 공유	/ FILE_SHARE_READ, FILE_SHARE_WRITE도 있음
		NULL,					// 보안 관련 옵션
		CREATE_ALWAYS,			// CREATE_ALWAYS : 새로운 파일 생성, 동일한 이름의 파일이 있으면 덮어쓴다
								// CREATE_NEW : 새로운 파일 생성
								// OPEN_EXISTING : 파일이 존재하면 오픈, 없으면 에러코드 리턴
		FILE_ATTRIBUTE_NORMAL /* | */,	// FILE_ATTRIBUTE_NORMAL : 다른 속성이 없다			// F12를 눌러 들어가 보면 몇개가 한 번에 묶여있는 것을 볼 수 있다. (16비트 자리 수(?)마다 한 묶음), 비트연산(OR) 사용 가능.
										// FILE_ATTRIBUTE_READONLY : 읽기 전용 파일
										// FILE_ATTRIBUTE_HIDDEN : 숨김 파일 생성
		NULL);

	WriteFile(hFile, str, 128, &write, NULL);
	CloseHandle(hFile);
}

char * txtData::vectorArrayCombine(std::vector<std::string> vecArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vecArray.size(); ++i)
	{
		strncat_s(str, 128, vecArray[i].c_str(), 126);
		if (i + 1 < vecArray.size())
			strcat_s(str, ",");
	}

	return str;
}

std::vector<std::string> txtData::txtLoad(const char * loadFileName)
{
	char str[128];
	DWORD read;

	HANDLE hFile;
	hFile = CreateFile(loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(hFile, str, 128, &read, NULL);

	CloseHandle(hFile);

	return charArraySeparation(str);
}

std::vector<std::string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vecStr;
	const char* separator = ",";
	char* token;
	char* temp;

	token = strtok_s(charArray, separator, &temp);
	
	vecStr.push_back(token);

	while ((token = strtok_s(NULL, separator, &temp)) != NULL)
	{
		vecStr.push_back(token);
	}

	return vecStr;
}

std::vector<int> txtData::txtLoadInt(const char * loadFileName)
{
	char str[128];
	DWORD read;

	HANDLE hFile;
	hFile = CreateFile(loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(hFile, str, 128, &read, NULL);

	CloseHandle(hFile);

	return charArraySeparationInt(str);
}

std::vector<int> txtData::charArraySeparationInt(char charArray[])
{
	vector<int> vecStr;
	const char* separator = ",";
	char* token;
	char* temp;
	int	tempInt;

	token = strtok_s(charArray, separator, &temp);

	tempInt = atoi(token);
	vecStr.push_back(tempInt);

	while ((token = strtok_s(NULL, separator, &temp)) != NULL)
	{
		vecStr.push_back(tempInt);
	}

	return vecStr;
}
