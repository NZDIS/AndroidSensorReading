
#include <jni.h>
#include <stdlib.h>
#include "Controller.h"
#include "Accelerometer.h"


Accelerometer accelerometer;


JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CAccelerometer_accelerometerStartup (JNIEnv *env, jclass c, jobject handler) {
	accelerometer.startup(env, handler);
}

JNIEXPORT void JNICALL Java_org_nzdis_sensorspeed_CAccelerometer_accelerometerShutdown (JNIEnv *env, jclass c) {
	accelerometer.shutdown();
}


