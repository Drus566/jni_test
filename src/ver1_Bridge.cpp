#include <iostream>
#include "howdo1_NativeCallsClass.h"


JNIEXPORT jobject JNICALL Java_ver1_Bridge_createObject(JNIEnv *env, jobject obj, jstring val_str, jint val_int, jboolean val_bool) {
    jclass objectClass = env->FindClass("ver1/User");
    jmethodID constructorId = env->GetMethodID(objectClass, "<init>", "(I)V");
    jobject o = env->NewObject(objectClass, constructorId, val_str, val_int, val_bool);
    return env->NewGlobalRef(o);
}

/*
 * Class:     ver1_Bridge
 * Method:    getObjectValue
 * Signature: (Lver1/User;)I
 */
JNIEXPORT jint JNICALL Java_ver1_Bridge_getObjectValue(JNIEnv *env, jobject obj1, jobject obj2) {
    jclass objectClass = env->GetObjectClass(obj1);
    jfieldID fieldId = env->GetFieldID(objectClass, "age", "I");
    return env->GetIntField(obj1, fieldId);
}

/*
 * Class:     ver1_Bridge
 * Method:    setObjectValue
 * Signature: (Lver1/User;I)V
 */
JNIEXPORT void JNICALL Java_ver1_Bridge_setObjectValue(JNIEnv *env, jobject obj1, jobject obj2, jint val) {
    std::cout << "Java_ver1_Bridge_setObjectValue" << std::endl;
}
