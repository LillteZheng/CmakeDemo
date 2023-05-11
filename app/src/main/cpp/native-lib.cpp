#include <jni.h>
#include <string>

#include "myInclude/jnilog.h"
#include "myInclude/test.h"


extern "C"
jstring Java_com_zhengsr_cmakedemo_JniUtils_getTestName(
        JNIEnv* env,
        jobject){
    std::string testName = "你好，我是测试";
    return env->NewStringUTF(testName.c_str());

}

extern "C"
jint Java_com_zhengsr_cmakedemo_JniUtils_getIntValue(JNIEnv *env, jobject thiz, jint a, jint b) {
    return getNumSum(a,b);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_zhengsr_cmakedemo_JniUtils_testBaseDataValue(JNIEnv *env, jobject thiz, jchar a, jint b,
                                                      jlong c, jstring d, jfloat e, jdouble f,
                                                      jshort g, jbyte h) {
    const char* str = env->GetStringUTFChars(d, NULL);
    char buf[256];
    snprintf(buf, sizeof(buf), "Char: %c, Int: %d, Long: %lld, String: %s, Float: %f, "
                               "Double: %lf, Short: %hd, Byte: %hhd",
             a, b, c, str, e, f, g, h);
    env->ReleaseStringUTFChars(d, str);
    return env->NewStringUTF(buf);
}