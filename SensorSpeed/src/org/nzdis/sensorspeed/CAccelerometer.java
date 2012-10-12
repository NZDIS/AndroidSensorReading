package org.nzdis.sensorspeed;

public class CAccelerometer extends TestSensor {

    public native void accelerometerStartup(CAccelerometer handler);
    public static native void accelerometerShutdown();

    class AccelerometerThread extends Thread {
		CAccelerometer ja;
		public AccelerometerThread(CAccelerometer ja) {
			this.ja = ja;
		}
		public void run() {
			accelerometerStartup(ja);
		}
		public void end() {
			accelerometerShutdown();
		}
	}
	
	AccelerometerThread accelThread;
	
	int i = 0;
	
    // called from the C object
	public void onSensorChanged() {
		sensorChanged();
	}

	@Override
	public void startup() {
		accelThread = new AccelerometerThread(this);
		accelThread.start();
	}

	@Override
	public void shutdown() {
		accelThread.end();
		accelThread = null;
	}
	
}
