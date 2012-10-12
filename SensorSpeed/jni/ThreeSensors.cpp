#include <jni.h>
#include <stdlib.h>
#include <android/sensor.h>
#include <android/looper.h>
#include "ThreeSensors.h"

#ifndef THREESENSORS_CPP_
#define THREESENSORS_CPP_



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CThreeSensors_threeSensorsStartup (JNIEnv *e, jclass c, jobject handler) {
	updateHandler = handler;
	env = e;

	jclass handlerClass = env->FindClass("org/nzdis/sensorspeed/CThreeSensors");
	if (handlerClass == NULL) {
		LOGI("big error 1");
	}
	mid = env->GetMethodID(handlerClass, "onSensorChanged", "()V");
	if (mid == NULL) {
		LOGI("big error 2");
	}

	ASensorEvent event;
	int events, ident;
	ASensorManager * sensorManager;
	const ASensor* accSensor;
	const ASensor* gyroSensor;
	const ASensor* magSensor;
	void* sensor_data = malloc(10000);

	SENSORS_ENABLED = 1;
	ALooper* looper = ALooper_forThread();

	if (looper == NULL) {
		looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	}

	sensorManager = ASensorManager_getInstance();

	accSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
	gyroSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_GYROSCOPE);
	magSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_MAGNETIC_FIELD);

	sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, LOOPER_ID,
			(ALooper_callbackFunc)get_sensorevents, sensor_data);

	ASensorEventQueue_enableSensor(sensorEventQueue, accSensor);
	ASensorEventQueue_enableSensor(sensorEventQueue, gyroSensor);
	ASensorEventQueue_enableSensor(sensorEventQueue, magSensor);

	int accMinDelay = ASensor_getMinDelay(accSensor);
	int gyroMinDelay = ASensor_getMinDelay(gyroSensor);
	int magMinDelay = ASensor_getMinDelay(magSensor);
	//LOGI("min-delay: %d", minDelay);
	ASensorEventQueue_setEventRate(sensorEventQueue, accSensor, (1000L/SAMP_PER_SEC)*1000);
	ASensorEventQueue_setEventRate(sensorEventQueue, gyroSensor, (1000L/SAMP_PER_SEC)*1000);
	ASensorEventQueue_setEventRate(sensorEventQueue, magSensor, (1000L/SAMP_PER_SEC)*1000);

	while ((ident = ALooper_pollAll(-1, NULL, &events, NULL) >= 0)) {
		// If a sensor has data, process it now.
		if (ident == LOOPER_ID) {
			LOGI("threeSensorStartup() - LOOPER!!!!!!");
			ASensorEvent event;
			while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
				if (event.type == ASENSOR_TYPE_ACCELEROMETER) {
					env->CallVoidMethod(updateHandler, mid);
					acceleration_x = event.acceleration.x;
					acceleration_y = event.acceleration.y;
					acceleration_z = event.acceleration.z;
				} else if (event.type == ASENSOR_TYPE_GYROSCOPE) {
					env->CallVoidMethod(updateHandler, mid);
					// TODO This is a placeholder. Need to find the true source of gyroscope data within the event.
					gyroscope_x = event.vector.x;
					gyroscope_y = event.vector.y;
					gyroscope_z = event.vector.z;
				} else if (event.type == ASENSOR_TYPE_MAGNETIC_FIELD) {
					env->CallVoidMethod(updateHandler, mid);
					magneticfield_x = event.magnetic.x;
					magneticfield_y = event.magnetic.y;
					magneticfield_z = event.magnetic.z;
				}
			}
		} else {
			LOGI("threeSensorStartup() - else!!!!!!");
		}
	}
}



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CThreeSensors_threeSensorsShutdown (JNIEnv *env, jclass c) {
	SENSORS_ENABLED = 0;
	LOGI("Approximate/inaccurate -> acc: %d, gyro: %d, mag:%d ", accCount, gyroCount, magCount);
}



#endif
