#include "calc.h"
void expression::setdata(std::string expr_str)
{ 
    if(expr_str[0]=='-')
        expr.push_back('0');

    for(auto i: expr_str) 
        expr.push_back(i);
}
void expression::getdata()
{
    std::string expr_str;
    std::cin>>expr_str;

    if(expr_str[0]=='-')
        expr.push_back('0');

    for(auto i: expr_str) 
        expr.push_back(i);
}
bool expression::IsOper(int j)
{
    bool f=0;
    char opers[5] {'+','-','*','/','^'};
    
    for(auto i: opers)
        if(expr[j]==i)
            f=1;
    
    return f;
}
bool expression::IsDigit(int j)
{

    bool f=0;
    char digits[10] {'0','1','2','3','4','5','6','7','8','9'};
    
    for(auto i: digits)
        if(expr[j]==i)
            f=1;
            
    return f;
}
int expression::whatOper(int j)
{
    switch (expr[j])
    {
        case '+': {return 0;break;} 
        case '-': {return 1;break;} 
        case '*': {return 2;break;} 
        case '/': {return 3;break;} 
        case '^': {return 4;break;} 
    }
}
double expression::whatDigit(int j)
{
    switch (expr[j])
    {
        case '0': {return 0;break;} 
        case '1': {return 1;break;}
        case '2': {return 2;break;}
        case '3': {return 3;break;}
        case '4': {return 4;break;}
        case '5': {return 5;break;}
        case '6': {return 6;break;}
        case '7': {return 7;break;}
        case '8': {return 8;break;} 
        case '9': {return 9;break;}
    }
}
void expression::calculate()
{
    std::vector<double> digits;
    std::vector<int> opers;
    result=0;
    for(int i=0;i<expr.size();i++)
        {
            if(expr[i]=='(')
                digits.push_back(brackets_count());
            else if(IsDigit(i)) {
                double dgt = 0;
                int index=1;
                int numIter=i;
                bool indicator=1;
                while ((IsDigit(numIter)|expr[numIter]=='.'|expr[numIter]==',')&& numIter<expr.size()) //считает каждое отдельное число
                {   
                    if(expr[numIter]=='.'|expr[numIter]==',') {
                            indicator=0;
                            index=1;
                            numIter++;
                            }
                    else {
                            if(indicator) {     //целое
                                dgt*=10;
                                dgt+=whatDigit(numIter);}
                            else {              //дробное
                                dgt+=whatDigit(numIter)/(pow(10,index));
                                index++;}
                            numIter++;
                    }
                    
                }
                
                i=numIter;
                digits.push_back(dgt);
                }//определить число
            if(IsOper(i)) 
                opers.push_back(whatOper(i));
        }
    for(int i=digits.size()-1;i>0;i--) {
        if(opers[i-1]==4){
            digits[i]=pow((digits[i-1]),(digits[i]));
            digits.erase(digits.begin()+i-1);
            opers.erase(opers.begin()+i-1);
            }
        }

    for(int i=1;i<digits.size();i++) 
        if(opers[i-1]==1)digits[i]=0-(digits[i]);
    
        for(int i=1;i<digits.size();i++)
            {
                if(opers[i-1]==2){
                    digits[i]*=digits[i-1];
                    digits.erase(digits.begin()+i-1);
                    opers.erase(opers.begin()+i-1);
                    i--;
                }
                if(opers[i-1]==3){
                    digits[i]=(digits[i-1])/(digits[i]);
                    digits.erase(digits.begin()+i-1);
                    opers.erase(opers.begin()+i-1);
                    i--;
                    }
            }
     for(auto i : digits) result +=i; 
    
}
void expression::showres()
{
    std::cout<<result<<std::endl;
}
double expression::brackets_count()
    {
        expression expr_in_brackets;
        std::string expr_in_br;
        int pos1=0;
        int pos2=0;
        int ind=0;

        for(int i=0;i<expr.size();i++){
            
            if(expr[i]==')'){
                ind--; 
                if(ind==0){pos2=i;break;}}
            
            if(ind!=0) 
                expr_in_br.push_back(expr[i]);
            
            if(expr[i]=='('){
                ind++;
                if(ind==1)
                    pos1=i;
                
                if(expr[pos1+1]=='-')
                    expr_in_br[0]='0';}
            }   

        expr.erase(expr.begin()+pos1,expr.begin()+pos2+1);
        expr_in_brackets.setdata(expr_in_br);
        expr_in_brackets.calculate();;
        return expr_in_brackets.result;
    }