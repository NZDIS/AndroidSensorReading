
#include <jni.h>
#include <stdlib.h>
#include <android/sensor.h>
#include <android/looper.h>
#include <android/log.h>
#include "Accelerometer.h"

#ifndef ACCELEROMETER_CPP_
#define ACCELEROMETER_CPP_

static int get_sensorevents(int fd, int events, void* data);

#define LOOPER_ID 1
#define SAMP_PER_SEC 120

ASensorEventQueue* sensorEventQueue;

int SENSORS_ENABLED = 1;
int accCounter = 0;
int64_t lastAccTime = 0;

float acceleration_x;
float acceleration_y;
float acceleration_z;

jmethodID mid;
jobject updateHandler;
JNIEnv *env;

Accelerometer::Accelerometer() {
}


Accelerometer::~Accelerometer() {
}


void Accelerometer::startup(JNIEnv *e, jobject handler) {

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

	LOGI("sensorValue() - ALooper_forThread()");
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

	//Sampling rate: 100Hz
	int a = ASensor_getMinDelay(accSensor);
	LOGI("min-delay: %d", a);
	ASensorEventQueue_setEventRate(sensorEventQueue, accSensor, (1000L/SAMP_PER_SEC)*1000);

	LOGI("sensorValue() - START");

	while ((ident = ALooper_pollAll(-1, NULL, &events, NULL) >= 0)) {
		// If a sensor has data, process it now.
		if (ident == LOOPER_ID) {
			LOGI("if");
			ASensorEvent event;
			while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
				LOGI("accelerometer X = %f y = %f z=%f ", event.acceleration.x, event.acceleration.y, event.acceleration.z);
			}
		} else {
			LOGI("else");
		}
	}

	LOGI("sensorValue() - END");
}


void Accelerometer::shutdown() {
}










static int get_sensorevents(int fd, int events, void* data) {
	ASensorEvent event;
	while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
		if (event.type == ASENSOR_TYPE_ACCELEROMETER) {
			env->CallVoidMethod(updateHandler, mid);
			//LOGI("accl(x,y,z,t): %f %f %f %lld", event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);
			acceleration_x = event.acceleration.x;
			acceleration_y = event.acceleration.y;
			acceleration_z = event.acceleration.z;
			if (accCounter == 0 || accCounter == 1000) {
				//LOGI("accl(x,y,z,t): %f %f %f %lld", event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);
				//LOGI("Acc-Time: %lld (%f)", event.timestamp, ((double)(event.timestamp-lastAccTime))/1000000000.0);
				lastAccTime = event.timestamp;
				accCounter = 0;
			}

			accCounter++;
		}
	}
	//should return 1 to continue receiving callbacks, or 0 to unregister
	return SENSORS_ENABLED;
}


#endif
