#include "CTreasure.h"
#include "LessonX.h"

CTreasure::CTreasure(const char* szName):CTanksWorld(szName)
{

}

CTreasure::~CTreasure()
{
    //dtor
}

void CTreasure::CreateNewTreasure(int iType, float posX, float posY)
{
    SetType(iType);
    if (iType == 0) this->CloneSprite("zhadan");
        else if (iType == 1) this->CloneSprite("upgrade");
            else if (iType == 2) this->CloneSprite("zanting");
    SetSpritePosition(posX, posY);
}

void CTreasure::OnSpriteColSprite(CTanksWorld* pSprite)
{
    if (strstr(pSprite->GetName(), "enemy") != NULL) return;
    if (strstr(pSprite->GetName(), "player") != NULL)
    {
        if (m_iType == 0) g_GameMain.BombAllTankEnemy();
        else if (m_iType == 1)
        {
            CTankPlayer* pTarget = (CTankPlayer*) pSprite;
            pTarget->Upgrade();
        }
        else if (m_iType == 2)
        {
            g_GameMain.SetPause(true);
        }
        //    else if (iType == 1)
        SetHp(0);
    }
}
