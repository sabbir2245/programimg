
#include <bits/stdc++.h>
using namespace std;
int binary(vector<int>& arr , int target ){
int left = 0 ;
int right = arr.size()-1 ;
while (left<=right)
{ 
  int mid = left+(right-left)/2;
  if(arr[mid]==target){
    return mid ; 
  }
  else if(arr[mid]<=target){
    left= mid+1 ; 
  }
  else if(arr[mid]>=target){

      right= mid-1 ; }
}

return -1 ; 
}


int main() {
    vector<int> arr= {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int target = 4 ; 

    int result= binary(arr,target);

    if(result!= -1 ){
      cout<<"Element found at index :"<<result<<endl ; 
    }
    else
    {
      cout<<"Element found not "<< endl ; 
    }
    

}
