#include <iostream>
#include<vector>
#include<queue>
using namespace std;
ostream & operator <<(ostream & aa,const vector<int> & bb)
{
    for(auto x:bb)
        aa<<x<<" ";
    aa<<endl;
    return aa;
}
void cout_point_b(int dis=10)
{
    for(int i=0;i<dis;i++)
        cout<<"  ";
}
void cout_point(int item,int x,int dy=2,char a=' ',char b='\n')
{
    for(int i=0;i<dy;i++)
        cout<<b;
    for(int i=0;i<x;i++)
        cout<<a;
    cout<<item;
}
class rb_tree
{
public:
    enum colour{red,black};
    rb_tree():root(nullptr),left_buttom_point_x(0),jj(0),a(nullptr){}
    void insert(int item){insert(item,root);}
    void remove(int item){remove(item,root);jj=0;print_mid(root);cout<<endl;}
    void print_mid(vector<int> &kk){a=&kk;print_mid(root);cout<<endl;}
    void print_tree(){find_min(root); print_tree(root,left_buttom_point_x);cout<<endl;}
    void print_anhang()
    {
        queue<p_node> aa,b;
        aa.push(root);
        cout<<"start"<<endl;
        anhangdayin(aa,b);
        cout<<"over"<<endl;
    }
    void erfen(int item)
    {
        cout<<erfenchazhao(0,(*a).size()-1,item)<<endl;
    }

private:
    class node
    {
    public:
        int item;
        colour col;
        node * left;
        node * right;
        node(int x,colour c=red):item(x),col(c),left(nullptr),right(nullptr){}
    };
    typedef node * p_node;
    p_node root;
    vector<int> *a;
    int jj;
    int left_buttom_point_x;

    void zengjia_x(){left_buttom_point_x+=4;}
    void insert(int item,p_node & x);
    void remove(int item,p_node & x);
    void print_mid(const p_node &x);
    void print_tree(const p_node &x, int a)const;
    void find_min(const p_node &x);
    p_node &find_left_min( p_node &x)
    {
        p_node tem=x;
        while(tem->left&&tem->left->left)
        {
            tem->left=tem->left->left;
        }
        if(x->left)
            return tem->left;
        else
            return x;
    }
    int erfenchazhao(int i,int j,int item){
        int l=i,r=j;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if((*a)[mid]<item)
                l=mid+1;
            else if((*a)[mid]>item)
                r=mid-1;
            else
              return mid;
        }
        cout<<" no data"<<endl;
        return 0;
    }
    void anhangdayin(queue<p_node> &q1,queue<p_node> &q2);
};
void rb_tree::remove(int item, p_node &x)
{
    if(x)
    {
        if(item<x->item)
            remove(item,x->left);
        else if(item>x->item)
            remove(item,x->right);
        else
        {
            if(x->left==nullptr)
            {
                p_node temp=x;
                x=x->right;
                delete temp;
            }
            else if(x->right==nullptr)
            {
                p_node temp=x;
                x=x->left;
                delete temp;
            }
            else
            {
                p_node& tem=find_left_min(x->right);
                x->item=tem->item;
                remove(tem->item,tem);
            }
        }
    }
}
void rb_tree::anhangdayin(queue<p_node> &q1,queue<p_node> &q2)
{
    if(!q1.empty())
    {
        int qianyige=0,shuzigeshu=0;
        while(!q1.empty())
         {

            p_node x=q1.front();
            q1.pop();
            int jjjj=erfenchazhao(0,(*a).size()-1,x->item)-qianyige-shuzigeshu++;
            //shuzigeshu++;
            cout_point_b(jjjj);
            qianyige=jjjj+qianyige;
            cout<<x->item;
            if(x->left)
                q2.push(x->left);
            if(x->right)
                q2.push(x->right);
        }
        cout<<endl<<endl;
        //q1=queue<p_node>();
        anhangdayin(q2,q1);
    }
}
void rb_tree::insert(int item, p_node &x)
{
    if(x==nullptr)
        x=new node(item);
    else if(item<x->item)    
        insert(item,x->left);    
    else if(item>x->item)
        insert(item,x->right);
    else
        cout<<"dose exit! "<<item<<endl;
}
void rb_tree::print_mid(const p_node &x)
{
    if(x)
    {
        print_mid(x->left);
        cout<<x->item<<" ";
        (*a)[jj++]=x->item;

        print_mid(x->right);
    }
}
void rb_tree::print_tree(const p_node &x,int a) const
{
    if(x)
    {
        cout_point(x->item,a);
        print_tree(x->left,a-4);
        print_tree(x->right,a+4);
    }
}
void rb_tree::find_min(const p_node &x)
{
    p_node xx=x;
    while(xx)
    {
        zengjia_x();
        xx=xx->left;
    }
}
int main()
{
    cout << "树形打印二叉树" << endl;
    vector<int> a({44,56,22,15,47,33,27,87,88,90,43,55,12,11,18,14,10});
    vector<int> xx(a.size());
    //xx[0]=1;
    vector<int> &p=a;
    cout<<"origin data :"<<a;
    rb_tree mm;
    for(auto x:p )
        mm.insert(x);
    cout<<"in order    :";
    mm.print_mid(xx);
    //mm.erfen(5);
    mm.print_anhang();
    //mm.print_tree();
    cout<<"remove "<<p[7]<<endl;
    mm.remove(p[7]);
    mm.print_anhang();
    //cout<<xx;
    return 0;
}
