#include <jni.h>
#include <string>

#include "myInclude/jnilog.h"
#include "myInclude/test.h"
#include <unistd.h>
#include "pthread.h"


extern "C"
jstring Java_com_zhengsr_cmakedemo_JniUtils_getTestName(
        JNIEnv* env,
        jobject){
    const char* testName = "你好，我是Jni返回给你的数据";
    return env->NewStringUTF(testName);
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
    //step 1: 拿到 class，也可以使用 env->FindClass
    jclass cls = env->GetObjectClass(person);
    //step 2: 拿到 ID
    jfieldID nameId =  env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jfieldID ageId = env->GetFieldID(cls,"age", "I");
    //打印 Java 的值，可以使用 getTypeField 的方法
    jstring name = (jstring)env->GetObjectField(person,nameId);
    jint age = (jint)env->GetIntField(person,ageId);
    logStrD(env,"name:", name);
    logIntD(env,"age:", age);
    //修改值，setTypeField 方法
    jstring newName = env->NewStringUTF("张三");
    env->SetObjectField(person,nameId,newName);
    env->SetIntField(person,ageId,25);
    //方式本地引用
    env->DeleteLocalRef(newName);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_zhengsr_cmakedemo_JniUtils_testJniJavaMethod(JNIEnv *env, jobject thiz, jobject person) {
    jclass cls = env->GetObjectClass(person);
    jmethodID  getMsgId = env->GetMethodID(cls,"getMsg","(Z)Ljava/lang/String;");
    auto  msg = (jstring)env->CallObjectMethod(person,getMsgId, true);
    return env->NewStringUTF(env->GetStringUTFChars(msg,JNI_FALSE));
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_zhengsr_cmakedemo_JniUtils_testThrowError(JNIEnv *env, jobject thiz,jint a,jint b) {
    if (b == 0) {
        //先判断是否之前存在异常
        jthrowable throwable = env->ExceptionOccurred();
        if (throwable != NULL) {
            //清楚异常
            env->ExceptionClear();
        }
        // 输出异常信息
        env->ExceptionDescribe();
        jclass exception = env->FindClass("java/lang/Exception");
        //抛出异常
        env->ThrowNew(exception , "分母不能为空!");
        return -1;
    }
    return a/b;
}
jstring returnString(JNIEnv *env, jobject thiz) {
    const char* testName = "函数动态注册,C 方法为 returnString，对应的 Java 方法为getStringFromC";
    return env->NewStringUTF(testName);
}


jint returnInt(JNIEnv *env, jobject thiz,jint a,jint b,jint c) {

    return a+b+c;
}

void timeTest(JNIEnv *env, jobject thiz,jobject timeListener) {
    jclass clsTimeListener = env->GetObjectClass(timeListener);
    jmethodID onTime = env->GetMethodID(clsTimeListener,"onTimer","(I)V");
    for (int i = 0; i < 10; ++i) {
        env->CallVoidMethod(timeListener,onTime,i);
        sleep(1);
    }
}
jobject g_listener;
JavaVM  *g_vm;
void *timeTask(void*){
    JNIEnv *env;
    //获取当前线程的 JNIEnv
    g_vm->AttachCurrentThread(&env, 0);
    //获取全局的 jobject ，拿到 Java 对象
    jobject listener = env->NewLocalRef(g_listener);
    logObjD(env,"listener:",listener);
    jclass clsTimeListener = env->GetObjectClass(listener);
    jmethodID onTime = env->GetMethodID(clsTimeListener,"onTimer","(I)V");
    for (int i = 0; i < 10; ++i) {
        env->CallVoidMethod(listener,onTime,i);
        sleep(1);
    }
    //释放资源
    env->DeleteLocalRef(listener);
    env->DeleteGlobalRef(g_listener);
    //线程与Java虚拟机分离
    g_vm->DetachCurrentThread();

    return nullptr;
}
void testThread(JNIEnv *env, jobject thiz,jobject timeListener){
    pthread_t tid;
    env->GetJavaVM(&g_vm);
    //初始化线程属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    //不能直接将 Java 传递给线程，因为 JNIEnv 是线程私有的，因此需要传递过去
    //当时 jvm 是进程共用的，因此可以通过 jvm 获取 jnienv，然后获取 jobject
    //因此，jobject ，需要设置成全局引用，否则会报错
    g_listener = env->NewGlobalRef(timeListener);
    pthread_create(&tid, &attr,timeTask, nullptr);
    pthread_setname_np(tid,"timeTask");
    //  env->DeleteGlobalRef(g_listener);
}



#define METHOD_CLASS "com/zhengsr/cmakedemo/JniUtils"
const JNINativeMethod methods[]{
      //  {"getStringFromC","()Ljava/lang/String;", (void *) returnString},
        {"getIntFromC","(III)I", (void *) returnInt},
        {"timerTask","(Lcom/zhengsr/cmakedemo/JniUtils$OnTimerListener;)V", (void *) timeTest},
        {"testJniThread","(Lcom/zhengsr/cmakedemo/JniUtils$OnTimerListener;)V", (void *) testThread}
};


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    jclass clazz = env->FindClass(METHOD_CLASS);
    if (clazz == NULL) {
        return -1;
    }
    if (env->RegisterNatives(clazz, methods, sizeof(methods)/sizeof(methods[0])) < 0) {
        return -1;
    }
    return JNI_VERSION_1_6;
}



