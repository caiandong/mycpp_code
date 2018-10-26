#include "widget.h"
#include "ui_widget.h"
#include<ctime>
#include<cstdlib>
#include<QtWidgets>
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    a=new vector<int>(1,0);
    b=new vector<int>(1,0);
    qtime=new QTimer(this);
    task=new task_sort(que);
    mythread=new QThread(this);
    connect(qtime, SIGNAL(timeout()), this, SLOT(time_out()));
    connect(this,&Widget::mm,task,&task_sort::run_task);

    task->moveToThread(mythread);
    mythread->start();
}

Widget::~Widget()
{
    delete ui;
    delete task;
    delete a;
    delete b;
    mythread->quit();
}

void Widget::on_pushButton_clicked()
{
    if(qtime->isActive())
    {
        ui->pushButton->setText("开始");
        ui->pushButton->setEnabled(true);
        qtime->stop();
    }
    else
    {
        ui->pushButton->setText("关闭");
        qtime->start(30);
    }


}

void Widget::time_out()
{
    if(que.size()-1<ii)
    {

        qtime->stop();
        ui->pushButton->setText("开始");
        ui->pushButton->setEnabled(true);
        return;
      }

    int i=que.at(ii).left;
    int j=que.at(ii).right;
    ii++;
    //qDebug()<<i<<" "<<j;
    task_sort::swap1((*a)[i],(*a)[j]);
    update();

}

void Widget::on_pushButton_2_clicked()
{
    delete a;
    delete b;
    int aaaa=ui->lineEdit->text().toInt();
    a=new vector<int>(aaaa,0);
    b=new vector<int>(aaaa,0);
    dw=15*30/aaaa;
    ii=0;
    que.clear();
    s.clear();
    srand(time(0));

    for(auto & x:*a)
        x=rand()%180;
    *b=*a;
    emit mm(b);
    for(auto x:*a)
        s.append(QString::number(x)+" ");

    update();

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setBrush(QBrush(Qt::red));
    if(a->size()<31)
        paint.drawText(20,45,s);
    //paint.drawLine(100,400,10*a->size()+80,400);
    for(int i=0;i<a->size();i++)
    {
        int h=(*a)[i]*2;
        paint.drawRect(80+dw*i,400-h,dw,h);
        //paint.drawText(100+10*i+2,400-h-10,QString::number((*a)[i]));
    }
}

void Widget::on_pushButton_3_clicked()
{
    if(que.size()-1<ii)
        return;

    int i=que.at(ii).left;
    int j=que.at(ii).right;
    ii++;

    task_sort::swap1((*a)[i],(*a)[j]);
    update();
}
