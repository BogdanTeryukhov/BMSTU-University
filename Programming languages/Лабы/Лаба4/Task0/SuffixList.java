package com.company;
import java.lang.Iterable;
import java.util.Iterator;

public class SuffixList implements Iterable<String>{
    private StringBuilder s;

    public SuffixList(StringBuilder s) {
        this.s = s;
    }

    public StringBuilder getS() {
        return s;
    }

    public void setS(StringBuilder s) {
        this.s = s;
    }

    public Iterator<String> iterator(){
        return  new SuffixIterator();
    }

    private class SuffixIterator implements Iterator<String>{
        private int pos = 0;

        public SuffixIterator(){
            pos = 0;
        }

        @Override
        public boolean hasNext() {
            return pos < s.length();
        }

        @Override
        public String next() {
            return s.substring(pos++,s.length());
        }
    }

}
