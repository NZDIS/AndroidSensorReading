#include <jni.h>
#include <stdlib.h>
#include <android/sensor.h>
#include <android/looper.h>
#include "MagneticField.h"

#ifndef MAGNETICFIELD_CPP_
#define MAGNETICFIELD_CPP_



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CMagneticField_magneticFieldStartup (JNIEnv *e, jclass c, jobject handler) {
	updateHandler = handler;
	env = e;

	jclass handlerClass = env->FindClass("org/nzdis/sensorspeed/CMagneticField");
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
	const ASensor* magSensor;
	void* sensor_data = malloc(10000);

	SENSORS_ENABLED = 1;
	ALooper* looper = ALooper_forThread();

	if (looper == NULL) {
		looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	}

	sensorManager = ASensorManager_getInstance();

	magSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_MAGNETIC_FIELD);

	sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, LOOPER_ID,
			(ALooper_callbackFunc)get_sensorevents, sensor_data);

	ASensorEventQueue_enableSensor(sensorEventQueue, magSensor);

	int minDelay = ASensor_getMinDelay(magSensor);
	//LOGI("min-delay: %d", minDelay);
	ASensorEventQueue_setEventRate(sensorEventQueue, magSensor, (1000L/SAMP_PER_SEC)*1000);

	while ((ident = ALooper_pollAll(-1, NULL, &events, NULL) >= 0)) {
		// If a sensor has data, process it now.
		if (ident == LOOPER_ID) {
			LOGI("magneticFieldStartup() - LOOPER!!!!!!!!");
			ASensorEvent event;
			while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
				if (event.type == ASENSOR_TYPE_MAGNETIC_FIELD) {
					env->CallVoidMethod(updateHandler, mid);
					magneticfield_x = event.magnetic.x;
					magneticfield_y = event.magnetic.y;
					magneticfield_z = event.magnetic.z;
				}
			}
		} else {
			LOGI("magneticFieldStartup() - else!!!!!!!!!!!!!");
		}
	}
}



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CMagneticField_magneticFieldShutdown (JNIEnv *env, jclass c) {
	SENSORS_ENABLED = 0;
}



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CThreeSensors_magneticFieldShutdown (JNIEnv *env, jclass c) {
	SENSORS_ENABLED = 0;
}



#endif
