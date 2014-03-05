#include "MainLogic.h"

MainLogic* MainLogic::s_pLogic = NULL;

MainLogic::MainLogic()
{

}

MainLogic::~MainLogic()
{

}

bool MainLogic::Init()
{
	m_kRule.Init(&m_kPlayerMan);
	m_kDealer.Init(&m_kRule, &m_kPlayerMan);
	m_kPlayerMan.Init(&m_kRule, &m_kDealer);

    return true;
}


MainLogic* MainLogic::GetInstance()
{
    if(!s_pLogic)
    {
        s_pLogic = new MainLogic;
        if(!s_pLogic || !s_pLogic->Init())
            CC_SAFE_DELETE(s_pLogic);
    }

    return s_pLogic;
}

void MainLogic::FreeInstance()
{
    CC_SAFE_DELETE(s_pLogic);
}

void MainLogic::update(float delta)
{
	m_kRule.Update(delta);
	m_kDealer.Update(delta);
	m_kPlayerMan.Update(delta);
}


void MainLogic::GetPlayerInfo(PokerPlayerInfo playerInfos[])
{
	m_kPlayerMan.GetPlayerInfo(playerInfos);
}

void MainLogic::GetPlayerJokboInfo(JokboResult jokboInfos[])
{
	m_kPlayerMan.GetPlayerJokbo(jokboInfos);
}

void MainLogic::GetDealerInfo(TableInfo& tableInfo)
{
	m_kDealer.GetTableInfo(tableInfo);
}

PokerSequence MainLogic::GetSequence()
{
	return m_kRule.GetCurPokerSequence();
}