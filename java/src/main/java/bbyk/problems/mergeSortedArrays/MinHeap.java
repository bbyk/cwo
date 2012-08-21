package bbyk.problems.mergeSortedArrays;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;

/**
 * @author bbyk
 */
public class MinHeap<E extends Comparable<? super E>> {
    private ArrayList<E> dynArray;
    private static int numComparisons;

    public static int getNumComparisons() {
        return numComparisons;
    }

    public static void resetStats() {
        numComparisons = 0;
    }

    public MinHeap() {
        this(8);
    }

    public MinHeap(int capacity) {
        if (capacity < 0)
            throw new IllegalArgumentException("capacity < 0");
        dynArray = new ArrayList<E>(capacity);
    }

    public void add(E e) {
        if (e == null)
            throw new NullPointerException("e");
        dynArray.add(e);
        heapUp(dynArray.size() - 1);
    }

    public E extract() {
        final E minNode = dynArray.get(0);
        final E lastNode = dynArray.remove(dynArray.size() - 1);
        if (!dynArray.isEmpty()) {
            dynArray.set(0, lastNode);
            heapDown(0);
        }
        return minNode;
    }

    private void heapDown(int pos) {
        while (pos < dynArray.size() / 2) {
            int child = pos * 2 + 1;
            if (child < dynArray.size() - 1 && dynArray.get(child).compareTo(dynArray.get(child + 1)) > 0) {
                child++;
            }
            numComparisons++;
            if (dynArray.get(pos).compareTo(dynArray.get(child)) <= 0) {
                break;
            }
            Collections.swap(dynArray, pos, child);
            pos = child;
        }
    }

    public boolean isEmpty() {
        return dynArray.isEmpty();
    }

    private void heapUp(int pos) {
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            numComparisons++;
            if (dynArray.get(pos).compareTo(dynArray.get(parent)) >= 0) {
                break;
            }
            Collections.swap(dynArray, pos, parent);
            pos = parent;
        }
    }

    public Enumeration<E> enumeration() {
        return new Enumeration<E>() {

            public boolean hasMoreElements() {
                return !isEmpty();
            }

            public E nextElement() {
                return extract();
            }
        };
    }
}
