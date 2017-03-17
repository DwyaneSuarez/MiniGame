/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
#include <ctime>
#include "CTreasure.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{
	m_iGameState			=	0;
	m_iBulletNum            =   0;
	m_iEnemyTankNum         =   0;
	m_iLevel                =   0;
	m_fCreateEnemyTankTime  =   0.f;
	m_pSplash = new CSprite("splash");
    m_pStart = new CSprite("start");
    m_pGameOver = new CSprite("game");
    m_vTanksWorld.clear();
    m_pScore = new CTextSprite("score");
    m_pHighest = new CTextSprite("hight");
    m_pEnemyNum = new CTextSprite("enemyNum");
    m_pLife = new CTextSprite("life");
    m_iScore = 0;
    m_iHighest = 0;
    m_iEnemyNum = 0;
    m_fGameTime = 0.f;
    srand((unsigned)time(0));
    m_bFlag = false;
}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
    delete m_pSplash;
    delete m_pStart;
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{

		    if (m_iScore >= 50 && m_iLevel == 0)
            {
                DeleteAllSprite();
                //ClearMap();
                m_iLevel = 1;
                GameInit();
            }
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if(!m_pTankPlayer->IsDead() && !m_pAim_nor->IsDead())
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{
				//SetGameState(0);
				GameEnd();
				SetGameState(0);
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	    {
            break;
	    }

    case 3:
        {
            /*
            DisplayGameOver();
            SetGameState(0);
            break;
            */
        }
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
    m_bPause = false;
    m_pSplash->SetSpriteVisible(false);
    m_pStart->SetSpriteVisible(false);
    m_pGameOver->CloneSprite("gameo");
    SetGameState(2);
    m_pTankPlayer = new CTankPlayer("myplayer");
    m_pTankPlayer->CloneSprite("player");
    m_pTankPlayer->Init();
    m_pTankPlayer->SetSpriteCollisionActive(1, 1);
    m_pTankPlayer->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
    m_vTanksWorld.push_back(m_pTankPlayer);
    /*
    m_pTankEnemy = new CTankEnemy("enemy");
    m_pTankEnemy->Init();
    */
    LoadMap(m_iLevel);
    m_pAim_nor = new CTanksWorld("myaim_nor");
    m_pAim_nor->CloneSprite("aim_nor");
    m_vTanksWorld.push_back(m_pAim_nor);
    m_pAim_nor->SetSpriteCollisionReceive(true);
    m_pAim_nor->SetSpritePosition(0.f, 20.f);

    m_iBulletNum = 0;
	m_iEnemyNum = 0;
	m_fCreateEnemyTankTime = 2.f;
	m_iScore = 0;
	m_iHighest = 0;
	m_iEnemyTankNum = 0;
    m_fGameTime = 0.f;
    m_fPauseTime = 0.f;
    m_iTreasureNum = 0;

    FILE * fp =fopen("save.dat","r+");
    if(fp)
    {
        fread(&m_iHighest,sizeof(int),1,fp);
        fclose(fp);
    }
	m_pHighest = new CTextSprite("hight");
	m_pHighest->SetTextValue(m_iHighest);
	m_pLife->SetTextValue(m_pTankPlayer->GetLifeNum());
    //m_pExplosion = new CEffect("")
    /*
    m_pTrs = new CTreasure("bomb");
    m_pTrs->CloneSprite("zhadan");
    m_pTrs->SetSpritePosition(0.f, 0.f);
    m_pTrs->SetSpriteCollisionActive(1, 1);
    m_pTrs->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
    m_vTanksWorld.push_back(m_pTrs);
    */
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
    m_fGameTime += fDeltaTime;
    m_pScore->SetTextValue(m_iScore);
    m_pHighest->SetTextValue(m_iHighest);
    m_pEnemyNum->SetTextValue(m_iEnemyNum);
    m_pLife->SetTextValue(m_pTankPlayer->GetLifeNum());
    m_pTankPlayer->SetFireTime(m_pTankPlayer->GetFireTime() + fDeltaTime);
    if (m_bPause)
    {
        m_fPauseTime += fDeltaTime;
        if (m_fPauseTime > 5.0f)
        {
            m_fPauseTime = 0.f;
            m_bPause = false;
        }
    }
    else AddTankEnemy(fDeltaTime);
    for (auto it : m_vTanksWorld)
    {
        CTanksWorld* cur = it;
        if (cur->IsDead())
        {
            if (strstr(cur->GetName(), "enemy") != NULL || strstr(cur->GetName(), "player") != NULL)
            {
                CEffect* pBoom = new CEffect("baozha", "boom", 3.0f);
                pBoom->PlayEffect(cur->GetSpritePositionX(), cur->GetSpritePositionY(), cur->GetSpriteRotation());
                /*
                CTreasure* pBomb = new CTreasure("bomb");
                pBomb->CloneSprite("zhadan");
                pBomb->SetSpritePosition(0.f, 0.f);
                */
            }
            if (strstr(cur->GetName(), "enemy") != NULL)
            {
                CTankEnemy* pEnemy = (CTankEnemy*) cur;
                if (pEnemy->GetType() == 2)
                {
                    m_iTreasureNum++;
                    char* szName = CSystem::MakeSpriteName("treasure", m_iTreasureNum);
                    CTreasure* pTreasure = new CTreasure(szName);
                    int iType = rand() % 3;
                    //int iType = 0;
                    pTreasure->CreateNewTreasure(iType, cur->GetSpritePositionX(), cur->GetSpritePositionY());
                    pTreasure->SetSpriteCollisionActive(1, 1);
                    pTreasure->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
                    m_vTanksWorld.push_back(pTreasure);
                }
            }
            Delete(cur->GetName());
        }
        else
        {
            if (!m_bPause) cur->Move(fDeltaTime);
                else
                {
                    if (strstr(cur->GetName(), "enemy") != NULL)
                        cur->SetSpriteLinearVelocity(0.f, 0.f);
                }
            //cur->Fire(fDeltaTime);
        }
    }

    /*
    for (vector<CTanksWorld*>::iterator it = m_vTanksWorld.begin(); it != m_vTanksWorld.end(); it++)
    {
        CTanksWorld* cur = *it;
        const char* name = cur->GetName();
        if (cur->IsDead())
        {
            Delete(cur->GetName());
        }
        else
        {
            cur->Move();
            cur->Fire();
        }
    }
    */
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
    FILE * fp =fopen("save.dat","w+");
    if(m_iScore>m_iHighest) fwrite(&m_iScore,sizeof(int),1,fp);
    fclose(fp);
    DisplayGameOver();
    DeleteAllSprite();
    //m_pGameOver->SetSpriteVisible(false);
    /*
    m_pGameOver->SetSpritePosition(0.f, 0.f);
    m_pGameOver->SetSpriteVisible(true);
    for (int i=1;i<=1e9;i++);
    m_pGameOver->SetSpriteVisible(false);
    */

    /*
    m_pSplash->SetSpriteVisible(true);
    m_pStart->SetSpriteVisible(true);
    SetGameState(0);
    */
}

void CGameMain::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
    if (GetGameState() == 0)
    {
        if (!m_bFlag)
        {
            if (iKey == KEY_SPACE)
            {
                m_iGameState = 1;
            }
            m_bFlag = true;
        }
        else
        {
            m_pGameOver->SetSpriteVisible(false);
            m_pSplash->SetSpriteVisible(true);
            m_pStart->SetSpriteVisible(true);
            m_bFlag = false;
        }
    }
    if (GetGameState() == 2)
    {
        m_pTankPlayer->Move(iKey, true);
        if (iKey == KEY_SPACE)
        {
            //float deltaTime = CSystem::GetTimeDelta();
            m_pTankPlayer->Fire();
        }
        //if (m_bFlag)
    }
}

