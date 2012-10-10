/*
 * Accelerometer.h
 */

#ifndef ACCELERATOR_H_
#define ACCELERATOR_H_

class Accelerometer {

#define LOG_TAG "org.nzdis.sensorspeed"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

public:
	Accelerometer();
	virtual ~Accelerometer();

	virtual void startup(JNIEnv *, jobject);
	virtual void shutdown();
};

#endif
