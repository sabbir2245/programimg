package Java.basic_class;

<<<<<<< HEAD
import Java.basic_class.OuterClass.InnerClass;

=======
>>>>>>> f58129b (dad)
class OuterClass {
    private String outerField = "Outer Field";
    private static String staticField = "Static Field"; 

    public void display66(){
        System.out.println("basic ");
    }

    //basic innerclass

    class InnerClass {
        void display() {
            System.out.println("This is the inner class, accessing: " + outerField);
        }
    }

    void createInner() {
        InnerClass inner = new InnerClass();  // Create instance of inner class
        inner.display();
    }

    //static nested class 
    static class StaticNestedClass {
        void display() {
            System.out.println("This is the static nested class, accessing: " + staticField);
        }
    }

    //local inner class 
    void display3() {
        class LocalInnerClass {
            void show() {
                System.out.println("This is a local inner class");
            }
        }

        LocalInnerClass localInner = new LocalInnerClass();  // Local to the method
        localInner.show();
    }



}

public class InnerClassExample {
    public static void main(String[] args) {
        OuterClass outer = new OuterClass();
        outer.createInner();  // Calling method that creates inner class instance

  //  InnerClass c = new InnerClass() ;  error
   // c.display();

   OuterClass.InnerClass inne = outer.new InnerClass() ; 
   inne.display();
    
   
        OuterClass.StaticNestedClass nested = new OuterClass.StaticNestedClass();
        nested.display();  // Calling method of static nested class
        

        outer.display3();


        //anonnmouse inner class 

        OuterClass outer4 = new OuterClass(){

            public void display66(){
                System.out.println("annonymous inner class ");
            }

        };

        outer4.display66();
      

    
    }
}
