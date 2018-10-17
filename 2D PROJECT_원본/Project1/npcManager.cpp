#include "stdafx.h"
#include "npcManager.h"


HRESULT npcManager::init()
{
	return S_OK;
}

void npcManager::release()
{
	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 delete한다
	for (m_iter = m_vecNPC.begin(); m_iter != m_vecNPC.end(); m_iter++)
	{
		delete (*m_iter);
	}
	// vector 자체를 삭제한다
	m_vecNPC.clear();
}

void npcManager::update()
{
	for (m_iter = m_vecNPC.begin(); m_iter != m_vecNPC.end(); m_iter++)
	{
		(*m_iter)->update();
	}
}

void npcManager::render(HDC hdc)
{
	for (m_iter = m_vecNPC.begin(); m_iter != m_vecNPC.end(); m_iter++)
	{
		(*m_iter)->render(hdc);
	}
}

void npcManager::setNPC(const char * textName, float x, float y, int speed)
{
	npc* NPC;
	NPC = new npc;
	NPC->init(textName, x, y, speed, CharInfo::i_npc);
	m_vecNPC.push_back(NPC);
}

npcManager::npcManager()
{
}


npcManager::~npcManager()
{
}
