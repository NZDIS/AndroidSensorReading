package org.nzdis.sensorspeed;

public class CGyroscope extends TestSensor {

    public native void gyroscopeStartup(CGyroscope handler);
    public static native void gyroscopeShutdown();

    class GyroscopeThread extends Thread {
		CGyroscope jg;
		public GyroscopeThread(CGyroscope jg) {
			this.jg = jg;
		}
		public void run() {
			gyroscopeStartup(jg);
		}
		public void end() {
			gyroscopeShutdown();
		}
	}
	
    GyroscopeThread gyroThread;
	
	int i = 0;
	
    // called from the C object
	public void onSensorChanged() {
		sensorChanged();
	}

	@Override
	public void startup() {
		gyroThread = new GyroscopeThread(this);
		gyroThread.start();
	}

	@Override
	public void shutdown() {
		gyroThread.end();
		gyroThread = null;
	}
	
}
