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
	hFile = CreateFile(saveFileName,	// ���̺��� ���� ��� / �����̸�
		GENERIC_WRITE,			// ���� ��� ����
		0,						// ���� ���� ��� ���� (0) : ���� ����
								// FILE_SHARE_DELETE : ���� ���� ��û�� ����	/ FILE_SHARE_READ, FILE_SHARE_WRITE�� ����
		NULL,					// ���� ���� �ɼ�
		CREATE_ALWAYS,			// CREATE_ALWAYS : ���ο� ���� ����, ������ �̸��� ������ ������ �����
								// CREATE_NEW : ���ο� ���� ����
								// OPEN_EXISTING : ������ �����ϸ� ����, ������ �����ڵ� ����
		FILE_ATTRIBUTE_NORMAL /* | */,	// FILE_ATTRIBUTE_NORMAL : �ٸ� �Ӽ��� ����			// F12�� ���� �� ���� ��� �� ���� �����ִ� ���� �� �� �ִ�. (16��Ʈ �ڸ� ��(?)���� �� ����), ��Ʈ����(OR) ��� ����.
										// FILE_ATTRIBUTE_READONLY : �б� ���� ����
										// FILE_ATTRIBUTE_HIDDEN : ���� ���� ����
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
