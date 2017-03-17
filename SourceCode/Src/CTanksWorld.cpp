#include "CTanksWorld.h"
#include "LessonX.h"

CTanksWorld::CTanksWorld(const char* szName):CSprite(szName)
{
    m_iDir = 0;
    m_iHp = 2;
    m_fSpeedX = 0.f;
    m_fSpeedY = 0.f;
}

CTanksWorld::~CTanksWorld()
{
    //dtor
}

bool CTanksWorld::IsDead()
{
    if (strstr(this->GetName(), "player") != NULL)
    {
        CTankPlayer* pPlayer = (CTankPlayer*) this;
        int iLifeNum = pPlayer->GetLifeNum();
        return iLifeNum <= 0;
    }
    else return m_iHp <= 0;
}

void CTanksWorld::Bounce()
{
    int oldDir = GetDir();
    int newDir;
    /*
    if (iColSide == 0) newDir = 1;
        else if (iColSide == 1) newDir = 3;
            else if (iColSide == 2) newDir = 2;
                else if (iColSide == 3) newDir = 0;
    */
    if (oldDir % 2 == 0) newDir = 2 - oldDir;
        else newDir = 4 - oldDir;
    if (newDir % 2 == 0)
    {
        SetSpeedX(0);
        SetSpeedY(8 * (newDir - 1));
    }
    else
    {
        SetSpeedY(0);
        SetSpeedX(8 * (2 - newDir));
    }
    SetSpriteRotation(90*newDir);
    SetSpriteLinearVelocity(GetSpeedX(), GetSpeedY());
}

void CTanksWorld::Bounce(int iColSide)
{
    int newDir;
    if (iColSide == 0) newDir = 1;
        else if (iColSide == 1) newDir = 3;
            else if (iColSide == 2) newDir = 2;
                else if (iColSide == 3) newDir = 0;
    if (newDir % 2 == 0)
    {
        SetSpeedX(0);
        SetSpeedY(8 * (newDir - 1));
    }
    else
    {
        SetSpeedY(0);
        SetSpeedX(8 * (2 - newDir));
    }
    SetSpriteRotation(90*newDir);
    SetSpriteLinearVelocity(GetSpeedX(), GetSpeedY());
}
