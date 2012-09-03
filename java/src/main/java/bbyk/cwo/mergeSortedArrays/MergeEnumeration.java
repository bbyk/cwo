package bbyk.cwo.mergeSortedArrays;

import java.util.Enumeration;
import java.util.NoSuchElementException;

/**
 * Does not support null values.
 * @author bbyk
 */
public class MergeEnumeration<T extends Comparable<? super T>> implements Enumeration<T> {
    private Enumeration<T> left;
    private Enumeration<T> right;
    private T leftValue;
    private T rightValue;
    private Boolean hasMore;
    private static int numComparisons;

    public static int getNumComparisons() {
        return numComparisons;
    }

    public MergeEnumeration(Enumeration<T> left, Enumeration<T> right) {
        if (left == null)
            throw new NullPointerException("left");
        if (right == null)
            throw new NullPointerException("right");

        this.left = left;
        this.right = right;
    }

    public boolean hasMoreElements() {
        // return cached evaluation if exists, otherwise re-evaluate and save
        if (hasMore == null)
            hasMore = left.hasMoreElements() || right.hasMoreElements() || leftValue != null || rightValue != null;
        return hasMore;
    }

    public T nextElement() {
        if (!hasMoreElements())
            throw new NoSuchElementException();

        // drop cache
        hasMore = null;

        if (left.hasMoreElements() && leftValue == null)
            leftValue = left.nextElement();
        if (right.hasMoreElements() && rightValue == null)
            rightValue = right.nextElement();

        numComparisons++;
        T result;
        if (leftValue == null && right.hasMoreElements()) {
            result = rightValue;
            rightValue = null;
            leftValue = null;
        } else if (rightValue == null && left.hasMoreElements()) {
            result = leftValue;
            leftValue = null;
            rightValue = null;
        } else if (leftValue == null) {
            result = rightValue;
            rightValue = null;
        } else if (rightValue == null) {
            result = leftValue;
            leftValue = null;
        } else if (leftValue.compareTo(rightValue) < 0) { // left < right
            result = leftValue;
            leftValue = null;
        } else if (leftValue.compareTo(rightValue) > 0) { // left > right
            result = rightValue;
            rightValue = null;
        } else {
            result = leftValue;
            leftValue = null;
            rightValue = null;
        }

        return result;
    }

    public static void resetStats() {
        numComparisons = 0;
    }
}
