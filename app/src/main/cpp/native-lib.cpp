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
                                                      jlong c,  jfloat e, jdouble f,
                                                      jshort g, jbyte h) {
    char buf[256];
    snprintf(buf, sizeof(buf), "Char: %c, Int: %d, Long: %lld,  Float: %f, "
                               "Double: %lf, Short: %hd, Byte: %hhd",
             a, b, c, e, f, g, h);
    return env->NewStringUTF(buf);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_zhengsr_cmakedemo_JniUtils_testArray(JNIEnv *env, jobject thiz, jstring string,
                                              jintArray int_array) {
    //引用类型不能在Java中使用，需要使用
    const char* msg = env->GetStringUTFChars(string,JNI_FALSE);
    env->ReleaseStringUTFChars(string,msg);

    jint len = env->GetArrayLength(int_array);
    jint *intP = env->GetIntArrayElements(int_array,JNI_FALSE);
    for (int i = 0; i < len; ++i){
        logD("index = %d,value = %d",i,intP[i]);
    }
    env->ReleaseIntArrayElements(int_array,intP,0);

    char buf[256];
    snprintf(buf, sizeof(buf), "字符串: %s, 数据长度: %d",
             msg,len);
    return env->NewStringUTF(buf);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zhengsr_cmakedemo_JniUtils_testJniChanageJavaBean(JNIEnv *env, jobject thiz,
                                                           jobject person) {
    jclass cls = env->GetObjectClass(person);
    jfieldID nameId =  env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jfieldID ageId = env->GetFieldID(cls,"age", "I");
    jstring name = (jstring)env->GetObjectField(person,nameId);
    jint age = (jint)env->GetIntField(person,ageId);
    logStrD(env,"name:", name);
    logIntD(env,"age:", age);
    jstring newName = env->NewStringUTF("张三");
    env->SetObjectField(person,nameId,newName);
    env->SetIntField(person,ageId,25);

    env->DeleteLocalRef(newName);
}