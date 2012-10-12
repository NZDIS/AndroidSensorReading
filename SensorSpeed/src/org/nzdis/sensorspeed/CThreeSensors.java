package org.nzdis.sensorspeed;

public class CThreeSensors extends TestSensor {

    private int accelCount = 0;
    private int gyroCount = 0;
    private int magCount = 0;

    public native void threeSensorsStartup(CThreeSensors handler);
    public static native void threeSensorsShutdown();

    class ThreeSensorsThread extends Thread {
		CThreeSensors ja;
		public ThreeSensorsThread(CThreeSensors ja) {
			this.ja = ja;
		}
		public void run() {
			threeSensorsStartup(ja);
		}
		public void end() {
			threeSensorsShutdown();
		}
	}
	
    ThreeSensorsThread sensorThread;
	
    // called from the C object
	public void onSensorChanged() {
		sensorChanged();
	}

	@Override
	public void startup() {
		sensorThread = new ThreeSensorsThread(this);
		sensorThread.start();
        accelCount = 0;
        gyroCount = 0;
        magCount = 0;
	}

	@Override
	public void shutdown() {
        System.out.println("Three Sensors: ");
        System.out.println(" - Accelerometer: " + accelCount);
        System.out.println(" - Gyroscope: " + gyroCount);
        System.out.println(" - Magnetic Field: " + magCount);
		sensorThread.end();
		sensorThread = null;
	}
	
}
