package myVector;

public class Vector<T> {
    private T inner[];
    private int size;

    public Vector() {
        this(4);
    }

    public Vector(int cap) {
        this.inner = (T[]) new Object[cap];
        this.size = 0;
    }

    public T get(int idx) {
        return inner[idx];
    }

    public int size() {
        return size;
    }

    public void resize(int cap) {
        if (cap == inner.length) {
            return;
        }
        T tmp[] = inner;
        inner = (T[]) new Object[cap];
        size = Integer.min(size, inner.length);
        for (int i = 0; i < size; i++) {
            inner[i] = tmp[i];
        }
    }

    public void push(T el) {
        if (size == inner.length) {
            resize(inner.length * 2);
        }
        inner[size++] = el;
    }

    public String toString() {
        String s = "[";
        // s += inner[0].getClass();
        for (int i = 0; i < this.size; i++) {
            s += inner[i].toString();
            if (i < this.size - 1) s += ", ";
        }
        s += "]";
        return s;
    }
}
