package org.nzdis.sensorspeed;

public class CMagneticField extends TestSensor {

    public native void magneticFieldStartup(CMagneticField handler);
    public static native void magneticFieldShutdown();

    class MagneticFieldThread extends Thread {
    	CMagneticField jm;
		public MagneticFieldThread(CMagneticField jm) {
			this.jm = jm;
		}
		public void run() {
			magneticFieldStartup(jm);
		}
		public void end() {
			magneticFieldShutdown();
		}
	}
	
    MagneticFieldThread magThread;
	
	int i = 0;
	
    // called from the C object
	public void onSensorChanged() {
		sensorChanged();
	}

	@Override
	public void startup() {
		magThread = new MagneticFieldThread(this);
		magThread.start();
	}

	@Override
	public void shutdown() {
		magThread.end();
		magThread = null;
	}
	
}