void CGameMain::OnKeyUp(const int iKey)
{
    if (GetGameState() == 2)
    {
        m_pTankPlayer->Move(iKey, false);
    }
}

void CGameMain::OnSpriteColWorldLimit(const char *szName, const int iColSide)
{
    if (strstr(szName, "player") != NULL)
    {
        m_pTankPlayer->SetSpriteLinearVelocity(0, 0);
    }
    else if (strstr(szName, "enemy") != NULL)
    {
        CTankEnemy* target = (CTankEnemy*) (Find(szName));
        //target->SetSpriteLinearVelocity(0.f, 0.f);
        //target->CTanksWorld::Bounce();
        //target->Move();
        target->Bounce(iColSide);
    }
    else if (strstr(szName, "bullet") != NULL)
    {
        CTanksWorld* target = Find(szName);
        target->SetHp(0);
    }
}

void CGameMain::AddBullet(int dir, float posX, float posY, int owner)
{
    //if (CSystem::GetTimeDelta() < 0.3f) return;
    char* szName = CSystem::MakeSpriteName("bullet", m_iBulletNum);
    CBullet* pBullet = new CBullet(szName);
    pBullet->CloneSprite("bullet");
    pBullet->SetSpritePosition(posX, posY);
    //pBullet->SetSpriteCollisionSend(true);
    //pBullet->SetSpriteCollisionReceive(true);
    pBullet->SetSpriteCollisionActive(1, 1);
    pBullet->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
    pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL, -26, -22, 26, 22);
    pBullet->OnMove(dir);
    m_iBulletNum++;
    pBullet->SetOwner(owner);
    m_vTanksWorld.push_back(pBullet);
}

