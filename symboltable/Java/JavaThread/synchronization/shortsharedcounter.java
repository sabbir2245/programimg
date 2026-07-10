package synchronization;

class SharedCounter {
    private int counter = 0;

    public synchronized void increment() {
        counter++;
    }

    public int get() {
        return counter;
    }

    public void count() {
        for (int i = 0; i < 10000; i++) {
            increment();
        }
    }
}

public class shortsharedcounter {
    public static void main(String[] args) {
        SharedCounter sharedCounter = new SharedCounter();

        Runnable task = () -> sharedCounter.count();

        Thread t1 = new Thread(task);
        Thread t2 = new Thread(task);
        Thread t3 = new Thread(task);

        t1.start();
        t2.start();
        t3.start();

        try {
            t1.join();
            t2.join();
            t3.join();
        } catch (InterruptedException e) {
            System.out.println(e);
        }

        System.out.println(sharedCounter.get());
    }

}
