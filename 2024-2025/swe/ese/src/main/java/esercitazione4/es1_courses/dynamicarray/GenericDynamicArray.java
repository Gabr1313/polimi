package esercitazione4.es1_courses.dynamicarray;

public class GenericDynamicArray<T> {
    private static final int allocationSize = 10;
    private int size;
    private T arr[];

    public GenericDynamicArray() {
        arr = (T[]) new Object[allocationSize];
        // non si può fare new T in Java, quindi dobbiamo istanziare degli Object e castarli a T
        // non entriamo troppo nel dettaglio di questo
        size = 0;
    }

    public int size() {
        return size;
    }

    public T get(int index) {
        return arr[index];
    }

    public void add(T l) {
        for (int i=0; i<size; i++) {
            if (arr[i].equals(l)) return;
        }
        if (size < arr.length) {
            arr[size] = l;
            size++;
        } else {
            T temp[] = arr;
            arr = (T[]) new Object[arr.length + allocationSize];
            for (int i=0; i<temp.length; i++) {
                arr[i] = temp[i];
            }
            arr[size] = l;
            size++;
        }
    }
}
