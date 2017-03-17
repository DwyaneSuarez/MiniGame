#ifndef CBULLET_H
#define CBULLET_H

#include <CommonClass.h>
#include "CTanksWorld.h"

class CBullet : public CTanksWorld
{
    public:
        CBullet(const char* );
        virtual ~CBullet();

        /*
        int GetDir() {return m_iDir;}
        int GetHp() {return m_iHp;}
        float GetSpeedX() {return m_fSpeedX;}
        float GetSpeedY() {return m_fSpeedY;}
        */
        int GetOwner() {return m_iOwner;}

        /*
        void SetDir(int dir) {m_iDir = dir;}
        void SetHp(int hp) {m_iHp = hp;}
        void SetSpeedX(float speedX) {m_fSpeedX = speedX;}
        void SetSpeedY(float speedY) {m_fSpeedY = speedY;}
        */
        void SetOwner(int owner) {m_iOwner = owner;}

        void OnMove(int );
        void OnSpriteColSprite(CTanksWorld* );
    protected:
    private:
        /*
        int m_iDir;
        int m_iHp;
        float m_fSpeedX;
        float m_fSpeedY;
        */
        int m_iOwner;
};

#endif // CBULLET_H
