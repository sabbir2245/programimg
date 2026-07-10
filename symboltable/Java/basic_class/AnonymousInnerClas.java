package Java.basic_class;

//annonymoous inner class can be of a normal class , interface , abstacrt class

interface Greeting {
    void sayHello();
}

class A {
    void show() {
        System.out.println("in original A class ");
    }
}

abstract class Vehicle{ 

    public abstract void drive() ;
    public abstract void refilloil() ;
    public void playmusic(){
        System.out.println("da ,  da na na na ");
    }
}





public class AnonymousInnerClas {
    public static void main(String[] args) {


        Greeting greeting = new Greeting() { // Anonymous inner class implementing Greeting
            @Override
            public void sayHello() {
                System.out.println("Hello from Anonymous Inner Class!");
            }
        };
        greeting.sayHello(); // Calling method of anonymous inner class


        A obj = new A(){
            //modifying A's show method without creating drived class
            public void show(){
                System.out.println("in  Annony inner  class ");
    
            } ; 

        };
        obj.show();


//        Vehicle ve = new Vehicle(); // not possible to createa instance of abtract class 
//but

        Vehicle ve = new Vehicle() {

            @Override
            public void drive() {
                System.out.println("driving ");
               
            }

            @Override
            public void refilloil() {
                System.out.println("refiling aoil ");
                   
            }
            
        };

        ve.drive();
        ve.refilloil();
        ve.playmusic() ; 




    }

}
