package zzjavapractice;

<<<<<<< HEAD
=======
import M;

>>>>>>> f58129b (dad)
class M {

    static int v;

    M() {
        v = 0;
    }

  void f1() {

        for (int i = 0; i < 5; i++) {
            v++;
            System.out.println("f1 is ope  " + v);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {

                e.printStackTrace();
            }
        }
    }

  void f2() {
        for (int i = 0; i < 5; i++) {
            v = v * 2;
            System.out.println("f2 is now  " + v);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {

                e.printStackTrace();
            }
        }
    }
}

public class basicthread {

    public static void main(String[] args) {
        M obj = new M();

        Runnable task = obj::f1;
        Runnable task2 = obj::f2;

        Thread t1 = new Thread(task);
        t1.start();
        Thread t2 = new Thread(task2);
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

}

//alternative main function

// M obj = new M();

// new Thread(obj::f1).start();
// new Thread(obj::f2).start();
// }