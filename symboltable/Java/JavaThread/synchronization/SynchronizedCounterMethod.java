package synchronization;

class SharedCounter1 {
    private int counter;

    SharedCounter1() {
        this.counter = 0;
    }

    public synchronized void increment() {
        this.counter++;
    }

    public int get() {
        return this.counter;
    }

    void count() {
        for (int i = 0; i < 10000; i++) {
            increment();
        }
    }
}

class ThreadCounterSyncMethod implements Runnable {
    SharedCounter1 sharedCounter;
    Thread t;

    public ThreadCounterSyncMethod(SharedCounter1 s, String name) {
        sharedCounter = s;
        t = new Thread(this, name);
        t.start();
    }

    public void run() {
        sharedCounter.count();
    }
}

public class SynchronizedCounterMethod {
    // public static void main(String[] args) {
    // SharedCounter1 sharedCounter = new SharedCounter1();
    // ThreadCounterSyncMethod ob1 = new ThreadCounterSyncMethod(sharedCounter,
    // "T1");
    // ThreadCounterSyncMethod ob2 = new ThreadCounterSyncMethod(sharedCounter,
    // "T2");
    // ThreadCounterSyncMethod ob3 = new ThreadCounterSyncMethod(sharedCounter,
    // "T3");
    // try {
    // ob1.t.join();
    // ob2.t.join();
    // ob3.t.join();
    // } catch (Exception e) {
    // System.out.println(e);
    // }
    // System.out.println(sharedCounter.get());
    // }

    
    public static void main(String[] args) {
        SharedCounter1 sh = new SharedCounter1();
      
        Runnable task = sh::count;

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
          
            e.printStackTrace();
        }
      
        
        System.out.println(sh.get());
    }
}
