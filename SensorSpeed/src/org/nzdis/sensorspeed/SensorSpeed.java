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
                runTest(new CAccelerometer(v.getContext()));
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
                //runTest(new CGyroscope(v.getContext()));
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

}
