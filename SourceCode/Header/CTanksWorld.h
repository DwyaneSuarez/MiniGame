#ifndef CTANKSWORLD_H
#define CTANKSWORLD_H

#include <CommonClass.h>

class CTanksWorld : public CSprite
{
    public:
        CTanksWorld(const char* );
        virtual ~CTanksWorld();

        int GetHp() {return m_iHp;}
        int GetDir() {return m_iDir;}
        float GetSpeedX() {return m_fSpeedX;}
        float GetSpeedY() {return m_fSpeedY;}

        void SetHp(int hp) {m_iHp = hp;}
        void SetDir(int dir) {m_iDir = dir;}
        void SetSpeedX(float speedX) {m_fSpeedX = speedX;}
        void SetSpeedY(float speedY) {m_fSpeedY = speedY;}

        bool IsDead();
        void Bounce();
        void Bounce(int );
        virtual void Init(){};
        virtual void Move(float ){};
        virtual void Move(){};
        virtual void Fire(float ){};
        virtual void OnSpriteColSprite(CTanksWorld* ){};
    protected:
    private:
        int m_iHp;
        int m_iDir;
        float m_fSpeedX;
        float m_fSpeedY;
};

#endif // CTANKSWORLD_H
