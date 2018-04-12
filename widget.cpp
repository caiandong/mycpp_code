#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QMessageBox>
#include<QDebug>
//******************************
double myStack::rect_w;
void myStack::get_initial(double m)
{
    myStack::rect_w=m;
}
myTask::myTask(QObject *parent, Widget *widget) : QObject(parent)
{
    vector1=&widget->vector1;//new QVector<chardate>;
    vector2=&widget->vector2;
    arrstack=widget->arrstack;
//    map['a']=150;
//    map['b']=450;
//    map['c']=750;
}

myTask &myTask::operator =(const myTask &x)
{
    vector1=x.vector1;
    vector2=x.vector2;
    arrstack=x.arrstack;
    return *this;
}

myTask::~myTask()
{

}

void myTask::recursion_hannuo(int k, myStack *a, myStack *b, myStack *c){
    if(k>0)
    {
        recursion_hannuo(k-1,a,c,b);
        turntochar(a,b);
        recursion_hannuo(k-1,c,b,a);
    }
}
void myTask::turntochar(myStack *a, myStack *b)
{
    vectordate m{a,b};
    vector1->append(m);
}

void myTask::huancun()
{
   rectweizhi mm;
   for(auto x: *vector1)
   {
       mm.from_which=x.from->nagezhuzi;
       mm.from_h=x.from->count();

       mm.rect_w= x.from->pop();
       x.to->push(mm.rect_w);

       mm.to_which =x.to->nagezhuzi;
       mm.to_h=x.to->count()+1;
       vector2->append(mm);
   }

}

void myTask::hanno_start(int k, myStack *a, myStack *b, myStack *c)
{
    if(vector1->count()!=0)
    {
        vector2->clear();
        vector1->clear();
    }
    recursion_hannuo(k,a,b,c);
    huancun();
    qDebug()<<vector2->count();
    emit hanno_end();
}

//*****************************
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //ui->times_lable->setBuddy(ui->startpushButton);//按下标签快捷键时接受焦点
    timer=new QTimer(this);
    initial_value();
    initial_mystack(mn);
    initial_drawgrah();
    //connect(timer,SIGNAL(timeout()),this,SLOT(draw_grah()));
    connect(timer,&QTimer::timeout,this,&Widget::fenpei);
   // connect(timer,&QTimer::timeout,this,&Widget::draw_grah);
    //connect(this,resizeprint,this,initial_drawgrah);
}

Widget::~Widget()
{
    delete ui;
    delete paintp;
    if(!arrstack)
        delete []arrstack;
    if(mythread)
    {
        mythread->quit();
        mythread->wait();

    }
}

void Widget::on_initialpushButton_clicked()
{
//    if()
    on_end_pushButton_clicked();
    number=0;
    change=true;
    lastbool=false;
    nextbool=false;
//    up=mn;
    arrstack[0]->clear();
    arrstack[1]->clear();
    arrstack[2]->clear();
    initial_mystack(mn);

    pix.fill(colors);
    initial_drawgrah();
    ui->next_pushButton->setEnabled(true);
//    update();


    //int x=ui->ChangetimesspinBox->text().toInt();
//    if(mn>5)
//    {
       if(!xiancheng){
           task=new myTask(nullptr,this);
           mythread=new QThread(this);

           task->moveToThread(mythread);


           connect(this,&Widget::start,task,&myTask::hanno_start);
           connect(mythread,&QThread::finished,task,&myTask::deleteLater);
           connect(task,&myTask::hanno_end,this,
           [=]()
           {
               //QMessageBox::information(this,QString("1").toUtf8(),"初始化完成,并且缓存完毕");
               //this->list=diguilei->list;
               update();
               chushihua=true;

           });

           mythread->start();
           xiancheng=true;
       }
       emit start(mn,arrstack[0],arrstack[1],arrstack[2]/*,ui->lineEdit_2*/);
//        }
//    else
//        recursion_hanno(mn,arrstack[0],arrstack[1],arrstack[2]);
}

void Widget::on_V_horizontalSlider_valueChanged(int value)
{
    if(value!=time)
    {
        time=value;
        timer->stop();
        timer->setInterval(value);
        //timer->start(value);
    }
}

