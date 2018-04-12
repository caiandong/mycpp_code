#include "task_sort.h"
#include<QDebug>

//vector<int> task_sort::kk=vector<int>({1,2,3,4,5});
task_sort::task_sort(QList<data1> &quee, QObject *parent) : QObject(parent),que(quee)
{

}

void task_sort::swap1(int &a, int &b)
{
    int tem=a;
    a=b;
    b=tem;
}

void task_sort::quick_sort(vector<int> &a, int l, int r)
{
    if(l<r)
    {
        int po=a[l];
        int ll=l,rr=r+1;
        for(; ;)
        {
            while(a[++ll]<po);
            while(a[--rr]>po);
            if(ll>rr)
                break;
            else
             //在这里把交换信息写入容器
            {
                swap1(a[ll],a[rr]);
                data1 d={ll,rr};
                que.append(d);
            }
        }
        {
            //同上
            swap1(a[l],a[rr]);
            data1 d={l,rr};
            que.append(d);
        }
        quick_sort(a,l,rr);
        quick_sort(a,rr+1,r);
    }
}

void task_sort::run_task(vector<int> *mlk)
{
    quick_sort(*mlk,0,mlk->size()-1);
}

