package bbyk.cwo.rangeRepo;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

import static java.lang.Math.max;
import static java.lang.Math.min;

/**
 * Represents a single range information and basic range operations.
 * The object is immutable.
 *
 * @author bbyk
 */
class Range {
    final int from;
    final int to;

    Range(int from, int to) {
        if (to < from) {
            int tmp = to;
            to = from;
            from = tmp;
        }

        this.from = from;
        this.to = to;
    }

    boolean isOverlappedWith(Range another) {
        return !(another.from > to || another.to < from);
    }

    Range merge(Range another) throws RangesNotMergeableException {
        if (!isOverlappedWith(another))
            throw new RangesNotMergeableException(this, another);
        final int newFrom = min(from, another.from);
        final int newTo = max(to, another.to);

        return new Range(newFrom, newTo);
    }

    List<Range> exclude(Range another) throws RangesNotMergeableException {
        if (!isOverlappedWith(another))
            throw new RangesNotMergeableException(this, another);
        final List<Range> result = new ArrayList<Range>();

        if (another.contains(this))
            return result;
        if (contains(another)) {
            if (from < another.from)
                result.add(new Range(from, another.from));
            if (another.to < to)
                result.add(new Range(another.to, to));
        }

        if (isOverlappedWith(another) && from > another.from)
            result.add(new Range(max(from, another.to), max(to, another.from)));

        if (isOverlappedWith(another) && to < another.to)
            result.add(new Range(min(from, another.to), min(to, another.from)));

        return result;
    }

    boolean contains(Range another) {
        return from <= another.from && to >= another.to;
    }

    static class ComparableByFrom implements Comparator<Range> {

        public int compare(Range o1, Range o2) {
            return o1.from - o2.from;
        }
    }
}
