#include "Card.h"
#include <string.h>

using namespace std;

//老师使用卡
class Teacher : public Card
{
    public:
        void add_money(int num,int n);
        bool use(int num);
};

//学生使用卡
class Student : public Card
{
    public:
        void add_money(int num,int n);
        bool use(int num);
};

//老师家属使用卡
class Family : public Card
{
    public:
        void add_money(int num,int n);
        bool use(int num);
};
