#include "answer.h"
using namespace my_answer;

Answer::Answer(QString _name) : Player(_name)
{
    playerType = PlayerType::Answer;
}
