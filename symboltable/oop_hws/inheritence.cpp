#include <bits/stdc++.h>

using namespace std;

class Animal
{ protected:
    string name;
    int age;

public:
    Animal(string s, int a) : name(s), age(a) {}

    virtual void makesound()
    {
        cout << "Animal makes a sound" << endl;
    }

    virtual ~Animal() = default ; 
};

class lion : public Animal
{
    public:
    lion(string s , int a ) : Animal(s,a) {}

    void  makesound() override{
        cout<< name << " lion fucking her pussy "<< endl;
    }


};

class zooman{

public :
void pet(Animal * kol){
    kol->makesound() ; 
    
}
};


int main()
{
    cout << "programming atsrted " << endl;

    Animal simp("op" , 22) ; 
    simp.makesound() ;

    lion POLeg ("simba"  , 8) ; 

    POLeg.makesound() ;  

    zooman ali ; 

    ali.pet(&simp) ;

    return 0;
}