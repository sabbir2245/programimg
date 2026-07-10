package zzjavapractice;

public class ParallelSum {
    
    private static int totalSum = 0;

    // Synchronized method to update the total sum safely
    private synchronized static void addToSum(int value) {
        totalSum += value;
    }

    public static void main(String[] args) throws InterruptedException {
        int numThreads = 5;
        int range = 100000;
        int chunkSize = range / numThreads;

        // Create and start threads
        Thread[] threads = new Thread[numThreads];
        for (int i = 0; i < numThreads; i++) {
            int start = i * chunkSize + 1;
            int end = (i + 1) * chunkSize;

            // Ensure the last thread processes up to the range
            if (i == numThreads - 1) {
                end = range;
            }

            threads[i] = new Thread(() -> {
                for (int j = start; j <= end; j++) {
                    addToSum(j);
                }
            });
            threads[i].start();
        }

        // Wait for all threads to finish
        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Total Sum: " + totalSum);
    }
}