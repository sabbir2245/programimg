
class NewThread1 implements Runnable {
    Thread t;

    NewThread1() {
        t = new Thread(this);
        t.start();
    }


    // This is the entry point for the thread.
    @Override
    public void run() {
        try {
            for (int i = 100; i > 0; i--) {
                System.out.println("Child Thread: " + i);
                Thread.sleep(1000);
            }
        } catch (InterruptedException e) {
            System.out.println("Child interrupted.");
        }
        System.out.println("Exiting child thread.");
    }
}

public class ImplementsThread {
    public static void main(String[] args) throws Exception {
        NewThread1 ss = new NewThread1(); // alternative : new NewTHred1(); 
       //  ss.t.join();
      
        for (int i = 500; i > 0; i--) {
            System.out.println("Main Thread: " + i);
            Thread.sleep(2000);
        }
    }
}
