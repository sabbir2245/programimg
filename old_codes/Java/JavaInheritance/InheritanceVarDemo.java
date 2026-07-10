package Java.JavaInheritance;

class AA {
    private int a;

    public AA() {
        a = 10;
    }

    public int getA() {
        return a;
    }

    public void setA(int a) {
        this.a = a;
    }

    public void printClass() {
        System.out.println("AA");
    }
}

class BB extends AA {
    private int b;

    public BB() {
        b = 20;
    }

    public int getB() {
        return b;
    }

    public void setB(int b) {
        this.b = b;
    }

    @Override
    public void printClass() {
        System.out.println("BB");
    }
}

class CC extends BB {
    private int c;

    public CC() {
        c = 30;
    }

    public int getC() {
        return c;
    }

    public void setC(int c) {
        this.c = c;
    }

    @Override
    public void printClass() {
        System.out.println("CC");
    }
}

public class InheritanceVarDemo {
<<<<<<< HEAD
    static AA getObject(int type) {
=======


static AA getObject(int type) {
>>>>>>> f58129b (dad)
        switch (type) {
            case 0:
                return new AA();
            case 1:
                return new BB();
            case 2:
                return new CC();
            default:
                return null;
        }
    }

    public static void main(String[] args) {
        var a = new AA();
        a.printClass(); // AA 
        var b = new BB();
        b.printClass(); // BB
        var c = new CC();
        var r = a;
        r.printClass(); // prints AA
        r = b;
        r.printClass(); // BB
        r = c;
        r.printClass(); // CC

        var x = getObject(0);
        var y = getObject(1);
        var z = getObject(2);

        System.out.println(x.getA());

        // System.out.println(y.getB()); // Error, type of y is AA
        // System.out.println(z.getC()); // Error, type of z is AA

<<<<<<< HEAD
=======
        System.out.println(((BB) y).getB()); 

>>>>>>> f58129b (dad)
        // Correct casting to access subclass methods
        if (y instanceof BB) {
            System.out.println(((BB) y).getB()); // Works because y is actually of type BB
        }

        if (z instanceof CC) {
            System.out.println(((CC) z).getC()); // Works because z is actually of type CC
        }
    }
}
