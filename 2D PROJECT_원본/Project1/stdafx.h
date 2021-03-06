// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <map>

using namespace std;

typedef struct tagSaveData
{
	int	selected_player_id;
	bool isMoveMap = false;
}SAVE_DATA;

typedef struct tagFloatPoint
{
	float x;
	float y;

	tagFloatPoint() { x = 0; y = 0; }
	//tagFloatPoint(float _x, float _y) { x = _x; y = _y; }
} FPOINT;

#define SYNTHESIZE(varType, varName, funcName)\
protected: varType varName;\
public: varType get##funcName() { return varName; }\
public: void set##funcName(varType var) { varName = var; }
#define TOTAL_ENEMY 36 //1: 6,	2: 7	3: 7	4: 8	5:8 
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "txtData.h"
#include "timeManager.h"
#include "keyManager.h"
#include "imageManager.h"
#include "sceneManager.h"
#include "effectManager.h"
#include "uiManager.h"
#include "soundManager.h"
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "utils.h"
#include "mainGame.h"

#include <CommDlg.h>

#define MAP_TOOL	// FULL_SCREEN, WINDOW_SCREEN, MAP_TOOL

//#define FULL_SCREEN
#ifdef FULL_SCREEN
	#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE
	#define WINSTARTX 0
	#define WINSTARTY 0
	#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
	#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)

#elif defined MAP_TOOL
	#define WINSTYLE	WS_OVERLAPPEDWINDOW
	#define WINSTARTX 50
	#define WINSTARTY 50
	#define WINSIZEX 1600
	#define WINSIZEY 800

#else
	#define WINSTYLE	WS_OVERLAPPEDWINDOW
	#define WINSTARTX 50
	#define WINSTARTY 50
	#define WINSIZEX 600
	#define WINSIZEY 800
#endif

#define PI	3.141592f
#define FPS	60

#define SAFE_DELETE(p) { if (p) delete p; p = NULL; }

#define RANDOM randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define	SCENEMANAGER sceneManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define UIMANAGER uiManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern SAVE_DATA	g_saveData;
extern POINT		g_ptMouse;
extern mainGame		g_mainGame;

enum CharInfo{i_normal, i_sniper, i_cannon, i_tank, i_sandbag, i_nomalboss, i_rageboss, i_player, i_npc};