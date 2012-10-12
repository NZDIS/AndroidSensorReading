package org.nzdis.sensorspeed;

public abstract class TestSensor extends Thread {
	
	private int runTimeSeconds = 0;
	private int counter = 0;
	protected long timerStart = 0;
	protected long timerStop = 0;
	protected boolean isRunning = false;

	public abstract void startup();
	public abstract void shutdown();
	
	@Override
	public void run() {
		startup();
        try {
        	System.out.println(this.getClass().getSimpleName() + " test starting - " + runTimeSeconds + "s");
			Thread.sleep(200);
	        startTest();
			Thread.sleep(runTimeSeconds * 1000);
			stopTest();
			Thread.sleep(200);
			System.out.println(this.getClass().getSimpleName() + " test complete");
			System.out.println(" - count: " + getCounter());
			System.out.println(" - duration(millis): " + getDuration());
			System.out.println(" - samples per second: " + ((1000 * getCounter()) / getDuration()));
			System.out.println(" ");
   		} catch (InterruptedException e) {
			e.printStackTrace();
   		}
        shutdown();
	}
	
	private void startTest() {
		counter = 0;
		timerStart = System.currentTimeMillis();
		isRunning = true;
	}
	
	protected void sensorChanged() {
		if (isRunning) {
			counter++;
		}
	}
	
	private void stopTest() {
		isRunning = false;
		timerStop = System.currentTimeMillis();
	}
	
	private int getCounter() {
		return counter;
	}
	
	private long getDuration() {
		return timerStop - timerStart;
	}
	
	public void setRunTimeSeconds(int s) {
		runTimeSeconds = s;
	}
}
