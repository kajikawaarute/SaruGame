#include "stdafx.h"
#include "IGameObjectManager.h"
#include "BananaPeelManager.h"
#include "BananaPeel.h"


BananaPeelManager::BananaPeelManager()
{
}


BananaPeelManager::~BananaPeelManager()
{
}

BananaPeel* BananaPeelManager::NewBananaPeel()
{
	BananaPeel* newBananaPeel = new BananaPeel;
	m_bananaPeels.push_back(newBananaPeel);
	return newBananaPeel;
}

void BananaPeelManager::Update()
{
	for (auto&bananaPeel : m_bananaPeels) 
	{
		bananaPeel->Update();
	}
}

void BananaPeelManager::Draw()
{
	for (auto&bananaPeel : m_bananaPeels)
	{
		bananaPeel->Draw();
	}
}
