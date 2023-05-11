#ifndef MAKER_H
#define MAKER_H
#include "player.h"


class Maker : public Player
{
public:
    Maker(QString);
    void LoadData();
    void UpdateData();
};

#endif // MAKER_H
