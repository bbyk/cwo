package bbyk.cwo.concurrency;

import org.testng.Assert;
import org.testng.annotations.Test;

public class AQSSemaphoreTest {

    @Test
    public void allInOneTest() throws InterruptedException {
        final AQSSemaphore sema = new AQSSemaphore(2);
        sema.aquire();
        Assert.assertEquals(sema.getPermits(), 1);
        sema.release();
        Assert.assertEquals(sema.getPermits(), 2);

        sema.aquire();
        sema.aquire();

        Assert.assertEquals(sema.getPermits(), 0);

        final Thread anotherThread = new Thread(new Runnable() {
            public void run() {
                sema.release();
            }
        });
        anotherThread.start();

        Assert.assertEquals(sema.getPermits(), 0);

        sema.aquire();

        anotherThread.join();
    }
}
