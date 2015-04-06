package bbyk.cwo.concurrency;

import com.google.common.annotations.VisibleForTesting;
import com.google.common.base.Preconditions;

/**
 * @author bbyk
 */
public class MonitorBasedSemaphore {
    private int permits;
    private final Object syncRoot = new Object();

    public MonitorBasedSemaphore(int permits) {
        Preconditions.checkArgument(permits > 0);
        this.permits = permits;
    }

    @VisibleForTesting
    public int getPermits() {
        return permits;
    }

    public void aquire() throws InterruptedException {
        synchronized (syncRoot) {
            while (permits == 0) {
                syncRoot.wait();
            }

            permits--;
        }
    }

    public void release() {
        synchronized (syncRoot) {
            permits++;
            syncRoot.notify();
        }
    }
}
