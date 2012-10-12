#include <jni.h>
#include <android/sensor.h>
#include <android/log.h>
#include "Common.h"

#ifndef COMMON_CPP_
#define COMMON_CPP_

#define LOG_TAG "org.nzdis.sensorspeed"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

#define LOOPER_ID 1
#define SAMP_PER_SEC 999

static int get_sensorevents(int fd, int events, void* data);

jmethodID mid;
jobject updateHandler;
JNIEnv *env;

ASensorEventQueue* sensorEventQueue;

int SENSORS_ENABLED = 1;

float acceleration_x;
float acceleration_y;
float acceleration_z;

float gyroscope_x;
float gyroscope_y;
float gyroscope_z;

float magneticfield_x;
float magneticfield_y;
float magneticfield_z;

int accCount = 0;
int gyroCount = 0;
int magCount = 0;

static int get_sensorevents(int fd, int events, void* data) {
	ASensorEvent event;
	while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {
		if (event.type == ASENSOR_TYPE_ACCELEROMETER) {
			env->CallVoidMethod(updateHandler, mid);
			acceleration_x = event.acceleration.x;
			acceleration_y = event.acceleration.y;
			acceleration_z = event.acceleration.z;
			accCount++;
		} else if (event.type == ASENSOR_TYPE_GYROSCOPE) {
			env->CallVoidMethod(updateHandler, mid);
			gyroscope_x = event.vector.x;
			gyroscope_y = event.vector.y;
			gyroscope_z = event.vector.z;
			gyroCount++;
		} else if (event.type == ASENSOR_TYPE_MAGNETIC_FIELD) {
			env->CallVoidMethod(updateHandler, mid);
			magneticfield_x = event.magnetic.x;
			magneticfield_y = event.magnetic.y;
			magneticfield_z = event.magnetic.z;
			magCount++;
		}
	}
	//should return 1 to continue receiving callbacks, or 0 to unregister
	return SENSORS_ENABLED;
}

#include "Accelerometer.cpp"
#include "Gyroscope.cpp"
#include "MagneticField.cpp"
#include "ThreeSensors.cpp"
#endif
