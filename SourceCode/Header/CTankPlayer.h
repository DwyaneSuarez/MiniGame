#ifndef CTANKPLAYER_H
#define CTANKPLAYER_H

#include <CommonClass.h>
#include "CTanksWorld.h"

class CTankPlayer : public CTanksWorld
{
    public:
        CTankPlayer(const char* );
        virtual ~CTankPlayer();

        /*
        int GetHp() {return m_iHp;}
        int GetDir() {return m_iDir;}
        float GetSpeedX() {return m_fSpeedX;}
        float GetSpeedY() {return m_fSpeedY;}

        void SetHp(int hp) {m_iHp = hp;}
        void SetDir(int dir) {m_iDir = dir;}
        void SetSpeedX(float speedX) {m_fSpeedX = speedX;}
        void SetSpeedY(float speedY) {m_fSpeedY = speedY;}
        */
        void SetFireTime(float fFireTime) {m_fFireTime = fFireTime;}
        //void SetLifeNum(int iLifeNum) {m_iLifeNum = iLifeNum;}
        float GetFireTime() {return m_fFireTime;}
        int GetLifeNum() {return GetHp() / 2;}

        void Init();
        void Move(int , bool );
        void Fire();
        void OnSpriteColSprite(CTanksWorld* );
        void Upgrade();
    protected:
    private:
        /*
        int m_iDir;
        int m_iHp;
        float m_fSpeedX;
        float m_fSpeedY;
        */
        float m_fFireFrequency;
        float m_fFireTime;
        int m_iLifeNum;
};

#endif // CTANKPLAYER_H
