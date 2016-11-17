#include "GameStateManager.h"

USING_NS_CC;

CGameStateManager* CGameStateManager::s_gameStateManagerInstance = NULL;

CGameStateManager::CGameStateManager()
{
}

CGameStateManager::~CGameStateManager()
{
	m_eStates.clear();
}

// Instance Methods
CGameStateManager* CGameStateManager::getInstance()
{
	if (!s_gameStateManagerInstance)
		s_gameStateManagerInstance = new CGameStateManager;
	return s_gameStateManagerInstance;
}

void CGameStateManager::destroy()
{
	if (s_gameStateManagerInstance)
		delete s_gameStateManagerInstance;
	s_gameStateManagerInstance = NULL;
}

// Normal Methods
// Public Methods
void CGameStateManager::startState(CGameStateManager::STATE state)
{
	if (!m_eStates.empty)
	{
		m_eStates.clear();
	}
	m_eStates.push_back(state);
}
void CGameStateManager::switchState(CGameStateManager::STATE state)
{
	if (!m_eStates.empty)
	{
		m_eStates.back() = state;
	}
	else
	{
		m_eStates.push_back(state);
	}
}
void CGameStateManager::pushState(CGameStateManager::STATE state)
{
	m_eStates.push_back(state);
}
CGameStateManager::STATE CGameStateManager::popState()
{
	if (!m_eStates.empty)
	{
		STATE toPopState = m_eStates.back();
		m_eStates.pop_back();
		return toPopState;
	}
	else
		return STATE_NIL;
}
CGameStateManager::STATE CGameStateManager::getCurrentState()
{
	if (!m_eStates.empty)
		return m_eStates.back();
	else
		return STATE_NIL;
}