package com.company;
import java.lang.Iterable;
import java.util.Iterator;

public class GcdList implements Iterable<Integer>{
    private int[] s;

    public GcdList(int ... s) {
        this.s = s;
    }

    public int[] getS() {
        return s;
    }

    public void setS(int[] s) {
        this.s = s;
    }

    public Iterator<Integer> iterator(){
        return new GcdIterator();
    }

    private class GcdIterator implements Iterator<Integer>{
        private int pos = 0;
        private int cursor = 1;

        public GcdIterator() {}

        private int getGCD(int num1, int num2) {
            int f = Math.min(num1,num2);
            int max = 0;
            for (int i = 1; i < f+1; i++) {
                if (num1 % i==0 && num2 % i==0){
                    if (i > max){
                        max = i;
                    }
                }
            }
            return max;
        }

        @Override
        public boolean hasNext() {
            return cursor < s.length;
        }

        @Override
        public Integer next() {
            return getGCD(s[pos++], s[cursor++]);
        }
    }
}
