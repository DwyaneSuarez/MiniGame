#include "CBullet.h"
#include "CTankPlayer.h"

CBullet::CBullet(const char* szName):CTanksWorld(szName)
{
    m_iOwner = 0;
}

CBullet::~CBullet()
{
    //dtor
}

void CBullet::OnMove(int dir)
{
    SetDir(dir);
    if (dir == 0)
    {
        SetSpeedX(0);
        SetSpeedY(-12);
    }
    else if (dir == 1)
    {
        SetSpeedX(12);
        SetSpeedY(0);
    }
    else if (dir == 2)
    {
        SetSpeedX(0);
        SetSpeedY(12);
    }
    else if (dir == 3)
    {
        SetSpeedX(-12);
        SetSpeedY(0);
    }
    SetSpriteRotation(90*GetDir());
    SetSpriteLinearVelocity(GetSpeedX(), GetSpeedY());
}

void CBullet::OnSpriteColSprite(CTanksWorld* pSprite)
{
    if (pSprite == NULL) return;
    if (strstr(pSprite->GetName(), "treasure") != 0) return;
    if (GetOwner() == 1 && strstr(pSprite->GetName(), "bullet") != NULL)
    {
        CBullet* pBullet = (CBullet*) pSprite;
        if (pBullet->GetOwner() == 1) return;
        if (pBullet->GetOwner() == 0)
        {
            SetHp(0);
            pSprite->SetHp(0);
            return;
        }
    }
    if (strstr(pSprite->GetName(), "sea") != NULL) return;
    SetHp(0);
    if (GetOwner() == 1 && strstr(pSprite->GetName(), "aim_nor") != NULL) return;
    if (GetOwner() == 0 && strstr(pSprite->GetName(), "enemy") != NULL) return;
    int curHp = pSprite->GetHp();
    pSprite->SetHp(curHp - 2);
    if (strstr(pSprite->GetName(), "player") != NULL)
    {
        CTankPlayer* pTarget = (CTankPlayer*) pSprite;
        pTarget->Init();
    }
}
