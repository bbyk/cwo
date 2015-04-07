package bbyk.cwo.games;

import org.testng.annotations.Test;

import java.util.Arrays;
import java.util.Set;

import static org.testng.Assert.assertTrue;

/**
 * @author bbyk on 4/6/15.
 */
public class BoggleTest {

    @Test
    public void simpleTest() {
        Boggle game = new Boggle();

        game.setDictionary(Arrays.asList("GEEKS", "FOR", "QUIZ", "GO"));
        game.setWorld(new Character[][]{{'G', 'I', 'Z'},
                {'U', 'E', 'K'},
                {'Q', 'S', 'E'}});

        Set<String> allWords = game.findAllWords();

        assertTrue(allWords.contains("GEEKS"));
        assertTrue(allWords.contains("QUIZ"));
    }
}