package bbyk.cwo.concurrency;

import org.testng.Assert;
import org.testng.annotations.Test;

public class MonitorBasedSemaphoreTest {
    @Test
    public void allInOneTest() throws InterruptedException {
        final MonitorBasedSemaphore sema = new MonitorBasedSemaphore(2);
        sema.aquire();
        Assert.assertEquals(sema.getPermits(), 1);
        sema.release();
        Assert.assertEquals(sema.getPermits(), 2);
        
        sema.aquire();
        sema.aquire();

        Assert.assertEquals(sema.getPermits(), 0);
        
        final Thread anotherThread = new Thread(new Runnable() {
            public void run() {
                try {
                    sema.aquire();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        anotherThread.start();
        
        Assert.assertEquals(sema.getPermits(), 0);
        
        sema.release();
        
        anotherThread.join();
    }
}
