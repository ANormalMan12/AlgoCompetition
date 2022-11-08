#include<bits/stdc++.h>
using namespace std;
#ifdef LOG
ofstream lout("log.txt");
#endif
//-----------------------------------
#define endl '\n'
using LL=long long;

#define ELESIZE 500100

#define LCHILD (pos*2)
#define RCHILD (pos*2+1)
#define pL a[pos].l
#define pR a[pos].r
#define ROOT 1

#define NoVal LLONG_MIN
#define pDC a[pos].dC
#define pSum a[pos].sum
#define pMin a[pos].min
#define pMax a[pos].max
#define pSet a[pos].reset

struct qRes{
    LL sum,min,max;
};

class segTree{//point type
    private:
    struct Cnode{
        int l,r;
        LL dC,sum;
        LL reset,min,max;
    };
    Cnode a[4*ELESIZE];

    public:
    segTree(){
        memset(a,0,4*ELESIZE*sizeof(a[0]));
    }
    void build(int pos,int l,int r){
        if(l<=r){
            pL=l;pR=r;
            pDC=pSum=0;//重置待维护信息
            pMin=pMax=0;
            pSet=NoVal;

            if(l!=r){
                build(LCHILD,l,(l+r)/2);
                build(RCHILD,(l+r)/2+1,r);
            }
        }
    }
    //pos points to the position
    void down(int pos,int Cl,int Cr,LL up,LL reset){
        //-----------Exactly match----------------------------
        if(pL==Cl&&pR==Cr){
            if(reset==NoVal){//上方不打算reset值
                if(pSet!=NoVal){//将现结点set值转化为正常值
                    //pSum=(pR-pL+1)*pSet;//,pSum,pMin,pMax has been changed before
                    //pDC=0;
                    int mid=(pL+pR)/2;
                    if(pL!=pR){
                        down(LCHILD,pL,mid,0,pSet);//内容下沉
                        down(RCHILD,mid+1,pR,0,pSet);
                    }
                    pSet=NoVal;
                }//处理正常值
                pDC+=up;
                pSum+=up*(pR-pL+1);
                pMin+=up;
                pMax+=up;
            }else{
                pDC=0;
                pMin=pMax=pSet=reset;
                pSum=(pR-pL+1)*reset;
            }
            return;
        }
        int mid=(pL+pR)/2;
        //-----------下沉懒惰结点---------------
        if((pDC!=0||pSet!=NoVal)&&pL!=pR){
            down(LCHILD,pL,mid,pDC,pSet);
            down(RCHILD,mid+1,pR,pDC,pSet);
        }
        pDC=0;
        pSet=NoVal;
        //-----------下沉待维护信息----------------------------
        if(Cr<=mid){
            down(LCHILD,Cl,Cr,up,reset);//To left
        }else if(Cl>mid){
            down(RCHILD,Cl,Cr,up,reset);//To right
        }else{
            down(LCHILD,Cl,mid,up,reset);
            down(RCHILD,mid+1,Cr,up,reset);
        }
        //---------回溯更新上方结点信息-----------------------
        pMax=a[LCHILD].max>a[RCHILD].max?a[LCHILD].max:a[RCHILD].max;
        pMin=a[LCHILD].min<a[RCHILD].min?a[LCHILD].min:a[RCHILD].min;
        pSum=a[LCHILD].sum+a[RCHILD].sum;
    }
    qRes Query(int pos,int Ql,int Qr){//点型
        //-----------Exacly match-----------------------
        if(pL==Ql&&pR==Qr){
            return {pSum,pMin,pMax};
        }
        //-----------下沉懒结点数据---------------------------
        int mid=(pL+pR)/2;
        if((pDC!=0||pSet!=NoVal)&&pL!=pR){
            down(LCHILD,pL,mid,pDC,pSet);
            down(RCHILD,mid+1,pR,pDC,pSet);
        }
        pDC=0;
        pSet=NoVal;
        //------------递归查找-------------------------------   
        if(Qr<=mid){
            return Query(LCHILD,Ql,Qr);
        }else if(Ql>mid){
            return Query(RCHILD,Ql,Qr);
        }else{
            qRes lres=Query(LCHILD,Ql,mid);
            qRes rres=Query(RCHILD,mid+1,Qr);
            qRes ret={lres.sum+rres.sum,
                      lres.min<rres.min?lres.min:rres.min,
                      lres.max>rres.max?lres.max:rres.max};
            return ret;
        }
    }
    void printRecu(int pos){
        cout<<'['<<pL<<','<<pR<<']';
        cout<<'('<<pDC<<','<<pSum<<','<<pMin<<','<<pMax<<',';
        if(pSet==NoVal){
            cout<<"No";
        }else{
            cout<<pSet;
        }
        cout<<')'<<'\n';
        if(pL!=pR){
            printRecu(LCHILD);
            printRecu(RCHILD);
        }
    }
    void print(){
        cout<<"(pDC,pSum,pMin,pMax,pSet)"<<'\n';
        printRecu(ROOT);
    }
};

segTree tr;

void solve(){
    int n;
    cin>>n;
    int tem;
    tr.build(ROOT,1,n);
    for(int in=1;in<=n;++in){
        cin>>tem;
        tr.down(ROOT,in,in,tem,NoVal);
    }
    #ifdef LOCAL
    tr.print();
    #endif
    LL q,order,l,r,d;
    cin>>q;
    for(int iq=1;iq<=q;++iq){
        cin>>order>>l>>r;
        if(order==1){
            cin>>d;
            tr.down(ROOT,l,r,d,NoVal);
        }else if(order==2){
            cin>>d;
            tr.down(ROOT,l,r,0,d);
        }else{
            auto res=tr.Query(ROOT,l,r);
            //printf("%lld %lld %lld\n",res.sum,res.max,res.min)
            cout<<res.sum<<' '<<res.max<<' '<<res.min<<'\n';
        }
        #ifdef LOCAL
        tr.print();
        #endif
    }
}

int main(){
#ifdef LOCAL
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}