#include <string>
#include <iostream>

#include <stdlib.h>
#include <time.h>

using namespace std;

//定义一个班车类
class Bus
{
    private:
        string bus_type;  //班车型号
        string bus_num;// 班车车牌号
        string bus_driver_name; //班车司机
        int start_time; //班车开始时间
        int people_max; //车上可以载的最多人数
        int people_num;//目前车上有多少人


    public:
        void init(string driver,string number,int strat);//初始化函数，班车司机，车牌号，出发时间
        void count();//有人上车后统计上车人数
        bool isfull();//判断车内是否满人
        void display_bus_information();//展示车的基本信息
        void set_type_num();//用随机函数产生 车的类型 和 在车上的人数
};

//新建一个车
void Bus::init(string driver,string number,int start)
{
    bus_driver_name = driver;
    bus_num = number;
    start_time = start;
}

//统计车上人数
void Bus::count()
{
    if(people_max == people_num)
    {
        cout << "人数已满，请下车等待另一辆车" << endl;
    }
    else
    {
        people_num++;
        cout << "欢迎乘车，此时车上有" << people_num << "人" << endl;
   }
}
   


//输出车的基本信息
void Bus::display_bus_information()
{
    cout << "车牌号：" << bus_num << endl;
    cout << "型号：" << bus_type << endl;
    cout << "目前载乘人数" << people_num << endl;
	cout << "驾驶员姓名：" << bus_driver_name << endl;
}

//判断车是否满员
bool Bus::isfull()
{
    return people_max == people_num;
}


//用随机函数产生 车的类型 和 在车上的人数
void Bus::set_type_num()
{
    srand((int)time(0)); //生成随机种子
    int t = rand() % 2 ;//生成一个0或1的数字，表示大车和小车
    if(t == 0)
    {
        bus_type = "small bus";
        people_max = 30;
        people_num = rand() % 31;
    }
    else
    {
        bus_type = "big bus";
        people_max = 50;
        people_num = rand() % 51;
    }
}