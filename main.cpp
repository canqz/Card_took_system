#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>



using namespace std;

#define MAX 1000

ofstream file_out1;
ifstream bus_file;
ifstream person_file;

class Card
{
    protected:
        string name;//姓名
        string id;//身份
        int card_num;//卡号
        int money;//金额
        int times;//使用次数
        string college; //所属学院
        int id_num;

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




//新建一个卡
void Card::init(string people_name,int num, int cardnum,string people_college,int people_money = 0, int people_times = 0)
{
    name = people_name;
    card_num = cardnum;
    college = people_college;//学院
    //辨别身份
    if(num == 1)
    {
        id_num = 1;
        id = "Teacher Card";
    }else if(num == 2)
    {
        id_num = 2;
        id = "Student Card";
    }else if (num == 3)
    {
        id_num = 3;
        id = "Family Card";
    }
    else
    {
        cout << "输入身份错误" << endl; 
    }
    money = people_money;
    times = people_times;
    
}


//注销卡
void Card::del(int num)//卡号匹配
{
    if(card_num == num)
    {
        name = "0";
        card_num = 0;
        money = 0;
        times = 0;
    }
    else
    {
        cout << "输入的卡号有错" << endl;
        return ;
    } 
}

// 显示余额
void Card::display_money(int num)
{
    if(card_num == num)
    {
        cout << "余额为：" << money << endl;
        if(money <= 5)
        {
            cout << "余额少于5元，请及时充值" << endl;

        }
    }
    else
    {
        cout << "输入卡号错误" << endl;
    }
    
}

//显示使用次数
void Card::display_times(int num)
{
    if(card_num == num)
    {
        cout << "本月使用次数为：" << times << endl;
    }
    else
    {
        cout << "输入卡号错误" << endl;
    }
}

//显示持卡人信息
void Card::display_information(int num)
{
    if (card_num == num)
    {
        cout << "姓名" << name << endl;
        cout << "身份" << id << endl;
        cout << "卡号" << card_num << endl;
        cout << "学院" << college <<endl;
    }
    else
    {
        cout << "输入卡号有错" << endl;
    }
    
}

//检查卡内余额是否用完
bool Card::money_out()
{
    if(money < 2)
    {
        display_information(card_num);
        cout << "卡内余额不足两元，请下车" << endl;
        return false;
    }
    else
    {
        return true;
    }
    
}

//将持卡人信息存入person.txt文件
void Card::save_to_file()
{
    if(name != "0")
    {
        file_out1.open("perpon.txt",ios::app);
        file_out1 << name << " " << id << " " << card_num << " "<< college << " " << money << " " << times << endl;
    }
}


//持卡人的操作

void Teacher::add_money(int num,int n)
{

    if (num == card_num){
		cout << "教师卡不能充值！\n";
	}
    else
    {
        cout << "输入卡号有错" << endl;
    }
}

void Student::add_money(int num,int n)
{
	if (num == card_num){
		if (n > 0)
        {
            money += n;
            cout << "恭喜你已经充值成功\n";
        }
	}
    else
    {
        cout << "输入卡号有错" << endl;
    }
    
}

void Family::add_money(int num,int n)
{
	if (num == card_num){
		if (n > 0)
        {
            money += n;
            cout << "恭喜你已经充值成功\n";
        }

	}
    else
    {
        cout << "输入卡号有错" << endl;
    }
}


bool Teacher::use(int num)
{
	if (num == card_num){
		times++;
		display_information(card_num);
		cout << "免费乘车" << endl;
        return true;
	}
    else
    {
        return false;
    }
    
}

//有待完善
bool Student::use(int num)
{
	if (num == card_num){
		if (money_out() == 0)
			return false;
		times++;
		money -= 2;
		display_information(card_num);
		display_money(card_num);
        return true;
	}
    else
    {
        return false;
    }
    
}


bool Family::use(int num)
{

	if (num == card_num){
		if (times < 19){
            cout << "本次乘车免费" << endl;
			times++;
			display_information(card_num);
			display_times(card_num);
            display_money(card_num);
            return true;
		}
		if (times == 19){
			times++;
			display_information(card_num);
			display_times(card_num);
            display_money(card_num);
			cout << "本月最后一次免费乘车" << endl;
            return true;
		}
		if (times == 20){
            if (money_out() == 0)
			    return false;
			times++;
			display_information(card_num);
			cout << "本次开始收费\n";
			money -= 2;
			display_money(card_num);
			cout << endl;
			return true;
		}
		if (times > 20){
            if (money_out() == 0)
			    return false;
			times++;
			money -= 2;
			display_information(card_num);
			display_money(card_num);
			cout << endl;
			return true;
		}
        return true;
	}
    else
    {
        return false;
    }
    
}



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
        void init(string driver,string number,double strat);//初始化函数，班车司机，车牌号，出发时间
        void count();//有人上车后统计上车人数
        bool isfull();//判断车内是否满人
        void display_bus_information();//展示车的基本信息
        void set_type_num();//用随机函数产生 车的类型 和 在车上的人数
};

