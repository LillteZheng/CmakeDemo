#include <jni.h>
#include <android/log.h>

#define LOG_TAG "JNI_LOG"


extern "C"  void logE(const char* msg,...){
//可变参数
    va_list ap;
    va_start(ap, msg);
    __android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, msg, ap);
    va_end(ap);
}

extern "C"  void logD(const char* msg,...){
    //可变参数
    va_list ap;
    va_start(ap, msg);
    __android_log_vprint(ANDROID_LOG_DEBUG, LOG_TAG, msg, ap);
    va_end(ap);
}

extern "C" void logStrD(JNIEnv* env,  const char* prefix,jstring str) {
    const char* c_str = env->GetStringUTFChars(str, JNI_FALSE);
    logD("%s %s", prefix, c_str);
    env->ReleaseStringUTFChars(str, c_str);
}

extern "C" void logShortD(JNIEnv* env,  const char* prefix, jshort s) {
    logD("%s %hd", prefix, s);
}

extern "C" void logByteD(JNIEnv* env,  const char* prefix, jbyte b) {
    logD("%s %hhd", prefix, b);
}

extern "C" void logCharD(JNIEnv* env,  const char* prefix, jchar c) {
    logD("%s %c", prefix, c);
}

extern "C" void logIntD(JNIEnv* env,  const char* prefix, jint i) {
    logD("%s %d", prefix, i);
}

extern "C" void logLongD(JNIEnv* env,  const char* prefix, jlong l) {
    logD("%s %lld", prefix, l);
}

extern "C" void logFloatD(JNIEnv* env,  const char* prefix, jfloat f) {
    logD("%s %f", prefix, f);
}

extern "C" void logDoubleD(JNIEnv* env,  const char* prefix, jdouble d) {
    logD("%s %lf", prefix, d);
}