void CGameMain::LoadMap(int ord)
{
    char* szName;
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 13; j++)
        {
            float posX,posY;
            posX = -24.f + 4 * j;
            posY = -20.f + 4 * i;
            if (g_iMap[ord][i][j] == 1)
            {
                szName = CSystem::MakeSpriteName("wall", i * 13 + j);
                CTanksWorld* pWall = new CTanksWorld(szName);
                pWall->CloneSprite("mu");
                pWall->SetSpriteCollisionActive(0, 1);
                pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
                pWall->SetSpritePosition(posX, posY);
                m_vTanksWorld.push_back(pWall);
            }
            else if (g_iMap[ord][i][j] == 2)
            {
                szName = CSystem::MakeSpriteName("steel", i * 13 + j);
                CTanksWorld* pSteel = new CTanksWorld(szName);
                pSteel->CloneSprite("tie");
                pSteel->SetSpriteCollisionActive(0, 1);
                pSteel->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
                pSteel->SetSpritePosition(posX, posY);
                pSteel->SetHp(10000000);
                m_vTanksWorld.push_back(pSteel);
            }
            else if (g_iMap[ord][i][j] == 3)
            {
                szName = CSystem::MakeSpriteName("grass", i * 13 + j);
                CTanksWorld* pGrass = new CTanksWorld(szName);
                pGrass->CloneSprite("shu");
                pGrass->SetSpriteCollisionActive(0, 0);
                pGrass->SetSpritePosition(posX, posY);
                m_vTanksWorld.push_back(pGrass);
            }
            else if (g_iMap[ord][i][j] == 4)
            {
                szName = CSystem::MakeSpriteName("sea", i * 13 + j);
                CTanksWorld* pSea = new CTanksWorld(szName);
                pSea->CloneSprite("hai");
                pSea->SetSpriteCollisionActive(0, 1);
                pSea->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
                pSea->SetSpritePosition(posX, posY);
                m_vTanksWorld.push_back(pSea);
            }
        }
}

void CGameMain::AddTankEnemy(float deltaTime)
{
    m_fCreateEnemyTankTime += deltaTime;
    if (m_fCreateEnemyTankTime > 3.0f)
    {
        char* szName = CSystem::MakeSpriteName("enemy", m_iEnemyTankNum);
        CTankEnemy* pTankEnemy = new CTankEnemy(szName);
        int iType = pTankEnemy->GetType();
        if (iType == 0) pTankEnemy->CloneSprite("putong");
            else if (iType == 1) pTankEnemy->CloneSprite("zhuangjia");
                else if (iType == 2) pTankEnemy->CloneSprite("armor");
        pTankEnemy->Init();

        pTankEnemy->SetSpriteCollisionActive(1, 1);
        pTankEnemy->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
        m_iEnemyTankNum++;
        //m_pTankEnemySet.insert(pTankEnemy);
        m_vTanksWorld.push_back(pTankEnemy);
        m_fCreateEnemyTankTime = 0.f;
        m_iEnemyNum++;
    }
}

