package bbyk.cwo.strings;

import org.testng.Assert;
import org.testng.annotations.Test;

public class LevenshteinDistanceTest {

    @Test
    public void distanceBetweenEqualIsZero() throws Exception {
        Assert.assertEquals(LevenshteinDistance.distance("abc", "abc"), 0);
    }
    
    @Test
    public void distanceBetweenPartlyOverlapped() throws Exception {
        Assert.assertEquals(LevenshteinDistance.distance("abc", "bcd"), 2);
    }
    
    @Test
    public void distanceNoOverlapsSum() throws Exception {
        Assert.assertEquals(LevenshteinDistance.distance("abc", "def"), 3);
    }
    
    @Test
    public void distanceNoOverlapsEmpty() throws Exception {
        Assert.assertEquals(LevenshteinDistance.distance("abc", ""), 3);
    }
}
