package lab5;

import java.lang.Math;

public class DifferentialEquationSolution {
    public static double[] solution(double[] b, double[] a, double[] c, double[] d, int size) {
        double[] alpha = new double[size];
        double[] beta = new double[size];
        alpha[0] = -c[0] / b[0];
        beta[0] = d[0] / b[0];
        double y;
        for (int i = 1; i < size - 1; i++) {
            y = a[i - 1] * alpha[i - 1] + b[i];
            alpha[i] = -c[i] / y;
            beta[i] = (d[i] - a[i - 1] * beta[i - 1]) / y;
        }
        y = a[size - 2] * alpha[size - 2] + b[size - 1];
        beta[size - 1] = (d[size - 1] - a[size - 2] * beta[size - 2]) / y;

        double[] x = new double[size];
        x[size - 1] = beta[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            x[i] = alpha[i] * x[i + 1] + beta[i];
        }
        return x;
    }

    //2*Math.pow(Math.E,x)
    //2
    public static double f(double x) {
        return 2;
    }

    //Math.pow(Math.E,x)
    //((double) 1 / 15) * (12 * Math.exp(-2 * x) + 8 * Math.exp(3 * x) - 5)
    public static double analytical(double x) {
        return ((double) 1 / 15) * (12 * Math.exp(-2 * x) + 8 * Math.exp(3 * x) - 5);
    }

    public static void main(String[] args) {
        int n = 10;
        double p = -1.0; // 5.0
        double q = -6.0; // -4.0
        double a = analytical(0);
        double b = analytical(1);

        double h = 1.0 / n;
        double[] xs = new double[n + 1];
        for (int i = 0; i < n + 1; i++) {
            xs[i] = i * h;
        }

        double[] aArr = new double[n - 2];
        for (int i = 1; i < n - 1; i++) {
            aArr[i - 1] = 1 - h / 2 * p;
        }
        double[] bArr = new double[n - 1];
        for (int i = 1; i < n; i++) {
            bArr[i - 1] = h * h * q - 2;
        }
        double[] cArr = new double[n - 2];
        for (int i = 1; i < n - 1; i++) {
            cArr[i - 1] = 1 + h / 2 * p;
        }
        double[] dArr = new double[n - 1];
        dArr[0] = h * h * f(0) - a * (1 - h / 2 * p);
        for (int i = 2; i < n; i++) {
            dArr[i - 1] = h * h * f(i*h);
        }
        dArr[n - 2] = h * h * f((dArr.length - 1) * h) - b * (1 + h / 2 * p);

        double[] ys = new double[n + 1];
        ys[0] = a;
        double[] solution = solution(bArr, aArr, cArr, dArr, n - 1);

//        for (int i = 0; i < solution.length; i++) {
//            ys[i + 1] = solution[i];
//        }
        System.arraycopy(solution, 0, ys, 1, solution.length);
        ys[n] = b;

        for (int i = 0; i < ys.length; i++) {
            System.out.printf("x=%.1f, y_analytical=%.6f, y_my=%.6f |y_analytical-y_my*|=%.6f\n",
                    xs[i], analytical(xs[i]), ys[i], Math.abs(ys[i] - analytical(xs[i])));
        }
    }
}
