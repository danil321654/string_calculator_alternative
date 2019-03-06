#include "calc.h"
int main()
{
    while(1){
        expression expr;
        expr.getdata();
        expr.calculate();
        expr.showres();
    }
    return 0;
}
