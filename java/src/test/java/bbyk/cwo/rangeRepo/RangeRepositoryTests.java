package bbyk.cwo.rangeRepo;

import org.testng.annotations.Test;

import static org.testng.Assert.*;

/**
 * @author bbyk
 */
@Test
public class RangeRepositoryTests {
    @Test
    public void testMergeTwoEnclosedRanges() {
        final RangeRepository repo = new RangeRepository();
        repo.addRange(10, 200);
        repo.addRange(150, 180);

        assertEquals(repo.db.size(), 1);
        assertEquals(repo.db.firstKey().from, 10);
        assertEquals(repo.db.firstKey().to, 200);
    }

    @Test
    public void testMergeTwoOverlappedRanges() {
        final RangeRepository repo = new RangeRepository();
        repo.addRange(10, 200);
        repo.addRange(150, 300);

        assertEquals(repo.db.size(), 1);
        assertEquals(repo.db.firstKey().from, 10);
        assertEquals(repo.db.firstKey().to, 300);
    }

    @Test
    public void testAddRangesNoOverlap() {
        final RangeRepository repo = new RangeRepository();
        repo.addRange(10, 200);
        repo.addRange(1, 9);

        assertEquals(repo.db.size(), 2);
        assertEquals(repo.db.firstKey().from, 1);
        assertEquals(repo.db.firstKey().to, 9);

        assertEquals(repo.db.lastKey().from, 10);
        assertEquals(repo.db.lastKey().to, 200);
    }

    @Test
    public void testAddRangeOverlappingThreeExistingRanges() {
        final RangeRepository repo = new RangeRepository();
        repo.addRange(10, 200);
        repo.addRange(1, 9);
        repo.addRange(205, 300);

        // this range causes the other three to be merged
        repo.addRange(3, 250);

        assertEquals(repo.db.size(), 1);
        assertEquals(repo.db.firstKey().from, 1);
        assertEquals(repo.db.firstKey().to, 300);
    }

    @Test
    public void testQuerySimpleRanges() {
        final RangeRepository repo = new RangeRepository();

        repo.addRange(10, 200);
        repo.addRange(150, 180);
        repo.addRange(250, 500);

        assertTrue(repo.queryRange(50, 100));
        assertFalse(repo.queryRange(180, 300));
        assertFalse(repo.queryRange(600, 1000));
    }

    @Test
    public void testDeleteRangesOverlapLeft() {
        final RangeRepository repo = new RangeRepository();
        repo.addRange(10, 200);
        repo.addRange(150, 180);

        repo.deleteRange(1, 15);

        assertEquals(repo.db.size(), 1);
        assertEquals(repo.db.firstKey().from, 15);
        assertEquals(repo.db.firstKey().to, 200);
    }

    @Test
    public void testDeleteRangesOverlapRight() {
        final RangeRepository repo = new RangeRepository();
        repo.addRange(10, 200);
        repo.addRange(150, 180);

        repo.deleteRange(180, 220);

        assertEquals(repo.db.size(), 1);
        assertEquals(repo.db.firstKey().from, 10);
        assertEquals(repo.db.firstKey().to, 180);
    }

    @Test
    public void testDeleteSeveralUnoverlappedRanges() {
        final RangeRepository repo = new RangeRepository();
        repo.addRange(10, 20);
        repo.addRange(30, 40);
        repo.addRange(50, 60);

        repo.deleteRange(1, 100);

        assertEquals(repo.db.size(), 0);
    }

    @Test
    public void testDeleteSeveralUnoverlappedRangesPlusEdges() {
        final RangeRepository repo = new RangeRepository();
        repo.addRange(10, 20);
        repo.addRange(30, 40);
        repo.addRange(50, 60);

        repo.deleteRange(15, 55);

        assertEquals(repo.db.size(), 2);
        assertEquals(repo.db.firstKey().from, 10);
        assertEquals(repo.db.firstKey().to, 15);

        assertEquals(repo.db.lastKey().from, 55);
        assertEquals(repo.db.lastKey().to, 60);
    }
}