void Widget::on_ChangetimesspinBox_valueChanged(int arg1)
{
    mn=arg1;

    ui->TimeslineEdit->setText(QString("%1").arg(sb_function(arg1),0,'f',2));
}

void Widget::on_startpushButton_clicked()
{

    if(!chushihua||zhengzaijinxing)
        QMessageBox::information(this,QString("1").toUtf8(),"未初始化,也许正在进行");
    else if(number==vector2.count())
        QMessageBox::information(this,QString("1").toUtf8(),"绘图好了 还按毛啊");
    if(!timer->isActive())
    {
        ui->next_pushButton->setEnabled(false);
        timer->start(time);
    }

     qDebug()<<"start ";
}

void Widget::on_end_pushButton_clicked()
{
    if(timer->isActive())
     {

        timer->stop();
        qDebug()<<"stop ";
        //chushihua=false;
        zhengzaijinxing=false;
       }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.drawPixmap(0,0,pix);
   // qDebug()<<xx++;

}

void Widget::resizeEvent(QResizeEvent *event)
{
   // emit resizeprint();
    qDebug()<<"ssddd";
}
void Widget::draw_grah()
{
    if(number==vector2.count())
      {
        timer->stop();
        zhengzaijinxing=false;
        qDebug()<<"stop self ";
        return;
      }
//    if(timer->isActive())

         rect_w=vector2[number].rect_w;
         from_h=vector2[number].from_h;
        from_which=vector2[number].from_which;
        to_h=vector2[number].to_h-1;
         to_which=vector2[number].to_which;
        QPixmap tempix1(rect_w,rh);



        tempix1.fill(Qt::white);
        paintp->drawPixmap(from_which-rect_w/2,Y-rh*from_h,tempix1);
        tempix1.fill(Qt::red);
        paintp->drawPixmap(to_which-rect_w/2,Y-rh*to_h,tempix1);
  //      update();
        //qDebug()<<"paint  up "<<up;
 //       return;
 //   }
//    tempix1.fill(Qt::red);
//    paintp->drawPixmap(to_which-rect_w/2,Y-rh*to_h,tempix1);

    number++;
    qDebug()<<"paint ";
    update();

}

void Widget::initial_drawgrah()
{
//    initial_mystack(mn);
//    pix=QPixmap(width(),height());
    n1=mn;
    for(int i=0;i<n1;i++){
        paintp->fillRect(ta-(rw+i*20)/2,Y-(n1-i)*rh,rw+i*20,rh,Qt::red);
    }

}

void Widget::fenpei()
{
    if(number==vector2.count())
      {
        timer->stop();
        zhengzaijinxing=false;
        qDebug()<<"stop self ";
        return;
      }
    if(lastbool&& number<1)
    {
        qDebug()<<"jieshu";
        timer->stop();
        zhengzaijinxing=false;
        return;
    }
    if(change)
    {

        task0();
        mmu=one;
//        if(number==0)
//            change=true;
//        else
            change=false;
    }
    else if(mmu==one)
    {
        task1();

    }
    else if(mmu==tow)
    {
        task2();

    }
    else if(mmu==three)
    {
        task3();

    }

}

void Widget::task0()
{
    if(lastbool)
    {

//        if(number<1)
//            {
//                qDebug()<<"jieshu"<<number;
//                timer->stop();
//                zhengzaijinxing=false;
//                return;
//            }
//        number--;
        rect_w=vector2[number-1].rect_w;
        from_h=vector2[number-1].to_h-1;
        from_which=vector2[number-1].to_which;
        to_h=vector2[number-1].from_h;
        to_which=vector2[number-1].from_which;
        //change=true;
        //number--;
    }
    else
    {
//        if(number==vector2.count())
//              {
//                timer->stop();
//                zhengzaijinxing=false;
//                qDebug()<<"stop self ";
//                return;
//              }
         rect_w=vector2[number].rect_w;
         from_h=vector2[number].from_h;
         from_which=vector2[number].from_which;
         to_h=vector2[number].to_h-1;
         to_which=vector2[number].to_which;
         //change=false;
         //number++;
    }
    up=from_h;
    down=mn;
    rightleft=from_which;
    rdx=to_which>from_which?rh:-rh;

}

