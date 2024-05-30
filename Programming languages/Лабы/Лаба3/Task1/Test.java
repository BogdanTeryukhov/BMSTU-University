package com.company;
import java.util.Arrays;

public class Test {
    public static void main(String[] args){
        MaxCommonDel[] a = new MaxCommonDel[]{
                new MaxCommonDel(15,30),
                new MaxCommonDel(24,36),
                new MaxCommonDel(48,96),
                new MaxCommonDel(154, 226)
        };
        Arrays.sort(a);
        for ( MaxCommonDel s : a ) System .out.println ( s );
    }
}
