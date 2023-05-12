

#ifndef JNILOG_H
#define JNILOG_H

#ifdef __cplusplus
extern "C" {
#endif

void logD(const char* msg,...);
void logE(const char* msg,...);
void logStrD(JNIEnv* env,  const char* prefix,jstring str) ;
void logIntD(JNIEnv* env,  const char* prefix, jint i);
#ifdef __cplusplus
}
#endif
#endif
