package myes;

public class C {
    void m(C x) {
        System.out.println("C(C)");
    }

    void m(S x) {
        System.out.println("C(S)");
    }
}
