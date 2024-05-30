package com.company;

public class Complex {
    private double real_part;
    private double imag_part;

    public Complex(double real_part, double imag_part){
        setReal_and_Imag(real_part, imag_part);
    }

    public double getReal_part() {
        return real_part;
    }

    public double getImag_part() {
        return imag_part;
    }

    public void setReal_and_Imag(double real, double imag) {
        this.real_part = real;
        this.imag_part = imag;
    }

    public static Complex Sum(Complex numb1, Complex numb2){
        return new Complex(numb1.getReal_part()+numb2.getReal_part(), numb1.getImag_part()+ numb2.getImag_part());
    }

    public static Complex Difference(Complex numb1, Complex numb2){
        return new Complex(numb1.getReal_part()-numb2.getReal_part(), numb1.getImag_part()- numb2.getImag_part());
    }

    public static Complex Multiplication(Complex numb1, Complex numb2){
        return new Complex(((numb1.getReal_part()*numb2.getReal_part())+(-(numb1.getImag_part()* numb2.getImag_part()))),
                (numb1.getReal_part()* numb2.getImag_part())+(numb1.getImag_part()* numb2.getReal_part()));
    }

    public static Complex Division(Complex numb1, Complex numb2){
        return new Complex(((numb1.getReal_part()*numb2.getReal_part())+(-(numb1.getImag_part()* (-numb2.getImag_part())))) / ((numb1.getReal_part()* numb1.getReal_part())-((numb2.getImag_part() * (-numb2.getImag_part())))),
                (numb1.getReal_part()* numb2.getImag_part()+(numb1.getImag_part()* numb2.getReal_part())) / ((numb1.getReal_part()* numb1.getReal_part())+(-(numb2.getImag_part() * numb2.getImag_part()))));
    }

    public String toString() {
        String str = "";

        str += real_part;
        if (imag_part != 0) {
            str += imag_part > 0 ? " + " : " - ";
            str += Math.abs(imag_part) + "i";
        }
        return str;
    }

}
