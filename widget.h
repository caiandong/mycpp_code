#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include"task_sort.h"
using namespace std;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
signals:
    void mm( vector<int> *s);
private slots:
    void on_pushButton_clicked();
    void time_out();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    float dw=10;
    int ii=0;
    Ui::Widget *ui;
    QTimer * qtime;
    vector<int> *a,*b;
    task_sort * task;
    QList<data1> que;
    QThread *mythread;
    QString s;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // WIDGET_H
