
class M {

    boolean isprime(int num) {
        if (num <= 1)
            return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0)
                return false;
        }
        return true;

    }

    public void printprime(int s, int e) {
        for (int i = s; i < e; i++) {
            if (isprime(i)) {
                System.out.println("prime is" + i);
            }
        }
    }
}


class N{

    M obj = new M() ; 
 

    public void printii() {
        for (int i = 3; i < 56; i++) {
            if (obj.isprime(i)) {
                System.out.println("prime is" + i);
            }
        }
    }
}

public class primethread {

    public static void main(String[] args) {

        M obj = new M();

        Thread t1 = new Thread(() -> obj.printprime(1, 50));
        Thread t2 = new Thread(() -> obj.printprime(51, 100));

        // Thread t1 = new Thread(obj::printprime(1,50)) ; //errro
        // Thread t2 = new Thread(obj::printprime(51, 100));//error
        // not possible because it has parameters

        N obj2 = new N() ; 
        Thread t3 = new Thread(obj2::printii) ; 
        Thread t4 = new Thread(obj2::printii) ; 

        t3.start();
        t4.start();


       


        t1.start();
        t2.start();

        try {
            
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
