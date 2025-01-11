package esercitazione4.es1_courses.dynamicarray;

import esercitazione4.es1_courses.modules.Student;

public class DynamicArrayOfStudents {
    private static final int allocationSize = 10;
    private int size;
    private Student arr[];

    public DynamicArrayOfStudents() {
        arr = new Student[allocationSize];
        size = 0;
    }

    public int size() {
        return size;
    }

    public Student get(int index) {
        return arr[index];
    }

    public void add(Student s) {
        for (int i=0; i<size; i++) {
            if (arr[i].equals(s)) return;
        }
        // per evitare che lo stesso studente sia presente due volte.
        if (size < arr.length) {
            arr[size] = s;
            size++;
        } else {
            Student temp[] = arr;
            arr = new Student[arr.length + allocationSize];
            for (int i=0; i<temp.length; i++) {
                arr[i] = temp[i];
            }
            arr[size] = s;
            size++;
        }
    }
}
