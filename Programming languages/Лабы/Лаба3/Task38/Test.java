package com.company;
import java.util.Arrays;

public class Test {
    public static void main(String[] args) {
        DivisionByComma[] a = new DivisionByComma[]{
                new DivisionByComma("aaa,abac jdsfjldf djfj effsd"),
                new DivisionByComma("ab,jldjlf,djflsdkj df dljksflj"),
                new DivisionByComma("alhah hg,f,f,f,df,d"),
                new DivisionByComma("a")
        };
        Arrays.sort(a);
        for (DivisionByComma s : a) System.out.println(s);
    }
}

