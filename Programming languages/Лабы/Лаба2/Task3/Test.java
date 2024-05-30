package com.company;

public class Test {
    public static void main (String[] args){
        Complex p = new Complex(3.0, -2.0);
        Complex n = new Complex(2.0, 8.0);
        System.out.println(Complex.Sum(p,n));
        System.out.println(Complex.Difference(p,n));
        System.out.println(Complex.Multiplication(p,n));
        System.out.println(Complex.Division(p,n));
    }
}

