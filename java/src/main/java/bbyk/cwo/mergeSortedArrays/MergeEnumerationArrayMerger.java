package bbyk.cwo.mergeSortedArrays;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Enumeration;

/**
 * @author bbyk
 */
public class MergeEnumerationArrayMerger<E extends Comparable<? super E>> implements Enumeration<E> {
    private Enumeration<E> enumeration;

    public MergeEnumerationArrayMerger(E[][] arrays) {
        if (arrays == null)
            throw new NullPointerException("arrays");

        final Deque<Enumeration<E>> queue = new ArrayDeque<Enumeration<E>>(arrays.length);
        for (final E[] array : arrays) {
            queue.add(new ArrayEnumeration<E>(array));
        }
        while (queue.size() > 1) {
            final Enumeration<E> first = queue.pop();
            final Enumeration<E> second = queue.pop();
            // if number of enumerations is odd, do not merge last one
            queue.add(second == null ? first : new MergeEnumeration<E>(first, second));
        }
        enumeration = queue.pop();
    }

    public boolean hasMoreElements() {
        return enumeration.hasMoreElements();
    }

    public E nextElement() {
        return enumeration.nextElement();
    }
}
