#ifndef ANSWER_H
#define ANSWER_H
#include "player.h"

namespace my_answer {
    class Answer : public Player
    {
    public:
        Answer(QString);
        void UpdateData();
        void LoadData();
        int GetEXP() { return exp;}
    private:
        int exp;
    };
}

#endif // ANSWER_H