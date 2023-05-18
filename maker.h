#ifndef MAKER_H
#define MAKER_H
#include "player.h"

namespace my_maker
{
    class Maker : public Player
    {
    public:
        Maker(QString);
        void LoadData();
        void UpdateData();
        void UpdateEXP(int _length);
    };
}

#endif // MAKER_H
