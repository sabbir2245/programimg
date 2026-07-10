#include<iostream>
using namespace std;

void matrixin(double **matrix , int rows , int cols ){
    for(int i =0 ; i < rows ; i++){
        for(int j =0 ; j <cols ; j ++){
            cout<< "enter element no :" << i+1<< "," <<j+1 <<endl;
            cin>> matrix[i][j];

        }
    }

}

void addmatrix(double **matrix1 ,double **matrix2 ,double **result, int rows , int cols ){
     for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix1[i][j]+ matrix2[i][j];}
     }
}

void submatrix(double **matrix1 ,double **matrix2 ,double **result, int rows , int cols ){
     for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix1[i][j]- matrix2[i][j];}
     }
}

void multimatrix(double **matrix1 ,double **matrix2 ,double **result, int rows1 , int cols1,int cols2){
    for (int i = 0; i < rows1; i++){
        for (int j = 0; j < cols2; j++){ 
            result[i][j]= 0 ;
            for(int k = 0 ; k<cols1;k++){
                result[i][j] += matrix1[i][j] *matrix2[i][j] ;
            }
    
        }
    }
    
}
void printmatrix (double **matrix, int rows , int cols ){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout<< matrix[i][j]<< " ";
        }

            cout<< endl;
    }
}

int main (){
    int rows , cols ;
cout<< " enter number of rows :"<<endl; 
cin>> rows ;
cout<< " enter number of columns :"<<endl;
cin>> cols ; 

double **matrix1 =new double *[rows];
for(int i = 0 ; i<rows;i++){
    matrix1[i] = new double [cols];
}
double **matrix2 =new double *[rows];
for(int i = 0 ; i<rows;i++){
    matrix2[i] = new double [cols];
}

double **result =new double *[rows];
for(int i = 0 ; i<rows;i++){
    result[i] = new double [cols];
}


cout<<"enter first matrix"<<endl;

matrixin(matrix1,rows,cols);
cout<<"enter second matrix"<<endl;
matrixin(matrix2,rows,cols);

addmatrix(matrix1,matrix2,result,rows,cols);
cout << "Matrix Addition Result:\n";

printmatrix(result,rows,cols);

submatrix(matrix1,matrix2,result,rows,cols);
cout << "Matrix substraction Result:\n";


printmatrix(result,rows,cols);

   for (int i = 0; i < rows; ++i) {
        delete[] matrix1[i];
        delete[] matrix2[i];
        delete[] result[i];
    }
    delete[] matrix1;
    delete[] matrix2;
    delete[] result;



return 0 ; 
}
