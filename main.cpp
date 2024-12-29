#include<bits/stdc++.h>
using namespace std;
class matrix
{
public:
    matrix();//构造函数
    matrix(int r,int c,double* m);//构造函数初始化矩阵
    void setMatrix(int r,int c,double* m);//矩阵赋值函数
    bool square(matrix a);//判断方阵
    matrix matrixAdd(matrix a,matrix b);//矩阵加法函数
    matrix matrixSub(matrix a,matrix b);//矩阵减法函数
    matrix matrixSca(double x,matrix a);//矩阵数乘函数
    matrix matrixMul(matrix a,matrix b);//矩阵乘法函数
    matrix matrixTurn(matrix a);//矩阵转置函数
    matrix matrixCo(matrix a,int x,int y);//余子式矩阵函数
    double matrixDet(matrix a);//求行列式函数
    matrix matrixAcc(matrix a);//求伴随矩阵函数
    matrix matrixInv(matrix a);//求逆矩阵函数
    void display();//显示矩阵函数
    ~matrix();//析构函数
private:
    int row,column;
    double Matrix[10][10]={0};
};
matrix::matrix()
{
    row=0;
    column=0;
}
matrix::matrix(int r,int c,double* m)
{
    row=r;
    column=c;
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            Matrix[i][j]=m[i*c+j];
        }
    }
}
void matrix::setMatrix(int r,int c,double* m)
{
    row=r;
    column=c;
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            Matrix[i][j]=m[i*c+j];
        }
    }
}
bool matrix::square(matrix a)
{
    if(a.row==a.column)
        return 1;
    else
        return 0;
}
matrix matrix::matrixAdd(matrix a,matrix b)
{
    double x[a.row*a.column]= {0};
    matrix c(a.row,a.column,x);
    if(a.row!=b.row||a.column!=b.column)
    {
        printf("error\n");
    }
    else
    {
        for(int i=0; i<a.row; i++)
        {
            for(int j=0; j<a.column; j++)
            {
                c.Matrix[i][j]=a.Matrix[i][j]+b.Matrix[i][j];
            }
        }
    }
    return c;
}
matrix matrix::matrixSub(matrix a,matrix b)
{
    double x[a.row*a.column]= {0};
    matrix c(a.row,a.column,x);
    if(a.row!=b.row||a.column!=b.column)
    {
        printf("error\n");
    }
    else
    {
        for(int i=0; i<a.row; i++)
        {
            for(int j=0; j<a.column; j++)
            {
                c.Matrix[i][j]=a.Matrix[i][j]-b.Matrix[i][j];
            }
        }
    }
    return c;
}
matrix matrix::matrixSca(double x,matrix a)
{
    matrix c=a;
    for(int i=0; i<c.row; i++)
    {
        for(int j=0; j<c.column; j++)
        {
            c.Matrix[i][j]*=x;
        }
    }
    return c;
}
matrix matrix::matrixMul(matrix a,matrix b)
{
    matrix c;
    c.row=a.row;
    c.column=b.column;
    if(a.column!=b.row)
    {
        throw invalid_argument("Error");
    }
    else
    {
        for(int i=0; i<a.row; i++)
        {
            for(int j=0; j<b.column; j++)
            {
                double sum=0;
                for(int k=0; k<a.column; k++)
                {
                    sum+=(a.Matrix[i][k]*b.Matrix[k][j]);
                }
                c.Matrix[i][j]=sum;
            }
        }
    }
    return c;
}
matrix matrix::matrixTurn(matrix a)
{
    double x[a.column*a.row]= {0};
    matrix c(a.column,a.row,x);
    for(int i=0; i<a.column; i++)
    {
        for(int j=0; j<a.row; j++)
        {
            c.Matrix[i][j]=a.Matrix[j][i];
        }
    }
    return c;
}
matrix matrix::matrixCo(matrix a,int x,int y)
{
    if(!a.square(a))
    {
        throw invalid_argument("Error:This is not a square matrix.");
    }
    else
    {
        matrix re;
        x=x-1;
        y=y-1;
        re.row=a.row-1;
        re.column=a.column-1;
        int m=0,n=0;
        for(int i=0; i<a.row; i++)
        {
            if(i==x)
                continue;
            else
            {
                for(int j=0; j<a.column; j++)
                {
                    if(j==y)
                        continue;
                    else
                    {
                        re.Matrix[m][n]=a.Matrix[i][j];
                        n++;
                    }
                }
                n=0;
                m++;
            }
        }
        return re;
    }
}
double matrix::matrixDet(matrix a)
{
    if(!a.square(a))
        throw invalid_argument("Error:This is not a square matrix.");
    else
    {
        if(a.row==2)
        {
            double re=(a.Matrix[0][0]*a.Matrix[1][1])-(a.Matrix[0][1]*a.Matrix[1][0]);
            return re;
        }
        else
        {
            double sum=0;
            for(int j=1; j<=a.column; j++)
            {
                int flag=1;
                if((1+j)%2==1)
                    flag=-1;
                matrix b=a.matrixCo(a,1,j);
                sum+=(flag*a.Matrix[0][j-1]*matrixDet(b));
            }
            return sum;
        }
    }
}
matrix matrix::matrixAcc(matrix a)
{
    if(!a.square(a))
        throw invalid_argument("Error:This is not a square matrix.");
    else
    {
        matrix re;
        re.row=a.column;
        re.column=a.row;
        for(int i=0; i<a.column; i++)
        {
            for(int j=0; j<a.row; j++)
            {
                int flag=1;
                if((i+j)%2==1)
                    flag=-1;
                re.Matrix[i][j]=flag*a.matrixDet(a.matrixCo(a,j+1,i+1));
            }
        }
        return re;
    }
}
matrix matrix::matrixInv(matrix a)
{
    if(!a.square(a))
        throw invalid_argument("Error:This is not a square matrix.");
    else
    {
        if(a.matrixDet(a)==0)
            throw invalid_argument("Error:This matrix can not be computed.");
        else{
            matrix re=a.matrixAcc(a);
            re=re.matrixSca(1.0/a.matrixDet(a),re);
            return re;
        }
    }
}
void matrix::display()
{
    printf("----------------------------------------\n");
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++)
        {
            printf("%10.2lf",Matrix[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------------\n");
}
matrix::~matrix()
{
}
int main()
{
    while(true)
    {
        printf("请选择运算：\n1.矩阵加法 2.矩阵减法 3.矩阵数乘 4.矩阵乘法 5.矩阵转置");
        printf("\n6.余子式矩阵 7.矩阵的行列式 8.伴随矩阵 9.逆矩阵 0.退出程序\n");
        int x;
        scanf("%d",&x);
        if(x==0)
            break;
        else
        {
            if(x==1||x==2||x==4)
            {
                matrix a,b,c;
                int ar,ac,br,bc;
                printf("请输入矩阵a的行数和列数（用空格分隔）：\n");
                scanf("%d %d",&ar,&ac);
                printf("请输入矩阵b的行数和列数（用空格分隔）：\n");
                scanf("%d %d",&br,&bc);
                if(ar<=0||ac<=0||br<=0||bc<=0)
                {
                    printf("error\n");
                    continue;
                }
                else
                {
                    double am[ar*ac],bm[br*bc];
                    printf("请输入矩阵a的元素（用空格分隔）：\n");
                    for(int i=0; i<ar*ac; i++)
                    {
                        scanf("%lf",&am[i]);
                    }
                    printf("请输入矩阵b的元素（用空格分隔）：\n");
                    for(int i=0; i<br*bc; i++)
                    {
                        scanf("%lf",&bm[i]);
                    }
                    a.setMatrix(ar,ac,am);
                    b.setMatrix(br,bc,bm);
                    if(x==1)
                    {
                        c=a.matrixAdd(a,b);
                    }
                    else
                    {
                        if(x==2)
                        {
                            c=a.matrixSub(a,b);
                        }
                        else
                        {
                            c=a.matrixMul(a,b);
                        }
                    }
                    c.display();
                }
            }
            else
            {
                if(x==3)
                {
                    double sca;
                    printf("请输入倍数：\n");
                    scanf("%lf",&sca);
                    matrix a,b;
                    int ar,ac;
                    printf("请输入矩阵a的行数和列数（用空格分隔）：\n");
                    scanf("%d %d",&ar,&ac);
                    if(ar<=0||ac<=0)
                    {
                        printf("error\n");
                        continue;
                    }
                    else
                    {
                        double am[ar*ac];
                        printf("请输入矩阵a的元素（用空格分隔）：\n");
                        for(int i=0; i<ar*ac; i++)
                        {
                            scanf("%lf",&am[i]);
                        }
                        a.setMatrix(ar,ac,am);
                        b=a.matrixSca(sca,a);
                        b.display();
                    }
                }
                else
                {
                    if(x==5||x==6||x==7||x==8||x==9)
                    {
                        matrix a,b;
                        int ar,ac;
                        printf("请输入矩阵a的行数和列数（用空格分隔）：\n");
                        scanf("%d %d",&ar,&ac);
                        if(ar<=0||ac<=0)
                        {
                            printf("error\n");
                            continue;
                        }
                        else
                        {
                            double am[ar*ac];
                            printf("请输入矩阵a的元素（用空格分隔）：\n");
                            for(int i=0; i<ar*ac; i++)
                            {
                                scanf("%lf",&am[i]);
                            }
                            a.setMatrix(ar,ac,am);
                            if(x==5)
                            {
                                b=a.matrixTurn(a);
                                b.display();
                            }
                            else
                            {
                                if(x==6)
                                {
                                    printf("哪个元素的余子式？\n");
                                    int ax,ay;
                                    scanf("%d %d",&ax,&ay);
                                    b=a.matrixCo(a,ax,ay);
                                    b.display();
                                }
                                else
                                {
                                    if(x==7)
                                    {
                                        double re=a.matrixDet(a);
                                        printf("a的行列式的值为%.2lf\n",re);
                                    }
                                    else
                                    {
                                        if(x==8)
                                        {
                                            b=a.matrixAcc(a);
                                            b.display();
                                        }
                                        else
                                        {
                                            if(x==9)
                                            {
                                                b=a.matrixInv(a);
                                                b.display();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        printf("error\n");
                        continue;
                    }
                }
            }
        }
    }
    return 0;
}
