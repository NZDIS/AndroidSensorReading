#include <jni.h>
#include <stdlib.h>
#include <android/sensor.h>
#include <android/looper.h>
#include "Gyroscope.h"

#ifndef GYROSCOPE_CPP_
#define GYROSCOPE_CPP_



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CGyroscope_gyroscopeStartup (JNIEnv *e, jclass c, jobject handler) {
	updateHandler = handler;
	env = e;

	jclass handlerClass = env->FindClass("org/nzdis/sensorspeed/CGyroscope");
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
	const ASensor* gyroSensor;
	void* sensor_data = malloc(10000);

	SENSORS_ENABLED = 1;
	ALooper* looper = ALooper_forThread();

	if (looper == NULL) {
		looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	}

	sensorManager = ASensorManager_getInstance();

	gyroSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_GYROSCOPE);

	sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, LOOPER_ID,
			(ALooper_callbackFunc)get_sensorevents, sensor_data);

	ASensorEventQueue_enableSensor(sensorEventQueue, gyroSensor);

	int minDelay = ASensor_getMinDelay(gyroSensor);
	//LOGI("min-delay: %d", minDelay);
	ASensorEventQueue_setEventRate(sensorEventQueue, gyroSensor, (1000L/SAMP_PER_SEC)*1000);

	while ((ident = ALooper_pollAll(-1, NULL, &events, NULL) >= 0)) {
		// If a sensor has data, process it now.
		if (ident == LOOPER_ID) {
			LOGI("gyroscopeStartup() - LOOPER!!!!!!!");
			ASensorEvent event;
			while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
				if (event.type == ASENSOR_TYPE_GYROSCOPE) {
					env->CallVoidMethod(updateHandler, mid);
					// TODO This is a placeholder. Need to find the true source of gyroscope data within the event.
					gyroscope_x = event.vector.x;
					gyroscope_y = event.vector.y;
					gyroscope_z = event.vector.z;
				}
			}
		} else {
			LOGI("gyroscopeStartup() - else!!!!!!!");
		}
	}
}



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CGyroscope_gyroscopeShutdown (JNIEnv *env, jclass c) {
	SENSORS_ENABLED = 0;
}



JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CThreeSensors_gyroscopeShutdown (JNIEnv *env, jclass c) {
	SENSORS_ENABLED = 0;
}



#endif
