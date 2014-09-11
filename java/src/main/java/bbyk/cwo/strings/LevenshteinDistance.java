package bbyk.cwo.strings;

/**
 * @author bbyk
 */
public class LevenshteinDistance {
    public static int distance(String from, String to) {
        final int[][] cache = new int[from.length() + 1][to.length() + 1];
        for (int i = 0; i < cache.length; i++) {
            cache[i][0] = i;
        }
        for (int k = 0; k < cache[0].length; k++) {
            cache[0][k] = k;
        }
        for (int i = 1; i < cache.length; i++) {
            for (int k = 1; k < cache[i].length; k++) {
                int d1 = cache[i - 1][k] + 1;
                int d2 = cache[i - 1][k - 1] + (to.charAt(k - 1) != from.charAt(i - 1) ? 1 : 0);
                int d3 = cache[i][k - 1] + 1;
                cache[i][k] = Math.min(Math.min(d1, d2), d3);
            }
        }
        return cache[cache.length - 1][cache[cache.length - 1].length - 1];
    }
}
