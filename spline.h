class SPLINE{
    public:
        SPLINE(int *X,int *Y,int len);
        double get(double x);
        void debugg();
    private:
        int _len;
        int splineX[50];
        double splineA[50];
        double splineB[50];
        double splineC[50];
        double splineD[50];
};