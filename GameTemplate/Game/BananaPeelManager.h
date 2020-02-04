#pragma once
#include "IGameObject.h"

class BananaPeel;
class BananaPeelManager : public IGameObject
{
public:
	BananaPeelManager();
	~BananaPeelManager();
	BananaPeel* NewBananaPeel();
	void Update();
	void Draw();

private:
	std::vector<BananaPeel*> m_bananaPeels; //�o�i�i�̔�̉ϒ��z��B
};

