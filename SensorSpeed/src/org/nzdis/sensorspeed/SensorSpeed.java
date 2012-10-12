package org.nzdis.sensorspeed;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class SensorSpeed extends Activity {

	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
    	final Button buttonJavaAccelerometer = (Button) findViewById(R.id.buttonJavaAccelerometer);
    	buttonJavaAccelerometer.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                runTest(new JavaAccelerometer(v.getContext()));
            }
        });

    	final Button buttonCAccelerometer = (Button) findViewById(R.id.buttonCAccelerometer);
    	buttonCAccelerometer.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                runTest(new CAccelerometer());
            }
        });

    	final Button buttonJavaGyroscope = (Button) findViewById(R.id.buttonJavaGyroscope);
    	buttonJavaGyroscope.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                runTest(new JavaGyroscope(v.getContext()));
            }
        });

    	final Button buttonCGyroscope = (Button) findViewById(R.id.buttonCGyroscope);
    	buttonCGyroscope.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                runTest(new CGyroscope());
            }
        });

    	final Button buttonJavaMagneticField = (Button) findViewById(R.id.buttonJavaMagneticField);
    	buttonJavaMagneticField.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                runTest(new JavaMagneticField(v.getContext()));
            }
        });

    	final Button buttonCMagneticField = (Button) findViewById(R.id.buttonCMagneticField);
    	buttonCMagneticField.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                runTest(new CMagneticField());
            }
        });

    	final Button buttonJavaThreeSensors = (Button) findViewById(R.id.buttonJavaThreeSensors);
    	buttonJavaThreeSensors.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                runTest(new JavaThreeSensors(v.getContext()));
            }
        });

    	final Button buttonCThreeSensors = (Button) findViewById(R.id.buttonCThreeSensors);
    	buttonCThreeSensors.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                runTest(new CThreeSensors());
            }
        });

    }
	
	public void runTest(TestSensor test) {
        EditText editRunTimeSeconds = (EditText) findViewById(R.id.editRunTimeSeconds);
        test.setRunTimeSeconds(Integer.parseInt(editRunTimeSeconds.getText().toString()));
        test.start();
	}

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

	static {
		System.out.println("SensorSpeed - loading C++ library...");
		System.loadLibrary("Sensors");
		System.out.println("SensorSpeed - loading C++ library successful");
	}
}
