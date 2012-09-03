package bbyk.cwo.mergeSortedArrays;

import java.util.Enumeration;

/**
 * @author bbyk
 */
public class ArrayEnumeration<T> implements Enumeration<T> {
    private T[] array;
    private int index;

    public ArrayEnumeration(T[] array) {
        if (array == null)
            throw new NullPointerException("array");
        this.array = array;
    }

    public boolean hasMoreElements() {
        return index < array.length;
    }

    public T nextElement() {
        return array[index++];
    }
}
