#include "CTankEnemy.h"
#include "CBullet.h"
#include "LessonX.h"
#include <cstdlib>
#include <ctime>
using namespace std;

CTankEnemy::CTankEnemy(const char* szName):CTanksWorld(szName)
{
    /*
    m_iDir = 0;
    m_iHp = 2;
    m_fSpeedX = 0.f;
    m_fSpeedY = 0.f;
    */
    //SetSpriteWorldLimit(WORLD_LIMIT_NULL, -26, -22, 26, 22);
    //SetSpriteCollisionActive(1, 1);
    m_fChangeDirTime = 0.f;
    m_fCreateBulletTime = 0.f;
    int iType = rand() % 10;
    if (iType == 9)
    {
        CTanksWorld::SetHp(8);
        SetType(2);
        SetSpeedConstant(8.f);
    }
    else if (iType == 8 || iType == 7)
    {
        CTanksWorld::SetHp(2);
        SetType(1);
        SetSpeedConstant(10.f);
    }
    else
    {
        CTanksWorld::SetHp(2);
        SetType(0);
        SetSpeedConstant(8.f);
    }
}

CTankEnemy::~CTankEnemy()
{
    //dtor
}

void CTankEnemy::Init()
{
    //int newPos = CSystem::RandomRange(0, 2);
    //newPos = 0;
    srand(unsigned(time(0)));
    int newPos = rand() % 3;
    //SetType(iType);
    SetDir(2);
    float posX;
    if (newPos == 0) posX = -24.f;
        else if (newPos == 1) posX = 0;
            else if (newPos == 2) posX = 24.f;
    SetSpritePosition(posX, -20.f);
    SetSpriteLinearVelocity(0.f, GetSpeedConstant());
    SetSpriteCollisionActive(1, 1);
    SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
    SetSpriteRotation(90 * GetDir());
    SetSpriteWorldLimit(WORLD_LIMIT_NULL, -26, -22, 26, 22);
}

void CTankEnemy::Move()
{
    //int newDir = (GetDir()+1)%4;
    //int newDir = CSystem::RandomRange(0, 3);
    //srand(unsigned(time(NULL)));
    int newDir = rand() % 4;
    SetDir(newDir);
    if (newDir % 2 == 0)
    {
        SetSpeedX(0);
        SetSpeedY(GetSpeedConstant() * (newDir - 1));
    }
    else
    {
        SetSpeedY(0);
        SetSpeedX(GetSpeedConstant() * (2 - newDir));
    }
    SetSpriteRotation(90*newDir);
    SetSpriteLinearVelocity(GetSpeedX(), GetSpeedY());
    Fire();
}

void CTankEnemy::Move(float deltaTime)
{
    m_fChangeDirTime += deltaTime;
    if (m_fChangeDirTime > 4.0f)
    {
        Move();
        m_fChangeDirTime = 0.f;
    }
}

void CTankEnemy::Fire()
{
    //m_fCreateBulletTime += deltaTime;
    //if (m_fCreateBulletTime > 3.0f)
    {
        m_fCreateBulletTime = 0.f;
        float posX,posY;
        posX = GetSpritePositionX();
        posY = GetSpritePositionY();
        int dir;
        dir = GetDir();
        if (dir == 0) posY = posY - GetSpriteHeight() / 2 - 1;
            else if (dir == 1) posX = posX + GetSpriteWidth() / 2 + 1;
                else if (dir == 2) posY = posY + GetSpriteHeight() / 2 + 1;
                    else if (dir == 3) posX = posX - GetSpriteWidth() / 2 - 1;
        g_GameMain.AddBullet(dir, posX, posY, 0);
    }
}

void CTankEnemy::OnSpriteColSprite(CTanksWorld* pSprite)
{
    //if (strstr(pSprite->GetName(), "enemy") != NULL) return;
    if (strstr(pSprite->GetName(), "treasure") != NULL) return;
    if (pSprite != NULL)
    {
        SetSpriteLinearVelocity(0.f, 0.f);
        if (strstr(pSprite->GetName(), "enemy") != NULL)
        {
            CTankEnemy* pTarget = (CTankEnemy*) pSprite;
            pTarget->SetChangeDirTime(3.8f);
            //pSprite->Bounce();
            //pTarget->Move(0.2f);
        }
        //if (strstr(pSprite->GetName(), "enemy") == NULL)
        m_fChangeDirTime = 3.8f;
        //CTanksWorld::Bounce();
    }
}

void CTankEnemy::Bounce(int iColSide)
{
    m_fChangeDirTime = 0.f;
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
    Fire();
}
