package bbyk.problems.mergeSortedArrays;

import java.util.Enumeration;
import java.util.NoSuchElementException;

/**
 * @author bbyk
 */
public class MinHeapArrayMerger<E extends Comparable<? super E>> implements Enumeration<E> {
    private E[][] arrays;
    private MinHeap<Node> minHeap;

    public MinHeapArrayMerger(E[][] arrays) {
        if (arrays == null)
            throw new NullPointerException("arrays");
        this.arrays = arrays;
    }

    public boolean hasMoreElements() {
        ensureMinHeap();
        return !minHeap.isEmpty();
    }

    public E nextElement() {
        ensureMinHeap();

        if (!hasMoreElements())
            throw new NoSuchElementException();

        final Node removeNode = minHeap.extract();
        final E value = removeNode.value;

        if (removeNode.enumeration.hasMoreElements()) {
            removeNode.value = removeNode.enumeration.nextElement();
            minHeap.add(removeNode);
        }

        return value;
    }

    private void ensureMinHeap() {
        // initially fill the heap with first values of all arrays
        if (minHeap == null) {
            minHeap = new MinHeap<Node>(arrays.length);
            for (E[] a : arrays) {
                final ArrayEnumeration<E> enumeration = new ArrayEnumeration<E>(a);
                if (enumeration.hasMoreElements()) {
                    final Node node = this.new Node();
                    node.enumeration = enumeration;
                    node.value = enumeration.nextElement();
                    minHeap.add(node);
                }
            }
        }
    }

    private class Node implements Comparable<Node> {
        ArrayEnumeration<E> enumeration;
        E value;

        public int compareTo(Node o) {
            return value.compareTo(o.value);
        }
    }
}