//新建一个车
void Bus::init(string driver,string number,double start)
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
    int t = rand() % 2 ;//生成一个0或1 的数字，表示大车和小车
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


int main()
{
    Teacher T[MAX];
    Student S[MAX];
    Family  F[MAX];
    Bus     B[20];

    int x,y;//选择业务
    
    //人员变量
    string name;//姓名
    int id,money;//身份，卡内余额
    int num;//卡号
    string college;//学院
    int a = 0,b = 0,c = 0;//分别为teacher，student，family的已有注册人数
    

    //班车变量
    string driver_name;
    string bus_number;
    double start_time;
    double current_time;
    int bus_index = 0;

    //上车过程的变量
    int go_card_number;



    cout << "           欢迎使用一卡通乘车系统" << endl;
	cout << "输入1 进行一卡通业务办理，输入2 开始乘车, 输入0退出 " << endl;
    while (cin >> x && x != 0)
    {
        //一卡通业务办理
        if(x == 1)
        {
            cout << "输入1注册一张新卡，输入2为卡充值，输入3查询卡内余额，输入4查询本月已使用次数，输入5注销卡，输入0退出\n";
            while(cin >> y && y != 0)
            {
                if(y == 1)
                {
                    cout << "办理新卡：\n依次输入姓名,需要注册的卡种类（教师卡为1，学生卡为2，家属卡为3）,卡号,学院\n";
                    cout << "输入“0 0 0 0”退出注册卡中心\n";

                    while (cin >> name >> id >> num >> college && name != "0")
                    {
                        if(id == 1)
                        {
                            T[a].init(name,id,num,college);
                            T[a].save_to_file();
                            a++;
                        }
                        else if(id == 2)
                        {
                            S[b].init(name,id,num,college);
                            S[b].save_to_file();
                            b++;
                        }
                        else if(id == 3)
                        {
                            F[c].init(name,id,num,college);
                            F[c].save_to_file();
                            c++;
                            
                        }
                        cout << "恭喜你注册了一张新卡，如果还需办理新卡：\n依次输入姓名、需要注册的卡种类（教师卡为1，学生卡为2，家属卡为3）、卡号\n";
                        cout << "输入“0 0 0 0”退出注册卡中心\n";
                        //需要保存持卡人信息
                    }
                    
                }

                if(y == 2)
                {
                    cout << "输入卡号及充值金额：";
                    cin >> id >> money;
                    if (id >= 10000 && id < 20000)
                        cout << "教师卡不能充值！\n";
                    if (id >= 20000 && id < 30000){
                        for (int i = 0; i < b; i++)
                            S[i].add_money(id, money);
                        }
                    if (id >= 30000 && id < 40000){
                        for (int i = 0; i < c; i++)
                            F[i].add_money(id, money);
                    }
                }
                if (y == 3)
                {
                    cout << "输入卡号:";
                    cin >> id;
                    if (id >= 10000 && id < 20000){
                        cout << "教师卡免费乘坐！\n";
                    }
                    if (id >= 20000 && id < 30000){
                        for (int i = 0; i < b; i++)
                            S[i].display_money(id);
                    }
                    if (id >= 30000 && id < 40000){
                        for (int i = 0; i < c; i++)
                            F[i].display_money(id);
                    }
                }

                if (y == 4)
                {
                    cout << "输入卡号:";
                    cin >> id;
                    if (id >= 10000 && id < 20000){
                        for (int i = 0; i < a; i++)
                            T[i].display_times(id);
                    }
                    if (id >= 20000 && id < 30000){
                        for (int i = 0; i < b; i++)
                            S[i].display_times(id);
                    }
                    if (id >= 30000 && id < 40000){
                        for (int i = 0; i < c; i++)
                            F[i].display_times(id);
                    }

                }

                if(y == 5)
                {
                    cout<<"输入卡号：";
                    cin>>id;
                    if (id >= 10000 && id < 20000){
                        for (int i = 0; i < a; i++)
                            T[i].del(id);
                            
                        }
                    if (id >= 20000 && id < 30000){
                        for (int i = 0; i < b; i++)
                            S[i].del(id);
                    }
                    if (id >= 30000 && id < 40000){
                        for (int i = 0; i < c; i++)
                            F[i].del(id);
                    }
                    cout << "注销卡号成功！" << endl;
                }
                 cout << "输入1注册一张新卡，输入2为卡充值，输入3查询卡内余额，输入4查询本月已使用次数，输入5注销卡，输入0退出" << endl;
            }
        }


        //上车操作
        if(x == 2)
        {
            cout << "请输入当前时间(24小时制，只用输入小时即可）：" ; 
            cin >> current_time;
            //开始上车
            if(current_time >= 8 && current_time <= 18)
            {
                //从bus.txt中加载班车信息
                bus_file.open("bus.txt");
                while(bus_file >> driver_name >> bus_number >> start_time && driver_name != "")
                {
                    B[bus_index].init(driver_name,bus_number,start_time);
                    bus_index++;
                }
                bus_file.close();

                //计算当前时间要出发的汽车
                int index = (current_time - 8) * 2;

                //调用随机函数产生车的型号规格以及在车上的人数
                B[index].set_type_num();

                cout << "目前要出发的车辆信息为：" << endl;
                B[index].display_bus_information();

                if(B[index].isfull())
                {
                    cout << "车已满员，请乘坐下一辆车" << endl;
                }
                else 
                {
                    cout << "欢迎上车，请输入您的卡号：(输入0则退出）" ;
                    while(cin >> go_card_number && go_card_number != 0)
                    {
                        bool istook = false;
                        if(go_card_number >= 10000 && go_card_number <20000)
                        {
                            //老师卡
                            for(int k = 0; k < a; k++)
                            {
                                if(T[k].use(go_card_number))
                                {
                                    istook = true;

                                }
                            }
                        }
                        else if(go_card_number >= 20000 && go_card_number <30000)
                        {
                            //学生卡
                            for(int k = 0; k < b; k++)
                            {
                                if(S[k].use(go_card_number))
                                {
                                    istook = true;
                                }
                            }
                            
                        }
                        else if(go_card_number >= 30000 && go_card_number < 40000)
                        {
                            //家属卡
                            for(int k = 0; k < c; k++)
                            {
                                if(F[k].use(go_card_number))
                                {
                                    istook = true;
                                }
                            }
                        }
                        if(istook)  
                        {
                            B[index].count();
                        }
                        else
                        {
                            cout << "输入有误,未上车" << endl;
                        }
                        cout << "请下一位输入您的卡号(输入0则退出）："; 
                    }
                }
    
            }
            else
            {
                cout << "当前时间段没有班车，请其他时间再来乘坐" << endl;
            }
        }
        cout << "输入1进行一卡通业务办理，输入2 开始乘车, 输入0退出" << endl;
    }

    cout << "感谢您的使用，再见";
    return 0;
}