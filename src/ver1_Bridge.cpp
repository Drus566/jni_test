#include <iostream>
#include <string>
#include <vector>
#include "ver1_Bridge.h"
#include "sqlite3.h"


//JNIEXPORT jobject JNICALL Java_ver1_Bridge_createObject
//  (JNIEnv *env, jclass cl, jstring val_str, jint val_int, jboolean val_bool) {
//    jclass objectClass = env->FindClass("ver1/User");
//    if (objectClass == NULL) {
//        return NULL; // или выбросить исключение
//    }
//
//    jmethodID constructorId = env->GetMethodID(objectClass, "<init>", "(Ljava/lang/String;IZ)V");
//    if (constructorId == NULL) {
//        return NULL; // или выбросить исключение
//    }
//
//    jobject o = env->NewObject(objectClass, constructorId, val_str, val_int, val_bool);
//    if (o == NULL) {
//        return NULL; // или выбросить исключение
//    }
//
//    return env->NewGlobalRef(o);
//}
//
///*
// * Class:     ver1_Bridge
// * Method:    getObjectValue
// * Signature: (Lver1/User;)I
// */
//JNIEXPORT jint JNICALL Java_ver1_Bridge_getObjectValue(JNIEnv *env, jclass cl, jobject obj) {
//    jclass objectClass = env->GetObjectClass(obj);
//    jfieldID fieldId = env->GetFieldID(objectClass, "age", "I");
//    return env->GetIntField(obj, fieldId);
//}
//
///*
// * Class:     ver1_Bridge
// * Method:    setObjectValue
// * Signature: (Lver1/User;I)V
// */
//JNIEXPORT void JNICALL Java_ver1_Bridge_setObjectValue(JNIEnv *env, jclass cl, jobject obj, jint val_int) {
////    std::cout << "Java_ver1_Bridge_setObjectValue" << std::endl;
//    jclass objectClass = env->GetObjectClass(obj);
//    std::cout << objectClass << std::endl;
//    jfieldID fieldId = env->GetFieldID(objectClass, "age", "I");
//    env->SetIntField(obj, fieldId, val_int);
//}
//
//JNIEXPORT void JNICALL Java_ver1_Bridge_test
//  (JNIEnv *env, jclass cl) {
//    std::cout << "GGWP" << std::endl;
//}


JNIEXPORT jobject JNICALL Java_ver1_Bridge_createObject
    (JNIEnv *env, jobject obj, jstring val_str, jint val_int, jboolean val_bool) {
    jclass objectClass = env->FindClass("ver1/User");
    if (objectClass == NULL) return NULL; // или выбросить исключение

    jmethodID constructorId = env->GetMethodID(objectClass, "<init>", "(Ljava/lang/String;IZ)V");
    if (constructorId == NULL) return NULL; // или выбросить исключение

    jobject o = env->NewObject(objectClass, constructorId, val_str, val_int, val_bool);
    if (o == NULL) return NULL; // или выбросить исключение

    return env->NewGlobalRef(o);
}

JNIEXPORT jint JNICALL Java_ver1_Bridge_getObjectValue
    (JNIEnv *env, jobject, jobject obj) {
    jclass objectClass = env->GetObjectClass(obj);
    jfieldID fieldId = env->GetFieldID(objectClass, "age", "I");
    return env->GetIntField(obj, fieldId);
}

JNIEXPORT void JNICALL Java_ver1_Bridge_setObjectValue
    (JNIEnv *env, jobject, jobject obj, jint val_int) {
//    std::cout << "Java_ver1_Bridge_setObjectValue" << std::endl;
    jclass objectClass = env->GetObjectClass(obj);
    std::cout << objectClass << std::endl;
    jfieldID fieldId = env->GetFieldID(objectClass, "age", "I");
    env->SetIntField(obj, fieldId, val_int);
}