void Widget::task1()
{
    //qDebug()<<up;
    if(up>=mn+3)
     {
        mmu=tow;
        return;
    }
    QPixmap tempix2=QPixmap(rect_w,rh);
    tempix2.fill(Qt::white);
    paintp->drawPixmap(from_which-rect_w/2,Y-rh*up,tempix2);
    up+=0.5;
    tempix2.fill(Qt::red);
    paintp->drawPixmap(from_which-rect_w/2,Y-rh*up,tempix2);
    update();
}

void Widget::task2()
{

    QPixmap tempix2=QPixmap(rect_w,rh);
    tempix2.fill(Qt::white);
    paintp->drawPixmap(rightleft-rect_w/2,Y-rh*up,tempix2);
    rightleft+=rdx*0.5;
    tempix2.fill(Qt::red);
    paintp->drawPixmap(rightleft-rect_w/2,Y-rh*up,tempix2);
    update();
    if(rightleft==to_which)
     {
        mmu=three;
        down=up;
        //rightleft+=rh;
        return;
    }

}

void Widget::task3()
{
    if(down<=to_h)
     {
        change=true;

        if(nextbool)
        {
            timer->stop();
            nextbool=false;
            number++;
            return;
        }
        else if(lastbool)
        {
            timer->stop();
            lastbool=false;
            number--;
            return;
        }
        number++;
        return;
    }
    QPixmap tempix2=QPixmap(rect_w,rh);
    tempix2.fill(Qt::white);
    paintp->drawPixmap(rightleft-rect_w/2,Y-rh*down,tempix2);
    down-=0.5;
    tempix2.fill(Qt::red);
    paintp->drawPixmap(rightleft-rect_w/2,Y-rh*down,tempix2);
    update();
}

void Widget::jiekou()
{

}

void Widget::initial_mystack(int n)
{
    for(int i=1;i<=n;i++){
        double tem{(mn-i)*dr+rw};
        arrstack[0]->push(tem);
    }
}

void Widget::recursion_hanno(int k, myStack* a, myStack* b, myStack* c)
{
    if(k>0)
    {
        recursion_hanno(k-1,a,c,b);
        turntochar(a,b);
        recursion_hanno(k-1,c,b,a);
    }
}

void Widget::initial_value()
{

    rh=20;
    rw=30;
    dr=20;
    ta=150;//1/6*width() ;
    tb=450;//1/2*width();
    tc=750;//5/6*width();
    time=15;
    b=true;
    X=900;
    Y=500
            ;
    xiancheng=false;

    colors=Qt::white ;
    pix=QPixmap(X,Y);
    pix.fill(colors);
    paintp= new QPainter(&pix);
    number=0;    
    mn=3;

    //********************************wocao卧****啊！！！！！！！！！！！！
    mythread=nullptr;
    //日狗了啊 *****************************************
    //mystack::get_initial(rh);
    arrstack[0]=new myStack(ta);
    arrstack[1]=new myStack(tb);
    arrstack[2]=new myStack(tc);

    //ui->TimeslineEdit->setText("试试！");
    ui->V_horizontalSlider->setValue(time);
    ui->ChangetimesspinBox->setValue(mn);
    a=0;
    mmu=one;
    change=true;
}

void Widget::turntochar(myStack *A, myStack *B)
{
    vectordate m{A,B};
    vector1.append(m);
}


void Widget::on_next_pushButton_clicked()
{
    if(!chushihua)
        QMessageBox::information(this,QString("1").toUtf8(),"未初始化,并且缓存没完毕");
    else if(number==vector2.count())
         QMessageBox::information(this,QString("1").toUtf8(),"画完了 没了");
    else
    {
        //number++;
        timer->start(time);
        nextbool=true;

       // draw_grah();
    }
}

void Widget::on_last_pushButton_3_clicked()
{
    //number--;
    timer->start(time);
    lastbool=true;

    //QMessageBox::information(this,QString("fucking!").toUtf8(),"别急 这个按钮并不知道要做什么");
}
