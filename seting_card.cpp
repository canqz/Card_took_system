#include <string.h>
#include <iostream>
#include <fstream>

#include "People.h"

using namespace std;

ofstream file_out1;

//新建一个卡
void Card::init(string people_name,int num, int cardnum,string people_college,int people_money = 0, int people_times = 0)
{
    name = people_name;
    card_num = cardnum;
    college = people_college;//学院
    //辨别身份
    if(num == 1)
    {
        id = "Teacher Card";
    }else if(num == 2)
    {
        id = "Student Card";
    }else if (num == 3)
    {
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
	cout << "教师卡不能充值！\n";
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
}


bool Teacher::use(int num)
{
	if (num == card_num){
		times++;
		display_information(card_num);
		cout << "免费乘车\n" << endl;
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
			cout << "本月最后一次免费乘车\n" << endl;
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