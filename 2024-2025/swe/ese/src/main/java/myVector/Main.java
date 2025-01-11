package myVector;


public class Main {
    public static void main(String Args[]) {
        Vector<Integer> v = new Vector<>(1);
        v.push(1);
        v.push(2);
        v.push(3);
        v.push(4);
        v.push(5);
        System.out.println(v);

        Vector<Double> w = new Vector<>(1);
        w.push(1.);
        w.push(2.);
        w.push(3.);
        w.push(4.);
        w.push(5.);
        System.out.println(w);
    }
}
