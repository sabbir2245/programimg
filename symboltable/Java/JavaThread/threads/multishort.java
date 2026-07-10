
public class  multishort{
    public static void main(String[] args) {
   int[] sum = {0};  // Use array to store sum as it can be updated in threads
    
    
     Runnable task1 = () -> { for (int i = 1; i <= 2500; i++) sum[0] += i; };
        Runnable task2 = () -> { for (int i = 2501; i <= 5000; i++) sum[0] += i; };
        Runnable task3 = () -> { for (int i = 5001; i <= 7500; i++) sum[0] += i; };
        Runnable task4 = () -> { for (int i = 7501; i <= 10000; i++) sum[0] += i; };

        Thread t1 = new Thread(task1);
        Thread t2 = new Thread(task2);
        Thread t3 = new Thread(task3);
        Thread t4 = new Thread(task4);

        t1.start();
        t2.start();
        t3.start();
        t4.start();

        try {
            t1.join();
            t2.join();
            t3.join();
            t4.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread Interrupted");
        }

        System.out.println(sum[0]);  // Output the result
    }
}
