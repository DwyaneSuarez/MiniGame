/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include <set>
#include <vector>
#include "CTankPlayer.h"
#include "CBullet.h"
#include "CTankEnemy.h"
#include "CTanksWorld.h"
#include "CTreasure.h"
using namespace std;

/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������
	int             m_iBulletNum;
	int             m_iEnemyTankNum;
	int             m_iTreasureNum;
	int             m_iLevel;
	float           m_fCreateEnemyTankTime;
	float           m_fPauseTime;
	CSprite*        m_pSplash;
	CSprite*        m_pStart;
	CSprite*        m_pGameOver;
	CTankPlayer*    m_pTankPlayer;
	CTreasure*      m_pTrs;
	//CTankEnemy*     m_pTankEnemy;
	//std::set<CTankEnemy*> m_pTankEnemySet;
	vector<CTanksWorld*> m_vTanksWorld;
	CTanksWorld*    m_pAim_nor;
	CTextSprite*    m_pScore;
	CTextSprite*    m_pHighest;
	CTextSprite*    m_pEnemyNum;
	CTextSprite*    m_pLife;
	int             m_iScore;
	int             m_iEnemyNum;
	int             m_iHighest;
	float           m_fGameTime;
	bool            m_bFlag;
	bool            m_bPause;

	int g_iMap[2][11][13]=
    {
        {
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,3,0,3,0,0,0,1,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,1,0,4,0,4,0,1,0,0,0},
        {0,0,0,1,0,0,0,0,0,1,0,0,0},
        {0,0,0,1,0,1,0,1,0,1,0,0,0},
        {1,1,1,1,1,1,2,1,1,1,1,1,1},
        {0,1,0,1,0,0,0,0,0,1,0,1,0},
        {0,0,0,0,0,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,1,0,1,0,0,0,0,0}
        },
        {
        {0,0,0,2,0,0,0,2,0,0,0,0,0},
        {0,1,0,2,0,0,0,1,0,1,0,1,0},
        {0,1,0,0,0,0,1,1,0,1,2,1,0},
        {0,0,0,1,0,0,0,0,0,2,0,0,0},
        {3,0,0,1,0,0,2,0,0,1,3,1,2},
        {3,3,0,0,0,1,0,0,2,0,3,0,0},
        {0,1,1,1,3,3,3,2,0,0,3,1,0},
        {0,0,0,2,3,1,0,1,0,1,0,1,0},
        {2,1,0,2,0,1,0,1,0,0,0,1,0},
        {0,1,0,0,0,1,1,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,1,1,0},
        }
    };



public:
	CGameMain();            //���캯��
	~CGameMain();           //��������

	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	void            OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
	void            OnKeyUp(const int );
	void            OnSpriteColWorldLimit(const char* , const int );
	void            AddBullet(int, float, float, int );
	void            LoadMap(int );
	void            AddTankEnemy(float );
	CTanksWorld*    Find(const char* );
	void            Delete(const char* );
	void            OnSpriteColSprite(const char* , const char* );
	void            DeleteAllSprite();
	void            DisplayGameOver();
	void            BombAllTankEnemy();
	void            DisplayLifeNum() {m_pLife->SetTextValue(m_pTankPlayer->GetLifeNum());}
	void            SetPause(bool bPause) {m_bPause = bPause;}
	bool            GetPause() {return m_bPause;}
	void            ClearMap();
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
