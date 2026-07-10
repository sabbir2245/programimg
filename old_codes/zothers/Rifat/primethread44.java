import java.util.concurrent.*;

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
                System.out.println("Prime is: " + i);
            }
        }
    }
}

public class primethread44 {

    public static void main(String[] args) {
        // Create a fixed thread pool with 2 threads
        ExecutorService exe = Executors.newFixedThreadPool(2);

        M obj = new M();

        // Submit tasks to the executor service
        exe.submit(() -> obj.printprime(1, 45));   // Task 1
        exe.submit(() -> obj.printprime(55, 100)); // Task 2

        // Shutdown the executor service after tasks are submitted
        exe.shutdown();

        try {
            // Wait for the completion of all tasks
            if (!exe.awaitTermination(60, TimeUnit.SECONDS)) {
                exe.shutdownNow();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
            exe.shutdownNow();
        }
    }
}
 