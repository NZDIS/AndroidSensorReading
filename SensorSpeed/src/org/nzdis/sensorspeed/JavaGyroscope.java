package org.nzdis.sensorspeed;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class JavaGyroscope extends TestSensor implements SensorEventListener {

    private SensorManager sensorManager;
    private Sensor gyroscope;

    public JavaGyroscope(Context context) {
        sensorManager = (SensorManager)context.getSystemService(Context.SENSOR_SERVICE);
        gyroscope = sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
    }

	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		//System.out.println("Accuracy Changed: " + accuracy);
	}

	public void onSensorChanged(SensorEvent event) {
		sensorChanged();
	}

    public void startup() {
        sensorManager.registerListener(this, gyroscope, SensorManager.SENSOR_DELAY_FASTEST);
        System.out.println(this.getClass().getSimpleName() + " registered Listener");
    }

    public void shutdown() {
        sensorManager.unregisterListener(this);
        System.out.println(this.getClass().getSimpleName() + " unregistered Listener");
    }

}
