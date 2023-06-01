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
        void UptateEXP(int _level, int _length);
        void UptateEXP(int _exp);
        int GetEXP() { return exp;}
    private:
        int exp;
    };
}

#endif // ANSWER_H
