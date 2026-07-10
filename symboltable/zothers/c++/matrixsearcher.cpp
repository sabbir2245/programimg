#include <iostream>
using namespace std;

void searchinmatrix(int a[][4], int rows ,int cols , int target ){
int i = 0 ;
int j = cols -1 ;

while (i <rows && j >= 0 ){
    if (a[i][j]== target ){
        cout<< "the element found in the positon is : "<< i+1 << " ,"<< j+1 <<endl;
        return ;    }


if (a[i][j]> target ){
    j-- ;

}
else {
    i++ ;
}


}
cout<< "element not found";

}
int main(){
int matrix[][4]= {  {23 , 15 , 14 , 39 },
                    {18 , 25 , 34 , 33},
                    {25 , 28 , 37 , 48 },
                    {30 , 34 , 39 , 50 }};

 int rows = 4;
 int cols = 4 ;
 int target = 25 ;

 cout << "the matrix is "<<endl;

 for (int i = 0 ;i < rows ;i++ ){
    for(int j =0 ; j < cols ; j ++){
        cout<< matrix[i][j] << " ";
    }
    cout<<endl;
 }                   
searchinmatrix(matrix,rows , cols , target);

}





