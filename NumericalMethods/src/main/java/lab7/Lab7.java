package lab7;

public class Lab7 {
    private static final double eps = 0.001;
    static double f(double x) {
        return (2) * Math.pow(x, 3) + (3) * Math.pow(x, 2) + (-26) * x + (4);
    }

    static double df(double x) {
        return 6 * Math.pow(x, 2) + (6) * x + (-26);
    }

    static double df2(double x) {
        return 12 * x + 6;
    }

    public static void divideOnHalf(double a, double b) {
        double x;
        double a1 = a;
        double b1 = b;
        int k = 0;
        while (b1 - a1 > 2 * eps) {
            x = (a1 + b1) / 2;
            if (f(a) * f(x) < 0) {
                b1 = x;
            } else {
                a1 = x;
            }
            k++;
        }
        System.out.println("\tRoot: " + (a1 + b1) / 2);
        System.out.println("\tNum of steps: " + k);
    }

    public static double sgn(double x) {
        if (x > 0) {
            return 1;
        }
        else if (x == 0) {
            return 0;
        }
        else {
            return -1;
        }
    }

    public static void newtonMethod(double a, double b) {
        double x0;
        double x1;
        if (f(a) * df2(a) > 0) {
            x0 = a;
        } else {
            x0 = b;
        }
        int k = 0;
        while (true) {
            x1 = x0 - (f(x0) / df(x0));
            k++;
            if ((f(x1) * f(x1 + sgn(x1 - x0) * eps)) < 0) {
                break;
            }
            x0 = x1;
        }
        System.out.println("\tRoot: " + x1);
        System.out.println("\tNum of steps: " + k);
    }

    public static void main(String[] args) {
        System.out.println("DivideOnHalf method:");
        divideOnHalf(-10.0, 10.0);

        System.out.println("Newton method:");
        newtonMethod(-10.0, 10.0);
    }
}
