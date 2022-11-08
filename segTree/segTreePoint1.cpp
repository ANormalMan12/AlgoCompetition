#include<bits/stdc++.h>
using namespace std;

#ifdef LOG
ofstream lout("log.txt");
#endif
using LL=long long;

#define ELESIZE 500100

#define LCHILD (pos*2)
#define RCHILD (pos*2+1)
#define pL a[pos].l
#define pR a[pos].r
#define ROOT 1

#define pDC a[pos].dC
#define pSum a[pos].sum

class segTree{//point type
    private:
    struct Cnode{
        int l,r;
        long long dC,sum;
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
            if(l!=r){
                build(LCHILD,l,(l+r)/2);
                build(RCHILD,(l+r)/2+1,r);
            }
        }
    }
    void add(int pos,int Cl,int Cr,long long up){
    //--------------更新待维护信息----------------------------
        if(pL==Cl&&pR==Cr){
            pDC+=up;
            return;
        }
        pSum+=up*(Cr-Cl+1);//在下沉前可以预知更改的情况
    //--------------下沉待维护信息----------------------------
        int mid=(pL+pR)/2;
        if(Cr<=mid){
            add(LCHILD,Cl,Cr,up);//To left
        }else if(Cl>mid){
            add(RCHILD,Cl,Cr,up);//To right
        }else{
            add(LCHILD,Cl,mid,up);
            add(RCHILD,mid+1,Cr,up);
        }
    }
    long long Qsum(int pos,int Ql,int Qr){//点型
        //-----------更新当前节点数据-----------------------
        if(pL==Ql&&pR==Qr){
            return pSum+(pR-pL+1)*pDC;
        }
        pSum+=(pR-pL+1)*pDC;//pDC仅当查询时下沉
        //-----------下沉结点数据---------------------------
        int mid=(pL+pR)/2;
        add(LCHILD,pL,mid,pDC);
        add(RCHILD,mid+1,pR,pDC);
        //更新懒结点
        pDC=0;
        //------------递归查找-------------------------------   
        if(Qr<=mid){
            return Qsum(LCHILD,Ql,Qr);
        }else if(Ql>mid){
            return Qsum(RCHILD,Ql,Qr);
        }else{
            return Qsum(LCHILD,Ql,mid)+
                    Qsum(RCHILD,mid+1,Qr);
        }
    }
};

segTree tr;

void solve(){
    int n;
    cin>>n;
    tr.build(ROOT,1,n);
    int x;
    for(int in=1;in<=n;++in){
        cin>>x;
        tr.add(ROOT,in,in,x);
    }
    int q,order,d,l,r;
    cin>>q;
    for(int iq=0;iq<q;++iq){
        cin>>order>>l>>r;
        if(order==1){
            cin>>d;
            tr.add(ROOT,l,r,d);
        }else if(order==2){
            cout<<tr.Qsum(ROOT,l,r)<<'\n';
        }else{
            cout<<"ERROR";
        }
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
}