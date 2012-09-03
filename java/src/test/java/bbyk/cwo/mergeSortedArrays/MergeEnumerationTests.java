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
public class MergeEnumerationTests extends BaseTests {

    @BeforeTest
    public void beforeTest() {
        MergeEnumeration.resetStats();
    }

    @Test
    public void testOverlap1() {
        final ArrayEnumeration<Integer> left = new ArrayEnumeration<Integer>(new Integer[]{1, 2, 3, 4, 5});
        final ArrayEnumeration<Integer> right = new ArrayEnumeration<Integer>(new Integer[]{3, 4, 5, 6, 7});

        final MergeEnumeration<Integer> merge = new MergeEnumeration<Integer>(left, right);
        assertEquals(Collections.list(merge).toArray(), new int[]{1, 2, 3, 4, 5, 6, 7});
    }

    @Test
    public void testOverlap2() {
        final ArrayEnumeration<Integer> left = new ArrayEnumeration<Integer>(new Integer[]{3, 4, 5, 6, 7});
        final ArrayEnumeration<Integer> right = new ArrayEnumeration<Integer>(new Integer[]{1, 2, 3, 4, 5});

        final MergeEnumeration<Integer> merge = new MergeEnumeration<Integer>(left, right);
        assertEquals(Collections.list(merge).toArray(), new int[]{1, 2, 3, 4, 5, 6, 7});
    }

    @Test
    public void testNoOverlap() {
        final ArrayEnumeration<Integer> left = new ArrayEnumeration<Integer>(new Integer[]{1, 2, 3, 4, 5});
        final ArrayEnumeration<Integer> right = new ArrayEnumeration<Integer>(new Integer[]{6, 7, 8, 9, 10});

        final MergeEnumeration<Integer> merge = new MergeEnumeration<Integer>(left, right);
        assertEquals(Collections.list(merge).toArray(), new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    }

    @Test
    public void testFullMatch() {
        final ArrayEnumeration<Integer> left = new ArrayEnumeration<Integer>(new Integer[]{1, 2, 3, 4, 5});
        final ArrayEnumeration<Integer> right = new ArrayEnumeration<Integer>(new Integer[]{1, 2, 3, 4, 5});

        final MergeEnumeration<Integer> merge = new MergeEnumeration<Integer>(left, right);
        assertEquals(Collections.list(merge).toArray(), new int[]{1, 2, 3, 4, 5});
    }

    @Test
    public void testPipeline() {
        final MergeEnumeration<Integer> merge = new MergeEnumeration<Integer>(
                new MergeEnumeration<Integer>(
                        new ArrayEnumeration<Integer>(new Integer[]{1, 2, 3, 4, 5}),
                        new ArrayEnumeration<Integer>(new Integer[]{6, 7, 8, 9, 13})),
                new MergeEnumeration<Integer>(
                        new ArrayEnumeration<Integer>(new Integer[]{2, 3, 4, 11, 17}),
                        new ArrayEnumeration<Integer>(new Integer[]{12, 14, 15})));

        assertEquals(Collections.list(merge).toArray(), new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 17});
    }

    @Test
    public void testKArrays() {
        final int n = 10000; // size of input
        final int k = 100; // number of arrays to merge

        final Integer[][] arrays = createKSortedArrays(n, k);
        final ArrayList<Integer> mergedList = Collections.list(new MergeEnumerationArrayMerger<Integer>(arrays));
        assertTrue(mergedList.size() <= n * k);

        final double expectedCompexity = k * n * Math.log(k) / Math.log(2);
        System.out.println("Expected runtime complexity: " + expectedCompexity);
        System.out.println("Actual runtime complexity: " + MergeEnumeration.getNumComparisons());

        // order of magnitude of number of operations is expected to be the same
        assertEquals((int) Math.log10(MergeEnumeration.getNumComparisons()), (int) Math.log10(expectedCompexity));
    }
}
