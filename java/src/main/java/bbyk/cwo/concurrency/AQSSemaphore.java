package bbyk.cwo.concurrency;

import com.google.common.annotations.VisibleForTesting;
import com.google.common.base.Preconditions;

import java.util.concurrent.locks.AbstractQueuedSynchronizer;

/**
 * @author bbyk
 */
public class AQSSemaphore {
    private Sync sync;
    private int permits;

    public AQSSemaphore(int permits) {
        Preconditions.checkArgument(permits > 0);

        sync = new Sync();
        this.permits = permits;
    }

    private class Sync extends AbstractQueuedSynchronizer {
        public int getUsedPermits() {
            return super.getState();
        }

        @Override
        protected int tryAcquireShared(int arg) {
            while (true) {
                int issuedPermits = getState();
                if (issuedPermits == permits) {
                    return -1;
                }

                if (compareAndSetState(issuedPermits, issuedPermits + 1))
                    return permits - issuedPermits - 1;
            }
        }

        @Override
        protected boolean tryReleaseShared(int arg) {
            while (true) {
                final int issuedPermits = getState();
                if (compareAndSetState(issuedPermits, issuedPermits - 1))
                    return true;
            }
        }
    }

    public void aquire() throws InterruptedException {
        sync.acquireSharedInterruptibly(1);
    }

    public void release() {
        sync.releaseShared(1);
    }

    @VisibleForTesting
    public int getPermits() {
        return permits - sync.getUsedPermits();
    }
}
