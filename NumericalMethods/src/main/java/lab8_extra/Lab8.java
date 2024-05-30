package lab8_extra;

import java.util.Arrays;

class Complex {
    private double real;
    private double im;

    public Complex(double real, double im) {
        this.real = real;
        this.im = im;
    }

    public Complex add(Complex other) {
        return new Complex(this.getReal() + other.getReal(), this.getIm() + other.getIm());
    }

    public Complex subtract(Complex other) {
        return new Complex(this.getReal() - other.getReal(), this.getIm() - other.getIm());
    }

    public Complex multiply(Complex other) {
        return new Complex(this.getReal() * other.getReal() - this.getIm() * other.getIm(),
                this.getReal() * other.getIm() + this.getIm() * other.getReal());
    }

    public double getReal() {
        return real;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public double getIm() {
        return im;
    }

    public void setIm(double im) {
        this.im = im;
    }
}

class FFT {
    //Быстрое преобразование Фурье
    public static Complex[] custom_fft(Complex[] inputList) {
        int n = inputList.length;
        if (n <= 1) {
            return inputList;
        }

        Complex[] even = custom_fft(getEven(inputList));
        Complex[] odd = custom_fft(getOdd(inputList));

        Complex[] result = new Complex[n];
        double angle = -2.0 * Math.PI / n;
        for (int k = 0; k < n / 2; k++) {
            Complex t = new Complex(Math.cos(angle * k), Math.sin(angle * k)).multiply(odd[k]);
            result[k] = even[k].add(t);
            result[k + n / 2] = even[k].subtract(t);
        }
        return result;
    }

    //Обратное быстрое преобразование Фурье
    public static Complex[] custom_ifft(Complex[] inputList) {
        Complex[] complexes = new Complex[inputList.length];
        for (int i = 0; i < inputList.length; i++) {
            complexes[i] = new Complex(inputList[i].getReal(), -inputList[i].getIm());
        }
        Complex[] transformed = custom_fft(complexes);
        Complex[] scaledByIfft = new Complex[transformed.length];
        for (int i = 0; i < transformed.length; i++) {
            scaledByIfft[i] = new Complex(transformed[i].getReal() / transformed.length, -transformed[i].getIm() / transformed.length);
        }
        return scaledByIfft;
    }

    private static Complex[] getEven(Complex[] inputList) {
        Complex[] even = new Complex[inputList.length / 2];
        for (int i = 0; i < even.length; i++) {
            even[i] = inputList[i * 2];
        }
        return even;
    }

    private static Complex[] getOdd(Complex[] inputList) {
        Complex[] odd = new Complex[inputList.length / 2];
        for (int i = 0; i < odd.length; i++) {
            odd[i] = inputList[i * 2 + 1];
        }
        return odd;
    }
}
class InterpolatedFunction {
    public static double interpolation(double[] inputList, int numPoints, double x) {
        int n = inputList.length;
        Complex[] complexInput = new Complex[n];
        for (int i = 0; i < n; i++) {
            complexInput[i] = new Complex(inputList[i], 0);
        }

        Complex[] fftResult = FFT.custom_fft(complexInput);
        Complex[] extendedFFT = new Complex[numPoints];
        for (int i = 0; i < n / 2; i++) {
            extendedFFT[i] = fftResult[i];
            extendedFFT[numPoints - n / 2 + i] = fftResult[n / 2 + i];
        }

        Complex[] interpolatedComplex = FFT.custom_ifft(extendedFFT);
        return interpolatedComplex[(int)(x * numPoints) % numPoints].getReal();
    }

    public static double f(double x) {
        return -Math.abs(x - 0.5);
    }
}

public class Lab8 {
    public static void main(String[] args) {
        int N = 128;
        double[] inputFunctionValues = new double[N];
        for (int i = 0; i < N; i++) {
            inputFunctionValues[i] = InterpolatedFunction.f((double)i / N);
        }

        double[] midValues = new double[N];
        double[] interpolationMidValues = new double[N];
        for (int i = 0; i < N; i++) {
            midValues[i] = InterpolatedFunction.f((i + 0.5) / N);
            interpolationMidValues[i] = InterpolatedFunction.interpolation(inputFunctionValues, N, (i + 0.5) / N);
            System.out.println("i: " + i + " , " + "Значение в средней точках: " + midValues[i] + " , " + "Интерполированое значение: " + interpolationMidValues[i]);
        }

        double[] error = new double[N];
        for (int i = 0; i < N; i++) {
            error[i] = Math.abs(midValues[i] - interpolationMidValues[i]);
        }
        System.out.println("Максимальная погрешность в средних точках всех отрезков разбиения: " + Arrays.stream(error).max().getAsDouble());
    }
}
