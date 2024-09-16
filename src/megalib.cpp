#include <iostream>
#include "howdo1_NativeCallsClass.h"

JNIEXPORT void JNICALL Java_howdo1_NativeCallsClass_printOne(JNIEnv *env, jclass cl) {
    std::cout << "One" << std::endl;
}

JNIEXPORT void JNICALL Java_howdo1_NativeCallsClass_printTwo(JNIEnv *env, jclass cl) {
    std::cout << "Two" << std::endl;
}

JNIEXPORT jobject JNICALL Java_howdo1_NativeCallsClass_createObject(JNIEnv *env, jclass cl, jint i) {
    jclass objectClass = env->FindClass("howdo1/NativeCallsClass$MyObject");
    jmethodID constructorId = env->GetMethodID(objectClass, "<init>", "(I)V");
    jobject obj = env->NewObject(objectClass, constructorId, i);
    return env->NewGlobalRef(obj);
}

JNIEXPORT jint JNICALL Java_howdo1_NativeCallsClass_getObjectValue(JNIEnv *env, jclass cl, jobject obj) {
    jclass objectClass = env->GetObjectClass(obj);
    jfieldID fieldId = env->GetFieldID(objectClass, "value", "I");
    return env->GetIntField(obj, fieldId);
}

JNIEXPORT void JNICALL Java_howdo1_NativeCallsClass_setObjectValue(JNIEnv *env, jclass cl, jobject obj, jint i) {
    jclass objectClass = env->GetObjectClass(obj);
    jfieldID fieldId = env->GetFieldID(objectClass, "value", "I");
    env->SetIntField(obj, fieldId, i);
}
