
class ParallelMin implements Runnable {
    private int[] array;
    private int start;
    private int end;
    public int minval ; 
 

    public ParallelMin(int[] array, int start, int end) {
        this.array = array;
        this.start = start;
        this.end = end;
        this.minval = Integer.MAX_VALUE ; 
    }

    @Override
    public void run() {
        for (int i = start; i < end; i++) {
            if (array[i] < minval) {
                minval = array[i];
            }
        }

    }
}


    public class Parrallelmin{
    public static void main(String[] args) throws InterruptedException {
        int[] array = new int[1000];
  
        for (int i = 0; i < 1000; i++) {
            array[i] = (int) (Math.random() * 1000); 
        }
         int chunkSize = array.length / 5;
       
        Thread[] threads = new Thread[5];
        ParallelMin[] parallelMins = new ParallelMin[5]; //
        
       
        for (int i = 0; i < 5; i++) {
            int start = i * chunkSize;
            int end = (i == 4) ? array.length : (i + 1) * chunkSize;
            
            parallelMins[i] = new ParallelMin(array, start, end);
            threads[i] = new Thread(parallelMins[i]);
            threads[i].start();
        }

    
        for (int i = 0; i < 5; i++) {
            threads[i].join();
        }

    

        int finalMin = Integer.MAX_VALUE;
        for (int i = 0; i < 5; i++) {
            if (finalMin > parallelMins[i].minval) {
                finalMin = parallelMins[i].minval;
            }
        }

      
        System.out.println("Minimum value in the array: " + finalMin);
    }
}
