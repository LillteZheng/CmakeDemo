#include <jni.h>
#include <string>

#include "myInclude//test.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_zhengsr_cmakedemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

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
