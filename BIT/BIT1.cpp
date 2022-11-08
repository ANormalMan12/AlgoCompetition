#include<bits/stdc++.h>
using namespace std;
#ifdef LOG
ofstream lout("log.txt");
#endif
//-----------------------------------
#define endl '\n'
using LL=long long;

inline LL lowbit(LL x){
    return x&(-x); 
}
#define BITSIZE 500005
class BIT{
    public:
    LL tr[BITSIZE];
    LL n;
    void init(LL newn){
        memset(tr,0,sizeof(tr));
        n=newn;
    }
    LL sum(LL x){
        LL ret=0;
        while(x>0){
            ret+=tr[x];
            x-=lowbit(x);
        }
        return ret;
    }
    void add(LL x,LL d){
        while(x<=n){
            tr[x]+=d;
            x+=lowbit(x);
        }
    }
};


BIT aBIT;

void solve(){
    
    LL n;
    cin>>n;
    aBIT.init(n);
    LL d;
    for(LL in=1;in<=n;++in){
        cin>>d;
        aBIT.add(in,d);
    }
    LL q,order,t1,t2;
    cin>>q;
    for(LL iq=1;iq<=q;++iq){
        cin>>order>>t1>>t2;
        if(order==1){
            aBIT.add(t1,t2);
        }else if(order==2){
            cout<<aBIT.sum(t2)-aBIT.sum(t1-1)<<'\n';
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
    return 0;
}