CTanksWorld* CGameMain::Find(const char* szName)
{
    for (auto it : m_vTanksWorld)
    {
        CTanksWorld* cur = it;
        if (strcmp(cur->GetName(), szName) == 0) return cur;
    }
}

void CGameMain::Delete(const char* szName)
{
    //����ײ�綨�÷ֲ�����Ӧ����ɾ������ʱ����÷�
    if (strstr(szName, "enemy") != NULL)
    {
        CTankEnemy* pTarget = (CTankEnemy*) Find(szName);
        int iType = pTarget->GetType();
        if (iType == 0) m_iScore += 1;
            else if (iType == 1) m_iScore += 2;
                else if (iType == 2) m_iScore += 4;
        m_iEnemyNum--;
    }
    for (vector<CTanksWorld*>::iterator it = m_vTanksWorld.begin(); it != m_vTanksWorld.end(); it++)
    {
        CTanksWorld* cur = *it;
        if (strcmp(cur->GetName(), szName) == 0)
        {
            m_vTanksWorld.erase(it);
            cur->DeleteSprite();
            delete cur;
            break;
        }
    }
}

void CGameMain::OnSpriteColSprite(const char *szSrcName, const char *szTarName)
{
    CTanksWorld* tarSprite = Find(szTarName);
    /*
    if (strstr(szSrcName, "bomb") != NULL)
    {
        CTreasure* pTreasure = (CTreasure*) Find(szSrcName);
        pTreasure->OnSpriteColSprite(tarSprite);
    }
    */
    if (strstr(szSrcName, "bullet") != NULL)
    {
        CBullet* pBullet = (CBullet*) Find(szSrcName);
        pBullet->OnSpriteColSprite(tarSprite);
        /*
        if (pBullet->GetOwner() == 1 && strstr(szTarName, "enemy") != NULL)
        {
            m_iScore++;
            m_iEnemyNum--;
        }
        */  //�����趨��ĳЩʱ������bug
    }
    else if  (strstr(szSrcName, "enemy") != NULL)
    {
        CTankEnemy* pTankEnemy = (CTankEnemy*) Find(szSrcName);
        pTankEnemy->OnSpriteColSprite(tarSprite);
    }
    else if (strstr(szSrcName, "player") != NULL)
    {
        m_pTankPlayer->OnSpriteColSprite(tarSprite);
    }
    else if (strstr(szSrcName, "bomb") != NULL)
    {
        CTreasure* pTreasure = (CTreasure*) Find(szSrcName);
        pTreasure->OnSpriteColSprite(tarSprite);
    }
}

void CGameMain::DeleteAllSprite()
{
    /*
    m_pGameOver->SetSpritePosition(0.f, 0.f);
    m_pGameOver->SetSpriteVisible(true);
    for (int i=1;i<=1e9;i++);
    */
    while (m_vTanksWorld.size() > 0)
    {
        vector<CTanksWorld*>::iterator it = m_vTanksWorld.begin();
        CTanksWorld* cur = *it;
        m_vTanksWorld.erase(it);
        cur->DeleteSprite();
        delete cur;
    }
    //m_pGameOver = new CSprite("gameover");
    /*
    m_pGameOver->SetSpritePosition(0.f, 0.f);
    m_pGameOver->SetSpriteVisible(true);
    for (int i=1;i<=1e9;i++);
    */
}

void CGameMain::DisplayGameOver()
{
    /*
    m_pGameOver->CloneSprite("gameover");
    m_pGameOver->SetSpritePosition(0.f, 1.2f);
    m_pGameOver->SetSpriteVisible(true);
    //for (int i=1;i<=1e9;i++);
    //delete m_pGameOver;
    Sleep(3000);
    m_pGameOver->SetSpriteVisible(false);
    */
    m_pGameOver->SpriteMoveTo(0.f, 0.f, 20.f, true);
   //m_pGameOver->SetSpriteVisible(true);
    //Sleep(3000);
    //m_pGameOver->SetSpriteVisible(false);
}

void CGameMain::BombAllTankEnemy()
{
    for (auto it : m_vTanksWorld)
    {
        CTanksWorld* cur = it;
        if (strstr(cur->GetName(), "enemy") != NULL)
        {
            cur->SetHp(0);
        }
    }
}
/*
void CGameMain::ClearMap()
{

}
*/
