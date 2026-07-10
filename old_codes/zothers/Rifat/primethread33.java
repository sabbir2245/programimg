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

    public void printprime(int start, int end) {
        for (int i = start; i < end; i++) {
            if (isprime(i)) {
                System.out.println("Prime is: " + i);
            }
        }
    }
}

// Create a subclass of Thread
class customthread extends Thread {

    int s;
    int y;

    customthread(int sa, int uu) {
        s = sa;
        y = uu;
    }

    @Override
    public void run() {
        M obj = new M();
        obj.printprime(s, y);
    }
}

public class primethread33 {

    public static void main(String[] args) {

        // Create and start threads by directly instantiating customthread
        customthread t1 = new customthread(1, 45);
        customthread t2 = new customthread(55, 100);

        t1.start();
        t2.start();

        try {
            // Wait for both threads to finish
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
