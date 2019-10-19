#include "iostream"
#include "spline.h"
#include "cmath"
//void caluclation(int *X,int *Y,int len,double *out);

SPLINE::SPLINE(int *X,int *Y,int len){
    _len = len;
    for(int i = 0;i<len;i++)splineX[i] = *(X+i);
    double splineAA[len][len];
    for(int i = 0;i<len;i++)for(int j = 0;j<len;j++)splineAA[i][j] = 0;//初期化

    double splineH[len - 1];
    
    double inv_a[len][len];
    double caluclationBuf;

    for(int i = 0;i<len;i++)splineA[i] = *(Y+i);
    for(int i = 0;i<len-1;i++)splineH[i] = *(X + i + 1) - *(X + i);
    for(int i = 0;i<len;i++){
        float tempB;
        tempB = (i == 0 || i == len-1)?0:((3/splineH[i])*(splineA[i+1] - splineA[i]) - (3/splineH[i-1])*(splineA[i] - splineA[i-1]));//加速度は両端0
        splineB[i] = tempB;
    }
    for(int i = 0;i<len;i++){
        if(i == 0)splineAA[i][0] = 1;
        else if(i == len-1)splineAA[i][len-1] = 1;
        else{
            splineAA[i][i-1] = splineH[i-1];
            splineAA[i][i] = 2*(splineH[i-1] + splineH[i]);
            splineAA[i][i+1] = splineH[i];
        }
    }

    ////////////////逆行列////////////
    /////////////////////単位行列////////////////////
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            inv_a[i][j]=(i==j)?1.0:0.0;
        }
    }
    /////////////////////////////////////////////////
    for(int i=0;i<len;i++){
    caluclationBuf=1/splineAA[i][i];
    for(int j=0;j<len;j++){
        splineAA[i][j]*=caluclationBuf;
        inv_a[i][j]*=caluclationBuf;
    }
    for(int j=0;j<len;j++){
    if(i!=j){
    caluclationBuf=splineAA[j][i];
    for(int k=0;k<len;k++){
    splineAA[j][k]-=splineAA[i][k]*caluclationBuf;
    inv_a[j][k]-=inv_a[i][k]*caluclationBuf;
       }
      }
     }
    }
    ///////////////////////////////////////////////////
    for(int i = 0;i<len;i++){
        for(int j = 0;j<len;j++){
            if(j == 0)splineC[i] = 0;
            splineC[i] += inv_a[i][j]*splineB[j]; 
        }
    }
    for(int i = 0;i<len;i++)splineD[i] = (splineC[i+1] - splineC[i])/3/splineH[i];
    for(int i = 0;i<len;i++)splineB[i] = (splineA[i+1] - splineA[i])/splineH[i] - splineH[i]*(splineC[i+1] + 2*splineC[i])/3;
    /*
    for(int i = 0;i<4;i++){
        switch(i){
            case 0:
                for(int j = 0;j<len-1;j++)*(out + j) = splineA[j];
            break;
            case 1:
                for(int j = 0;j<len-1;j++)*(out + j + len) = splineB[j];
            break;
            case 2:
                for(int j = 0;j<len-1;j++)*(out + j + len*2) = splineC[j];
            break;
            case 3:
                for(int j = 0;j<len-1;j++)*(out + j + len*3) = splineD[j];
            break;
        }
    }
    */
}

double SPLINE::get(double x){
    int arraycount;
    double out;
    double x_error;
    for(int i = 0;i<_len;i++){
        if(splineX[i] <= x && splineX[i+1] > x){//xがTnの範囲内だったら
            x_error = (x - (double)splineX[i]);
            printf("%f,%f\n",x_error,x);
            out = splineA[i] + splineB[i]*x_error + splineC[i]*pow(x_error,2); + splineD[i]*pow(x_error,3);
            break;
        }else if(x == splineX[i]){
            out = splineX[i];
        }
    }
    return(out);
}

void SPLINE::debugg(){
    //for(int i = 0;i<_len;i++)printf("%d\t\t",splineX[i]);
    printf("\n");
    for(int i = 0;i<4;i++){
        switch(i){
            case 0:
                for(int j = 0;j<_len-1;j++)printf("%f\t\t",splineA[j]);
                printf("\n");
            break;
            case 1:
                for(int j = 0;j<_len-1;j++)printf("%f\t\t",splineB[j]);
                printf("\n");
            break;
            case 2:
                for(int j = 0;j<_len-1;j++)printf("%f\t\t",splineC[j]);
                printf("\n");
            break;
            case 3:
                for(int j = 0;j<_len-1;j++)printf("%f\t\t",splineD[j]);
                printf("\n");
            break;
        }
    }
}

int main(){
    int X[5] = {0,1,4,5,8};
    int Y[5] = {0,3,4,1,2};
    double out[5][5];
    SPLINE sp(X,Y,5);
    //sp.debugg();
    for(double i = 0;i<8;i += 0.01)sp.get(i);
    //printf("%f,%f\n",i,sp.get(i));
}

