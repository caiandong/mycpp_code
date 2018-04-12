#ifndef TASK_SORT_H
#define TASK_SORT_H

#include <QObject>
#include <QList>
#include <vector>
using namespace std;
struct data1
{
    int left;
    int right;

};
class task_sort : public QObject
{
    Q_OBJECT
public:
    explicit task_sort(QList<data1> &quee,QObject *parent = 0);
    static void swap1(int &a,int &b);

private:
    //static vector<int> kk;
    QList<data1> &que;
    //这个快排函数用QVector编译会出现越界错误，用vector却可以，这个函数有问题 可以重新写下
    void quick_sort(vector<int> &a,int l,int r);

signals:

public slots:
    void run_task(vector<int> *mlk);
};

#endif // TASK_SORT_H
