
class SharedBuffer {

    private final int MAX_SIZE = 5;
    int current = 3;

    public synchronized void produce() throws InterruptedException {
        while (current == MAX_SIZE) {
            wait();
        }
        current++;
        System.out.println("Produced: ");
        notify();
    }

    public synchronized void consume() throws InterruptedException {
        while (current == 0) {
            wait();
        }
        current--;
        System.out.println("Consumed: ");
        notify();

    }
}

class Producer extends Thread {
    private SharedBuffer buffer;

    public Producer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        try {
            for (int i = 0; i < 10; i++) {
                buffer.produce();
                Thread.sleep(1000);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Consumer extends Thread {
    private SharedBuffer buffer;

    public Consumer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        try {
            for (int i = 0; i < 10; i++) {
                buffer.consume();
                Thread.sleep(1500); // Simulate time to consume an item
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class ProducerConsumer {
    public static void main(String[] args) {
        SharedBuffer buffer = new SharedBuffer();
        Producer producer = new Producer(buffer);
        Consumer consumer = new Consumer(buffer);

        // runnable 

        // if Producer and consumer implemneted runnabel 
        // Thread producerThread = new Thread(new Producer(buffer));
        // Thread consumerThread = new Thread(new Consumer(buffer));
        // producerThread.start();
        // consumerThread.start();


        // lambda expression
        // Thread producerThread = new Thread(() -> {
        //     try {
        //         for (int i = 0; i < 10; i++) {
        //             buffer.produce();
        //             Thread.sleep(1000); // Simulate time to produce an item
        //         }
        //     } catch (InterruptedException e) {
        //         e.printStackTrace();
        //     }
        // });
        
        // Thread consumerThread = new Thread(() -> {
        //     try {
        //         for (int i = 0; i < 10; i++) {
        //             buffer.consume();
        //             Thread.sleep(1500); // Simulate time to consume an item
        //         }
        //     } catch (InterruptedException e) {
        //         e.printStackTrace();
        //     }
        // });



        

        producer.start();
        consumer.start();
    }
}
