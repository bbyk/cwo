package bbyk.cwo.rangeRepo;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeMap;

/**
 * Represents range db. Keeps track of ranges added to the repo.
 * May be used to query if a particular range exists in the repo.
 * Range that is enclosed inside another ranges is considered existing.
 * Maintains three methods to modify and access ranges:
 * <p/>
 * Uses TreeMap to keep track of ranges.
 * TreeMap is a balanced BST with log(n) operations
 * to fetch and modify
 *
 * @author bbyk
 * @see #addRange(int, int)
 * @see #queryRange(int, int)
 * @see #deleteRange(int, int)
 */
public class RangeRepository {
    TreeMap<Range, Range> db;

    public RangeRepository() {
        db = new TreeMap<Range, Range>(new Range.ComparableByFrom());
    }

    public void addRange(int from, int to) {
        Range newRange = new Range(from, to);

        try {
            final Range rangeByFromBeforeNew = db.floorKey(newRange);
            if (rangeByFromBeforeNew != null && rangeByFromBeforeNew.isOverlappedWith(newRange)) {
                newRange = rangeByFromBeforeNew.merge(newRange);
                db.remove(rangeByFromBeforeNew);
            }

            // Go through all the rest of the keys that are greater.
            // The operation is cheap and the tailMap returns a view.
            // Use iterator's remove method to remove items from the db.
            final Iterator<Range> iterator = db.tailMap(newRange).keySet().iterator();
            while (iterator.hasNext()) {
                final Range rangeByFromAfterNew = iterator.next();
                if (!rangeByFromAfterNew.isOverlappedWith(newRange))
                    break;
                newRange = rangeByFromAfterNew.merge(newRange);
                iterator.remove();
            }
        } catch (RangesNotMergeableException e) {
            // though it is a checked exception for range, it should never be thrown
            // if the implementation works correctly. If thrown, client can't recover.
            throw new IllegalStateException("state is corrupted", e);
        }

        db.put(newRange, newRange);
    }

    public boolean queryRange(int from, int to) {
        final Range queryRange = new Range(from, to);
        final Range rangeByFromBeforeNew = db.floorKey(queryRange);

        // no range found
        return rangeByFromBeforeNew != null && rangeByFromBeforeNew.contains(queryRange);
    }

    public void deleteRange(int from, int to) {
        Range deleteRange = new Range(from, to);

        List<Range> newRanges = new ArrayList<Range>();
        try {
            final Range rangeByFromBeforeNew = db.floorKey(deleteRange);
            if (rangeByFromBeforeNew != null && rangeByFromBeforeNew.isOverlappedWith(deleteRange)) {
                newRanges.addAll(rangeByFromBeforeNew.exclude(deleteRange));
                db.remove(rangeByFromBeforeNew);
            }

            // Go through all the rest of the keys that are greater.
            // The operation is cheap and the tailMap returns a view.
            // Use iterator's remove method to remove items from the db.
            final Iterator<Range> iterator = db.tailMap(deleteRange).keySet().iterator();
            while (iterator.hasNext()) {
                final Range rangeByFromAfterNew = iterator.next();
                if (!rangeByFromAfterNew.isOverlappedWith(deleteRange))
                    break;
                newRanges.addAll(rangeByFromAfterNew.exclude(deleteRange));
                iterator.remove();
            }
        } catch (RangesNotMergeableException e) {
            // though it is a checked exception for range, it should never be thrown
            // if the implementation works correctly. If thrown, client can't recover.
            throw new IllegalStateException("state is corrupted", e);
        }

        for (final Range newRange : newRanges) {
            db.put(newRange, newRange);
        }
    }
}
