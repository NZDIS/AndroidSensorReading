package org.nzdis.sensorspeed;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class JavaThreeSensors extends TestSensor implements SensorEventListener {

    private SensorManager sensorManager;
    private Sensor accelerometer;
    private Sensor gyroscope;
    private Sensor magneticField;

    private int accelCount = 0;
    private int gyroCount = 0;
    private int magCount = 0;

    public JavaThreeSensors(Context context) {
        sensorManager = (SensorManager)context.getSystemService(Context.SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        gyroscope = sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        magneticField = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
    }

	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		//System.out.println("Accuracy Changed: " + accuracy);
	}

	public void onSensorChanged(SensorEvent event) {
		sensorChanged();
		if (isRunning) {
			if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
				accelCount++;
			} else if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
				gyroCount++;
			} else if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
				magCount++;
			}
		}
	}

    public void startup() {
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_FASTEST);
        sensorManager.registerListener(this, gyroscope, SensorManager.SENSOR_DELAY_FASTEST);
        sensorManager.registerListener(this, magneticField, SensorManager.SENSOR_DELAY_FASTEST);
        accelCount = 0;
        gyroCount = 0;
        magCount = 0;
        //System.out.println(this.getClass().getSimpleName() + " registered Listener");
    }

    public void shutdown() {
        sensorManager.unregisterListener(this);
        System.out.println("Three Sensors: ");
        System.out.println(" - Accelerometer: " + accelCount);
        System.out.println(" - Gyroscope: " + gyroCount);
        System.out.println(" - Magnetic Field: " + magCount);
       // System.out.println(this.getClass().getSimpleName() + " unregistered Listener");
    }
    
}
