
#include<iostream>
using namespace std;

int main() {
    int n ;
       cin>>n ;

    int ar[n];
    int sum = 0 ;
    for (int i = 0; i < n; i++)
    {
        int y ;
        cin>>y;
         int u , w ;

        cin>>u >> w ;

      

    for (int i = 0; i < y-1; i++){
        int q , l ;
        cin>>q >>l;

        if(q>u && l> w){
           sum++;
        }
        
        } 
        
        if (sum>0)
{
   ar[i]=-1;
}
else
{
   ar[i]=u;
}

        
        }


    

for (int i = 0; i < n; i++) {
        cout << ar[i] << endl;
    }

return 0 ; 
}
