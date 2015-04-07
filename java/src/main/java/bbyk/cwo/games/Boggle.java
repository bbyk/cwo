package bbyk.cwo.games;

import com.google.common.collect.Lists;
import com.google.common.collect.Sets;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Set;

/**
 * @author Boris Byk on 4/6/15.
 */
public class Boggle {
    private Object[] trie = new Object[26];
    private Character[][] world;
    private LinkedList<Character> word;
    private Set<Integer> visited;
    private Set<String> res;

    public void setDictionary(Iterable<String> words) {

        for (String word : words) {
            Object[] ctrie = trie;

            for (int i = 0; i < word.length(); i++) {
                Character c = word.charAt(i);
                int cpos = c - 'A';
                if (ctrie[cpos] == null) {
                    ctrie[cpos] = new Object[26];
                }

                ctrie = (Object[]) ctrie[cpos];
            }
        }
    }

    public void setWorld(Character[][] world) {
        this.world = new Character[world.length + 2][world[0].length + 2];

        for (int y = 0; y < world.length; y++) {
            for (int x = 0; x < world[y].length; x++) {
                this.world[x + 1][y + 1] = world[x][y];
            }
        }
    }

    public Set<String> findAllWords() {
        res = Sets.newHashSet();
        visited = Sets.newHashSet();
        word = Lists.newLinkedList();

        for (int y = 0; y < world.length; y++) {
            for (int x = 0; x < world[y].length; x++) {
                if (world[y][x] == null)
                    continue;

                dfs(trie, y * world.length + x);
            }
        }

        return res;
    }

    private void dfs(Object[] trie, int s) {
        int y = s / world.length;
        int x = s % world[0].length;
        Character c = world[y][x];
        if (c == null)
            return;
        // letter is not in the dictionary
        if (trie[c - 'A'] == null)
            return;

        word.addLast(c);
        trie = (Object[]) trie[c - 'A'];

        for (Integer ap : Arrays.asList(s - 1, s + 1, s + world.length, s - world.length, s + world.length + 1, s + world.length - 1, s - world.length + 1, s - world.length - 1)) {
            // prune boundaries
            if (visited.contains(ap))
                continue;
            visited.add(ap);
            dfs(trie, ap);
            visited.remove(ap);
        }

        StringBuilder sb = new StringBuilder(word.size());

        for (Character ch : word) {
            sb.append(ch);
        }

        res.add(sb.toString());

        word.removeLast();
    }
}
