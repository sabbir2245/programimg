
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

class cv implements Runnable {

    int s;
    int y;

    cv(int sa, int uu) {
        s = sa;
        y = uu;

    }

    public void run() {
        M obj = new M();
        obj.printprime(s, y);
    }
}

public class primethread22 {

    public static void main(String[] args) {

        cv r1 = new cv(1, 45);
        cv r2 = new cv(55, 100);

        Thread t1 = new Thread(r1);
        Thread t2 = new Thread(r2);

        // alternatively
        // Thread t1 = new Thread( new cv(1, 45));
        // Thread t2 = new Thread(new cv(55, 100));


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
