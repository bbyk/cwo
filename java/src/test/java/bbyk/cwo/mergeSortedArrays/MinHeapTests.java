package bbyk.cwo.mergeSortedArrays;

import org.testng.annotations.BeforeTest;
import org.testng.annotations.Test;

import java.util.ArrayList;
import java.util.Collections;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;

/**
 * @author bbyk
 */
@Test
public class MinHeapTests extends BaseTests {
    @BeforeTest
    public void beforeTest() {
        MinHeap.resetStats();
    }

    @Test
    public void testMinHeap() {
        final MinHeap<Integer> minHeap = new MinHeap<Integer>();
        minHeap.add(2);
        minHeap.add(5);
        minHeap.add(1);

        assertEquals(Collections.list(minHeap.enumeration()).toArray(), new int[]{1, 2, 5});
    }

    @Test
    public void testAddExtract() {
        final MinHeap<Integer> minHeap = new MinHeap<Integer>();
        minHeap.add(1);
        minHeap.add(6);
        minHeap.add(2);
        minHeap.add(12);
        assertEquals(new Integer(1), minHeap.extract());
        minHeap.add(2);
        assertEquals(new Integer(2), minHeap.extract());
        assertEquals(new Integer(2), minHeap.extract());
    }

    @Test
    public void testMinHeapArrayMerger() {
        final Integer[][] input = new Integer[4][];
        input[0] = new Integer[]{1, 2, 3, 4, 5};
        input[1] = new Integer[]{6, 7, 8, 9, 13};
        input[2] = new Integer[]{2, 3, 4, 11, 17};
        input[3] = new Integer[]{12, 14, 15};

        final MinHeapArrayMerger<Integer> merger = new MinHeapArrayMerger<Integer>(input);
        assertEquals(Collections.list(merger).toArray(), new Integer[]{1, 2, 2, 3, 3, 4, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 17});
    }

    @Test
    public void testKArrays() {
        final int n = 10000; // size of input
        final int k = 100; // number of arrays to merge

        final MinHeapArrayMerger<Integer> merger = new MinHeapArrayMerger<Integer>(createKSortedArrays(n, k));

        final ArrayList<Integer> mergedList = Collections.list(merger);
        assertTrue(mergedList.size() <= n * k);

        final double expectedCompexity = k * n * Math.log(k) / Math.log(2);
        System.out.println("Expected runtime complexity: " + expectedCompexity);
        System.out.println("Actual runtime complexity: " + MinHeap.getNumComparisons());

        // order of magnitude of number of operations is expected to be the same
        assertEquals((int) Math.log10(MinHeap.getNumComparisons()), (int) Math.log10(expectedCompexity));
    }
}
