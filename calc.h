
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
class expression{
    private:
        std::vector<char> expr;
        bool IsOper(int);
        bool IsDigit(int);
        int whatOper(int);
        double whatDigit(int);
        double brackets_count();
    public:
        void setdata(std::string);
        void getdata();
        void calculate();
        void showres();
        double result=0;

};