JNIEXPORT jobject JNICALL Java_ver1_Bridge_test(JNIEnv *env, jobject obj) {
    sqlite3 *db;
    char *errMsg = nullptr;
    int rc;

    rc = sqlite3_open("example228.db", &db);
    if (rc) std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    const char *sqlCreateTable = "CREATE TABLE IF NOT EXISTS PERSON("
                                 "ID INT PRIMARY KEY NOT NULL, "
                                 "NAME TEXT NOT NULL);";
    rc = sqlite3_exec(db, sqlCreateTable, nullptr, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully" << std::endl;
    }

    sqlite3_close(db);
                                
    jclass response_class = env->FindClass("ver1/Response");
    // jmethodID response_class_constructors = env->GetMethodID(response_class, "<init>", "(Ljava/util/ArrayList;)V");
    jmethodID response_class_constructors = env->GetMethodID(response_class, "<init>", "(Ljava/util/List;)V");
    // Класс списка
    jclass array_list = env->FindClass("java/util/ArrayList");
    jmethodID array_list__constructor = env->GetMethodID(array_list, "<init>", "()V");
    jmethodID array_list__add = env->GetMethodID(array_list, "add", "(Ljava/lang/Object;)Z");

    // Класс инта
    jclass int_class = env->FindClass("java/lang/Integer");
    jmethodID int_class__constructor = env->GetMethodID(int_class, "<init>", "(I)V");

    // Класс бул
    jclass bool_class = env->FindClass("java/lang/Boolean");
    jmethodID bool_class__constructor = env->GetMethodID(bool_class, "<init>", "(Z)V");

    // Создаем основной список
    jobject outerList = env->NewObject(array_list, array_list__constructor);

    for (int i = 0; i < 5; ++i)
    {
        // Создаем внутренний список
        jobject innerList = env->NewObject(array_list, array_list__constructor);

        std::string name = "Имя_" + std::to_string(i); // Имя с кириллицей

        jstring jName = env->NewStringUTF(name.c_str());
        jobject jInt = env->NewObject(int_class, int_class__constructor, 3);
        jobject jBool = env->NewObject(bool_class, bool_class__constructor, JNI_TRUE);

        env->CallBooleanMethod(innerList, array_list__add, jName);
        env->CallBooleanMethod(innerList, array_list__add, jInt);
        env->CallBooleanMethod(innerList, array_list__add, jBool);

        env->CallBooleanMethod(outerList, array_list__add, innerList);

        env->DeleteLocalRef(jName);
        env->DeleteLocalRef(jInt);
        env->DeleteLocalRef(jBool);
        env->DeleteLocalRef(innerList);
    }

    jobject o = env->NewObject(response_class, response_class_constructors, outerList);
    env->DeleteLocalRef(outerList);

    return o;
}

JNIEXPORT jobject JNICALL Java_ver1_Bridge_testObj(JNIEnv *env, jobject obj)
{
    jclass array_list = env->FindClass("java/util/ArrayList");
    jmethodID array_list__constructor = env->GetMethodID(array_list, "<init>", "()V");
    jmethodID array_list__add = env->GetMethodID(array_list, "add", "(Ljava/lang/Object;)Z");

    jclass int_class = env->FindClass("java/lang/Integer");
    jmethodID int_class__constructor = env->GetMethodID(int_class, "<init>", "(I)V");

    jclass bool_class = env->FindClass("java/lang/Boolean");
    jmethodID bool_class__constructor = env->GetMethodID(bool_class, "<init>", "(Z)V");

    // Создаем основной список
    jobject outerList = env->NewObject(array_list, array_list__constructor);

    for (int i = 0; i < 5; ++i) {
        // Создаем внутренний список
        jobject innerList = env->NewObject(array_list, array_list__constructor);

        std::string name = "Имя_" + std::to_string(i); // Имя с кириллицей

        jstring jName = env->NewStringUTF(name.c_str());
        jobject jInt = env->NewObject(int_class, int_class__constructor, 3);
        jobject jBool = env->NewObject(bool_class, bool_class__constructor, JNI_TRUE);

        // 
        // jobjectArray objectArray = env->NewObjectArray(3, env->FindClass("java/lang/Object"), nullptr);
        
        // env->SetObjectArrayElement(objectArray, 0, jName);                             // String
        // env->SetObjectArrayElement(objectArray, 1, jInt);     // Integer (int)
        // env->SetObjectArrayElement(objectArray, 2, jBool); // Boolean

        env->CallBooleanMethod(innerList, array_list__add, jName);
        env->CallBooleanMethod(innerList, array_list__add, jInt);
        env->CallBooleanMethod(innerList, array_list__add, jBool);

        env->CallBooleanMethod(outerList, array_list__add, innerList);

        env->DeleteLocalRef(jName);
        env->DeleteLocalRef(jInt);
        env->DeleteLocalRef(jBool);
        env->DeleteLocalRef(innerList);
    }


    return outerList;
    // jobjectArray resultArray = env->NewObjectArray(results.size(), listClass, nullptr);

    // for (size_t i = 0; i < results.size(); ++i) {
    //     jobject listObject = env->NewObject(listClass, listConstructor);

    //     for (const auto& value : results[i]) {
    //         jstring jValue = env->NewStringUTF("ggwp");
    //         jmethodID addMethod = env->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");
    //         env->CallBooleanMethod(listObject, addMethod, jValue);
    //         env->DeleteLocalRef(jValue); // Освобождаем локальную ссылку
    //     }

    //     env->SetObjectArrayElement(resultArray, i, listObject);
    //     env->DeleteLocalRef(listObject); // Освобождаем локальную ссылку
    // }

    // env->ReleaseStringUTFChars(query, nativeQuery);

    // return resultArray; // Возвращаем массив списков
}
