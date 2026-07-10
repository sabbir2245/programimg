#include<iostream>
using namespace std;

class abstractEmployee{
    virtual void askforPromotion()=0 ;
};
class employee:abstractEmployee{
private:
int age ;
string name ;
string company;
 
public:
void setage(int x  ){
    if(x> 17)
    age = x; 
}
int getage(){ 
    return age; 
}
void setname(string ne ){
    name = ne;
}
string getname(){
    return name; 
}
void setcom(string me ){
    company = me ; 
}
string getcom(){
    return company; 
}


void intro(){
    cout<< age<<name << company<< endl;
}
employee(int v , string u , string i ){
    age = v ;
    name = u;
    company = i ;
}
void askforPromotion(){
    if(age>30)
        cout<<name << " got promoted ";
        else{
            cout<< name << " sorry ";
        }
}


};

int main(){  
employee mason = employee(25,"  jony ", "samsung");

mason.intro();
mason.setname("rakib");
mason.setage(24);
cout<< mason.getname()<< " is "<< mason.getage()<< " years old ";
mason.askforPromotion();
return 0 ; 
}
