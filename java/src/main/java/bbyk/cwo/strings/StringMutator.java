package bbyk.cwo.strings;

import com.google.common.base.Preconditions;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

/**
 * @author bbyk
 */
public class StringMutator {
    private char[] input;
    private List<String> permutations;

    public StringMutator(String input) {
        Preconditions.checkNotNull(input);
        this.input = input.toCharArray();
    }

    public List<String> getPermutations() {
        if (permutations == null) {
            permutations = new ArrayList<String>();
            printAndMutate(0);
        }
        return permutations;
    }

    private void printAndMutate(int from) {
        if (from == input.length) {
            permutations.add(new String(input));
            return;
        }

        for (int i = from; i < input.length; i++) {
            swap(from, i);
            printAndMutate(from + 1);
            swap(from, i);
        }
    }

    private void swap(int i, int j) {
        char tmp = input[i];
        input[i] = input[j];
        input[j] = tmp;
    }
}
