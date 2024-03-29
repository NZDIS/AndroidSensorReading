#include <jni.h>
#include <stdlib.h>
#include <android/sensor.h>
#include <android/looper.h>
#include "Accelerometer.h"

#ifndef ACCELEROMETER_CPP_
#define ACCELEROMETER_CPP_



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CAccelerometer_accelerometerStartup (JNIEnv *e, jclass c, jobject handler) {
	updateHandler = handler;
	env = e;

	jclass handlerClass = env->FindClass("org/nzdis/sensorspeed/CAccelerometer");
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
	void* sensor_data = malloc(10000);

	SENSORS_ENABLED = 1;
	ALooper* looper = ALooper_forThread();

	if (looper == NULL) {
		looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	}

	sensorManager = ASensorManager_getInstance();

	accSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);

	sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, LOOPER_ID,
			(ALooper_callbackFunc)get_sensorevents, sensor_data);

	ASensorEventQueue_enableSensor(sensorEventQueue, accSensor);

	int minDelay = ASensor_getMinDelay(accSensor);
	//LOGI("min-delay: %d", minDelay);
	ASensorEventQueue_setEventRate(sensorEventQueue, accSensor, (1000L/SAMP_PER_SEC)*1000);

	while ((ident = ALooper_pollAll(-1, NULL, &events, NULL) >= 0)) {
		// If a sensor has data, process it now.
		if (ident == LOOPER_ID) {
			LOGI("accelerometerStartup() - LOOPER!!!!!!");
			ASensorEvent event;
			while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
				if (event.type == ASENSOR_TYPE_ACCELEROMETER) {
					env->CallVoidMethod(updateHandler, mid);
					acceleration_x = event.acceleration.x;
					acceleration_y = event.acceleration.y;
					acceleration_z = event.acceleration.z;
				}
			}
		} else {
			LOGI("accelerometerStartup() - else!!!!!!");
		}
	}
}



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CAccelerometer_accelerometerShutdown (JNIEnv *env, jclass c) {
	SENSORS_ENABLED = 0;
}



#endif
