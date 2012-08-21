package bbyk.problems.mergeSortedArrays;

import java.util.Arrays;
import java.util.Random;

/**
 * @author bbyk
 */
public class BaseTests {

    protected Integer[][] createKSortedArrays(int n, int k) {
        final Integer[][] result = new Integer[k][];
        final Random random = new Random();
        for (int i = 0; i < k; i++) {
            result[i] = createSortedArray(random, n);
        }
        return result;
    }

    protected Integer[] createSortedArray(Random random, int size) {
        final Integer[] result = new Integer[size];
        for (int i = 0; i < result.length; i++) {
            result[i] = random.nextInt(10000);
        }
        Arrays.sort(result);
        return result;
    }
}
