#include "iostream"
#include "spline.h"

int X[5] = {0,1,4,5,8};
int Y[5] = {0,3,4,1,2};
SPLINE spline(X,Y,5);
int main(){
    for(double i = 0;i<10;i = i+0.1){
        printf("%lf,%lf\n",i,spline.get(i));
    }

}