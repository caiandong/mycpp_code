#ifndef WIDGET_H
#define WIDGET_H
//可以倒回，动态，放入另一个线程处理
#include <QWidget>
#include"quanjubianliang.h"
#include<QThread>
#include<QTimer>
#include<QVector>
#include<QMap>
namespace Ui {
class Widget;
}
//*****************************
class Widget;
class myTask:public QObject {
    Q_OBJECT
public:
     myTask(QObject *parent=0):QObject(parent){}
     myTask(QObject *parent , Widget *widget );
     myTask & operator =(const myTask& x);
    ~myTask();
private:
    void recursion_hannuo(int k, myStack* a, myStack* b, myStack* c);
    void turntochar( myStack* a, myStack* b);
    void huancun();
    //const static int ll=2;
    QVector<vectordate> *vector1;
    QVector<rectweizhi> *vector2;
    myStack **arrstack;
//    QMap<char,double> map;

signals:
    void hanno_end();
public slots:
    void hanno_start(int,myStack*,myStack*,myStack*);
};
//****************************

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
     myStack *arrstack[3];
     QVector<vectordate> vector1;    //作为来存储步骤的容器cun
     QVector<rectweizhi> vector2;
signals:
    void start(int k,myStack* a,myStack* b,myStack* c/*,QLineEdit *m*/);
    void resizeprint();
public slots:
     void draw_grah();
     void initial_drawgrah();
     void fenpei();
    // void shipeiqi();
private:

     void task0();
     void task1();
     void task2();
     void task3();
    //自己定义函数

    void jiekou();
    void initial_mystack(int);

    void recursion_hanno(int k, myStack* a,myStack* b,myStack* c);
    void initial_value();
    void turntochar(myStack* A,myStack* B);
    double sb_function(int n){
       if(n<1)
           return 0;
       double m=2;
       for(int i=1;i<n;i++)
           m*=2;
       return m-1;
    }
    myStack * sb2_function(char m, myStack ** p){
        if(m=='a')
            return (p[0]);
        else if(m=='b')
                return (p[1]);
        else if(m=='c')
            return (p[2]);

    }
private slots:
    void on_initialpushButton_clicked();

    void on_V_horizontalSlider_valueChanged(int value);

    void on_ChangetimesspinBox_valueChanged(int arg1);

    void on_startpushButton_clicked();

    void on_end_pushButton_clicked();

    void on_next_pushButton_clicked();

    void on_last_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    //自己定义的变量
    myStack stack1;     //继承自QStack<stackdate>，作为来存储步骤的容器
     //表示三根柱子上的盘子，抽象为栈
    myTask *task;        //自定义任务，movetothread 去执行
    QThread *mythread;  //创建个线程


    QTimer *timer;      //计时器
    double time;       //控制计时器速度
    bool change;        //中间运动和开始结束运动的变化
    double up,down,rightleft;       //表示中间运动的三个状态量
    QPainter * paintp;      //在pix上绘图
    //QPixmap tempix1;        //临时画布
    //好像不用更有效率
    double iv=0;        //控制 中间绘图速度
    double tem;      //
    char aa,bb;         //用于读入柱子交换
    myStack * tema;     //
    myStack * temb;     //
    enum chose{one,tow,three};      //
    chose mmu;      //
    //QPixmap  tempix2;       //ssssssssssss
    QColor colors;      //pix初始颜色
    int X,Y;            //画布大小
    bool b;             //
    QPixmap pix;        //在pix上绘图
    double rh,rw,dr,rx,ry;          //矩形大小
    int ta,tb,tc;       //代表 abc 三个柱子
    int mn,number,n1;       //
    bool xiancheng=false;       //线程状态
    long a;     //
    bool chushihua=false;
    bool zhengzaijinxing=false;
    bool nextbool=false;
    bool lastbool=false;
    int n_numbe=0;
    long long xx=0;

    double rdx;

    double rect_w;
    int from_h;
    double from_which;
    int to_h;
    double to_which;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // WIDGET_H
