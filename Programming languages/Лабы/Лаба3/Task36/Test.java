package com.company;
import java.util.Arrays;


public class Test {
    public static void main(String[] args) {
        NVector[] a = new NVector[]{
                new NVector(2.0,5.0,7.0),
                new NVector(23.0,3.0,5.0),
                new NVector(1.0,2.0,3.0)
        };
        Arrays.sort(a);
        for (NVector s : a) System.out.println(s);
    }
}