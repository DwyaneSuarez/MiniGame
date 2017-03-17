#ifndef CTREASURE_H
#define CTREASURE_H

#include <CTanksWorld.h>

class CTreasure : public CTanksWorld
{
    public:
        CTreasure(const char* );
        virtual ~CTreasure();

        void SetType(int iType) {m_iType = iType;}
        int GetType() {return m_iType;}

        void CreateNewTreasure(int , float , float );
        void OnSpriteColSprite(CTanksWorld* );
    protected:
    private:
        int m_iType;
};

#endif // CTREASURE_H
