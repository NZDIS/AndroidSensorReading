package org.nzdis.sensorspeed;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class JavaAccelerometer extends TestSensor implements SensorEventListener {

    private SensorManager sensorManager;
    private Sensor accelerometer;

    public JavaAccelerometer(Context context) {
        sensorManager = (SensorManager)context.getSystemService(Context.SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
    }

	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		//System.out.println("Accuracy Changed: " + accuracy);
	}

	public void onSensorChanged(SensorEvent event) {
		sensorChanged();
	}

    public void startup() {
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_FASTEST);
        System.out.println(this.getClass().getSimpleName() + " registered Listener");
    }

    public void shutdown() {
        sensorManager.unregisterListener(this);
        System.out.println(this.getClass().getSimpleName() + " unregistered Listener");
    }
    
}
