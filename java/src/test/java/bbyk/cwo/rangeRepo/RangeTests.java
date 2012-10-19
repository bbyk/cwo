package bbyk.cwo.rangeRepo;

import org.testng.annotations.Test;

import java.util.List;

import static org.testng.Assert.*;

/**
 * @author bbyk
 */
@Test
public class RangeTests {
    @Test
    public void testRangeNoIntersection() {
        final Range first = new Range(10, 20);
        final Range second = new Range(21, 30);

        assertFalse(first.isOverlappedWith(second));
    }

    @Test
    public void testRangeHasIntersection() {
        final Range first = new Range(10, 20);
        final Range second = new Range(15, 30);

        assertTrue(first.isOverlappedWith(second));
    }

    @Test
    public void testInvertedRange() {
        final Range range = new Range(20, 10);

        assertEquals(range.from, 10);
        assertEquals(range.to, 20);
    }

    @Test
    public void testMergeTwoRanges() throws RangesNotMergeableException {
        final Range first = new Range(10, 20);
        final Range second = new Range(15, 30);
        final Range third = first.merge(second);

        assertEquals(third.from, 10);
        assertEquals(third.to, 30);
    }

    @Test
    public void testContainsRanges() {
        final Range first = new Range(10, 20);
        final Range second = new Range(15, 20);

        assertTrue(first.contains(second));
    }

    @Test
    public void testDoesNotContainRangesOverlap() {
        final Range first = new Range(10, 20);
        final Range second = new Range(15, 21);

        assertFalse(first.contains(second));
    }

    @Test
    public void testDoesNotContainRangesSmaller() {
        final Range first = new Range(10, 20);
        final Range second = new Range(15, 21);

        assertFalse(second.contains(first));
    }

    @Test
    public void testExcludeOverlappingLeft() throws RangesNotMergeableException {
        final Range first = new Range(10, 20);
        final Range second = new Range(5, 15);

        final List<Range> list = first.exclude(second);

        assertEquals(list.size(), 1);
        assertEquals(list.get(0).from, 15);
        assertEquals(list.get(0).to, 20);
    }

    @Test
    public void testExcludeOverlappingRight() throws RangesNotMergeableException {
        final Range first = new Range(10, 20);
        final Range second = new Range(15, 25);

        final List<Range> list = first.exclude(second);

        assertEquals(list.size(), 1);
        assertEquals(list.get(0).from, 10);
        assertEquals(list.get(0).to, 15);
    }

    @Test
    public void testExcludeEnclosed() throws RangesNotMergeableException {
        final Range first = new Range(10, 20);
        final Range second = new Range(1, 25);

        final List<Range> list = first.exclude(second);

        assertEquals(list.size(), 0);
    }

    @Test
    public void testExcludeContains() throws RangesNotMergeableException {
        final Range first = new Range(7, 20);
        final Range second = new Range(8, 18);

        final List<Range> list = first.exclude(second);

        assertEquals(list.size(), 2);
        assertEquals(list.get(0).from, 7);
        assertEquals(list.get(0).to, 8);

        assertEquals(list.get(1).from, 18);
        assertEquals(list.get(1).to, 20);
    }

    @Test(expectedExceptions = {RangesNotMergeableException.class})
    public void testExcludeNoOverlapping() throws RangesNotMergeableException {
        final Range first = new Range(10, 20);
        final Range second = new Range(21, 30);

        final List<Range> list = first.exclude(second);
    }
}
