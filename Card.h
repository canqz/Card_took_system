#include <iostream>
#include <string.h>

using namespace std;

class Card
{
    protected:
        string name;//姓名
        string id;//身份
        int card_num;//卡号
        int money;//金额
        int times;//使用次数
        string college; //所属学院

    public:
        //开卡   姓名，身份，学院，卡号，金额， 次数
        void init(string people_name,int num, int cardnum ,string people_college,int people_money, int people_times);
        //注销卡 
        void del(int num);
        //显示持有着信息
        void display_information(int num);
        //显示卡余额
        void display_money(int num);
        //显示使用次数
        void display_times(int num);
        //余额是否用完
        bool money_out();
        //保存信息到文件
        void save_to_file();
    
};