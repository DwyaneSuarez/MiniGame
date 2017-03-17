#include "CTankPlayer.h"
#include "LessonX.h"
#include "CTreasure.h"

CTankPlayer::CTankPlayer(const char* szName):CTanksWorld(szName)
{
    /*
    m_iDir = 0;
    m_iHp = 2;
    m_fSpeedX = 0.f;
    m_fSpeedY = 0.f;
    */
    m_fFireTime = 0.f;
    //m_fFireFrequency = 0.5f;
    SetHp(6);
   // m_iLifeNum = 3;
}

CTankPlayer::~CTankPlayer()
{
    //dtor
}

void CTankPlayer::Init()
{
    m_fFireFrequency = 0.5f;
    SetSpritePosition(-8.f, 20.f);
    SetSpriteRotation(0);
    SetSpriteWorldLimit(WORLD_LIMIT_NULL, -26, -22, 26, 22);
    SetSpriteCollisionActive(1, 1);
    SetSpriteVisible(true);
}

void CTankPlayer::Move(int iKey, bool bPress)
{
    if (bPress)
    {
        if (iKey == KEY_UP)
        {
            SetDir(0);
            SetSpeedX(0);
            SetSpeedY(-8);
        }
        else if (iKey == KEY_RIGHT)
        {
            SetDir(1);
            SetSpeedX(8);
            SetSpeedY(0);
        }
        else if (iKey == KEY_DOWN)
        {
            SetDir(2);
            SetSpeedX(0);
            SetSpeedY(8);
        }
        else if (iKey == KEY_LEFT)
        {
            SetDir(3);
            SetSpeedX(-8);
            SetSpeedY(0);
        }
        SetSpriteRotation(90*GetDir());
        SetSpriteLinearVelocity(GetSpeedX(), GetSpeedY());
    }
    else
    {
        if (iKey == KEY_UP || iKey == KEY_DOWN || iKey == KEY_LEFT || iKey == KEY_RIGHT)
        {
            SetSpeedX(0);
            SetSpeedY(0);
            SetSpriteLinearVelocity(GetSpeedX(), GetSpeedY());
        }
    }
}

void CTankPlayer::Fire()
{
    //double fDeltaTime = CSystem::GetTimeDelta();
    if (m_fFireTime >= m_fFireFrequency)
    {
        m_fFireTime = 0.f;
        float posX,posY;
        posX = GetSpritePositionX();
        posY = GetSpritePositionY();
        int dir;
        dir = GetDir();
        if (dir == 0) posY = posY - GetSpriteHeight() / 2 - 2;
            else if (dir == 1) posX = posX + GetSpriteWidth() / 2 + 1;
                else if (dir == 2) posY = posY + GetSpriteHeight() / 2 + 1;
                    else if (dir == 3) posX = posX - GetSpriteWidth() / 2 - 1;
        g_GameMain.AddBullet(dir, posX, posY, 1);
    }
}

void CTankPlayer::OnSpriteColSprite(CTanksWorld* pSprite)
{
    if (pSprite != NULL)
    {
        if (strstr(pSprite->GetName(), "bullet") != NULL)
        {
            //SetLifeNum(m_iLifeNum - 1);
            //g_GameMain.DisplayLifeNum();
            //Init();
            pSprite->SetHp(0);
            SetHp(GetHp() - 2);
            Init();
        }
        else if (strstr(pSprite->GetName(), "wall") != NULL)
        {
            SetSpeedX(0);
            SetSpeedY(0);
            SetSpriteLinearVelocity(0, 0);
        }
        else if (strstr(pSprite->GetName(), "steel") != NULL)
        {
            SetSpeedX(0);
            SetSpeedY(0);
            SetSpriteLinearVelocity(0, 0);
        }
        else if (strstr(pSprite->GetName(), "sea") != NULL)
        {
            SetSpeedX(0);
            SetSpeedY(0);
            SetSpriteLinearVelocity(0, 0);
        }
        else if (strstr(pSprite->GetName(), "enemy") != NULL)
        {
            SetSpeedX(0);
            SetSpeedY(0);
            SetSpriteLinearVelocity(0, 0);
        }
        else if (strstr(pSprite->GetName(), "treasure") != NULL)
        {
            CTreasure* pTreasure = (CTreasure*) pSprite;
            if (pTreasure->GetType() == 0)
            {
                g_GameMain.BombAllTankEnemy();
            }
            else if (pTreasure->GetType() == 1)
            {
                Upgrade();
            }
            else if (pTreasure->GetType() == 2)
            {
                g_GameMain.SetPause(true);
            }
            pSprite->SetHp(0);
        }
    }
}

void CTankPlayer::Upgrade()
{
    m_fFireFrequency = 0.25f;
}
