package org.nzdis.sensorspeed;

import android.content.Context;

public class CAccelerometer extends TestSensor {

    public CAccelerometer(Context context) {
    }

    // called from the C object
	public void onSensorChanged() {
		sensorChanged();
	}

    public native void accelerometerStartup(CAccelerometer handler);
    public static native void accelerometerShutdown();

	@Override
	public void startup() {
    	/*new Thread(new Runnable() {
    		public void run() {
    			accelerometerStartup(this);
    		}
    	}).start();*/
		// TODO
		System.out.println("CAstart1");
		accelerometerStartup(this);
		System.out.println("CAstart2");
	}

	@Override
	public void shutdown() {
		accelerometerShutdown();
	}

	static {
		System.out.println("loading code");
		System.loadLibrary("Controller");
	}
	
}
