package bbyk.cwo.strings;

import org.apache.commons.math3.util.ArithmeticUtils;
import org.testng.annotations.Test;

import java.util.List;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertEqualsNoOrder;

/**
 * @author bbyk
 */
@Test
public class StringMutatorTests {
    @Test
    public void testOutput() {
        String input = "abc";
        final List<String> permutations = new StringMutator(input).getPermutations();
        assertEquals(permutations.size(), ArithmeticUtils.factorial(input.length()));
        assertEqualsNoOrder(permutations.toArray(), new Object[]{"acb", "abc", "bac", "bca", "cab", "cba"});
    }
}
