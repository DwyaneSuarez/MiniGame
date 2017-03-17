#ifndef CTANKENEMY_H
#define CTANKENEMY_H

#include <CommonClass.h>
#include "CTanksWorld.h"

class CTankEnemy : public CTanksWorld
{
    public:
        CTankEnemy(const char* );
        virtual ~CTankEnemy();

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
        void SetChangeDirTime(int fChangeDirTime) {m_fChangeDirTime = fChangeDirTime;}
        void SetType(int iType) {m_iType = iType;}
        void SetSpeedConstant(float fSpeedConstant) {m_fSpeedConstant = fSpeedConstant;}
        float GetChangeDirTime() {return m_fChangeDirTime;}
        int GetType() {return m_iType;}
        float GetSpeedConstant() {return m_fSpeedConstant;}

        void Init();
        void Move();
        void Move(float );
        //void Fire(float );
        void Fire();
        void OnSpriteColSprite(CTanksWorld* );
        void Bounce(int );
    protected:
    private:
        /*
        int m_iDir;
        int m_iHp;
        float m_fSpeedX;
        float m_fSpeedY;
        */
        float m_fChangeDirTime;
        float m_fCreateBulletTime;
        int m_iType;
        float m_fSpeedConstant;
        //float m_fFireFrequency;
};

#endif // CTANKENEMY_H
