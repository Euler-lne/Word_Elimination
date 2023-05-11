#ifndef ANSWER_H
#define ANSWER_H
#include "player.h"

class Answer : public Player
{
public:
    Answer(QString);
private:
    int exp;
};

#endif // ANSWER_H
