#include<bits/stdc++.h>
using namespace std;
using LL=long long;

class heap{//big root example
    private:
    int n;
    int* a;
    public:
    heap(int nsize){
        a=new int [nsize];
        n=0;
    }
    ~heap(){delete[] a;}
    void up(int p){
        while(p>1){
            if(a[p]>a[p/2]){//big root failed
                swap(a[p],a[p/2]);
                p/=2;
            }else{
                break;
            }
        }
    }
    void insert(int val){
        a[++n]=val;
        up(n);
    }
    void down(int p){
        int son=p*2;//point to left child
        while(son<=n){//in legal area
            if(son<n&&a[son]<a[son+1]){
                ++son;
            }//choose lchild or right child

            if(a[son]>a[p]){
                //!fail to adapt to big root!
                swap(a[son],a[p]);
                p=son;son=2*p;
                //update
            }else{
                break;
            }
        }
    }
    void extract(){
        a[1]=a[n--];
        down(1);
    }
    int getTop(){
        return a[1];
    }
    void remove(int k){
        a[k]=a[n--];
        up(k),down(k);
    }
};


int main(){
#ifdef LOCAL
freopen("in.txt","r",stdin);
freopen("out.txt","w",stdout);
#endif
    
}