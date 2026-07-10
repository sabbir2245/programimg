<<<<<<< HEAD
interface Alpha
{
=======
interface Alpha {
>>>>>>> f58129b (dad)
    default void reset() {
        System.out.println("Alpha's reset");
    }
}

<<<<<<< HEAD
interface Beta //extends Alpha
=======
interface Beta 
>>>>>>> f58129b (dad)
{
    default void reset() {
        System.out.println("Beta's reset");
    }
}
<<<<<<< HEAD
public class InterfaceMultipleInheritanceTest implements Alpha, Beta {
=======

class MYY implements Alpha, Beta {
>>>>>>> f58129b (dad)

    public void reset() {
        System.out.println("My reset");
    }
}
<<<<<<< HEAD
=======

public class InterfaceMultipleInheritanceTest {

    public static void main(String[] args) {

        MYY obj = new MYY();
        obj.reset();

    }
}
>>>>>>> f58129b (dad)
