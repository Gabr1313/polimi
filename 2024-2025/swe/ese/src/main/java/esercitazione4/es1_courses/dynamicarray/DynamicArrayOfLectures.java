package esercitazione4.es1_courses.dynamicarray;

import esercitazione4.es1_courses.modules.Lecture;

public class DynamicArrayOfLectures {
    private static final int allocationSize = 10;
    private int size;
    private Lecture[] arr;

    public DynamicArrayOfLectures() {
        arr = new Lecture[allocationSize];
        size = 0;
    }

    public int size() {
        return size;
    }

    public Lecture get(int index) {
        return arr[index];
    }

    public void add(Lecture l) {
        for (int i=0; i<size; i++) {
            if (arr[i].equals(l)) return;
        }
        // per evitare che lo stesso studente sia presente due volte.
        if (size < arr.length) {
            arr[size] = l;
            size++;
        } else {
            Lecture[] temp = arr;
            arr = new Lecture[arr.length + allocationSize];
            for (int i=0; i<temp.length; i++) {
                arr[i] = temp[i];
            }
            arr[size] = l;
            size++;
        }
    }
}
