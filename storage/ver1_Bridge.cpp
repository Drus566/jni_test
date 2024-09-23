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

JNIEXPORT jobject JNICALL Java_ver1_Bridge_search(JNIEnv *env, jobject obj, jstring query) {
    std::string db_name = "example.db";

    /*********** PREPARE JNI *********/
    std::string path_response_class = "ver1/Response";

    // Response

    jclass response_class = env->FindClass("ver1/Response");
    if (response_class == nullptr) {
        std::cerr << "JNI: Failed to find class " << path_response_class << std::endl;
        return NULL;
    }
    jmethodID response_class__constructor = env->GetMethodID(response_class, "<init>", "(Ljava/util/List;)V");
    if (response_class__constructor == nullptr) {
        std::cerr << "JNI: Failed to find constructor for '" << path_response_class << "'" << std::endl;
        return NULL;
    }

    // ArrayList
    jclass array_list = env->FindClass("java/util/ArrayList");
    if (array_list == nullptr) {
        std::cerr << "JNI: Failed to find class 'java/util/ArrayList'" << std::endl;
        return NULL;
    }
    jmethodID array_list__constructor = env->GetMethodID(array_list, "<init>", "()V");
    if (array_list__constructor == nullptr) {
        std::cerr << "JNI: Failed to find constructor for 'java/util/ArrayList'" << std::endl;
        return NULL;
    }
    jmethodID array_list__add = env->GetMethodID(array_list, "add", "(Ljava/lang/Object;)Z");
    if (array_list__add == nullptr) {
        std::cerr << "JNI: Failed to find method 'add' for 'java/util/ArrayList'" << std::endl;
        return NULL;
    }

    // Integer
    jclass int_class = env->FindClass("java/lang/Integer");
    if (int_class == nullptr) {
        std::cerr << "JNI: Failed to find class 'java/lang/Integer'" << std::endl;
        return NULL;
    }
    jmethodID int_class__constructor = env->GetMethodID(int_class, "<init>", "(I)V");
    if (int_class__constructor == nullptr) {
        std::cerr << "JNI: Failed to find constructor for 'java/lang/Integer'" << std::endl;
        return NULL;
    }
    jmethodID int_class__int_value = env->GetMethodID(int_class, "intValue", "()I");
    if (int_class__int_value == NULL) {
        std::cerr << "JNI: Failed to find getValue method for 'java/lang/Integer'" << std::endl;
        return NULL;
    }

    // Float
    jclass float_class = env->FindClass("java/lang/Float");
    if (float_class == nullptr) {
        std::cerr << "JNI: Failed to find class 'java/lang/Float'" << std::endl;
        return NULL;
    }
    jmethodID float_class__constructor = env->GetMethodID(float_class, "<init>", "(F)V");
    if (float_class__constructor == nullptr) {
        std::cerr << "JNI: Failed to find constructor for 'java/lang/Float'" << std::endl;
        return NULL;
    }

    // /*********** PREPARE SQLITE3 *********/

    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errMsg = 0;

    const std::string sql_query = env->GetStringUTFChars(query, NULL);

    // Open the database
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "JNI: Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return NULL;
    }

    // Set PRAGMA case_sensitive_like to OFF (default behavior)
    if (sqlite3_exec(db, "PRAGMA case_sensitive_like = OFF;", 0, 0, &errMsg) != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql_query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "JNI: Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return NULL;
    }

    int column_count = sqlite3_column_count(stmt);
    int type = 0;

    jobject outer_list = env->NewObject(array_list, array_list__constructor);
    if (outer_list == nullptr) {
        std::cerr << "JNI: Failed create new object for 'java/util/ArrayList'" << std::endl;
        return NULL;
    }

    // Execute the SQL statement and fetch results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        jobject inner_list = env->NewObject(array_list, array_list__constructor);
        if (inner_list == nullptr) {
            std::cerr << "JNI: Failed create new object for 'java/util/ArrayList'" << std::endl;
            return NULL;
        }

        for (int col = 0; col < column_count; col++) {
            type = sqlite3_column_type(stmt, col);
            if (type == SQLITE_INTEGER) {
                int val = sqlite3_column_int(stmt, col);
                jobject j_int = env->NewObject(int_class, int_class__constructor, val);

                // std::cout << "JNI: int val = sqlite3_column_int(stmt, col); | " << val << std::endl;
                if (j_int == nullptr) {
                    /*** ATTENTION: boolean in sqlite3 saved like integers ***/
                    std::cerr << "JNI: Failed create new j_int object" << std::endl;
                    return NULL;
                }
                if (!env->CallBooleanMethod(inner_list, array_list__add, j_int)) {
                    std::cerr << "JNI: Failed add j_int to inner list" << std::endl;
                    return NULL;
                }
                env->DeleteLocalRef(j_int);
            }
            else if (type == SQLITE_TEXT) {
                const char *str = reinterpret_cast<const char *>(sqlite3_column_text(stmt, col));
                jstring j_string = env->NewStringUTF(str);
                // std::string cpp_str(str);
                // std::cout << "JNI: const char *str = reinterpret_cast<const char *>(sqlite3_column_text(stmt, col)); | " << cpp_str << std::endl;
                if (j_string == nullptr) {
                    std::cerr << "JNI: Failed create new j_string" << std::endl;
                    return NULL;
                }
                if (!env->CallBooleanMethod(inner_list, array_list__add, j_string)) {
                    std::cerr << "JNI: Failed add j_string to inner list" << std::endl;
                    return NULL;
                }
                env->DeleteLocalRef(j_string);
            }
            else if (type == SQLITE_FLOAT) {
                float val = sqlite3_column_double(stmt, col);
                jobject j_float = env->NewObject(float_class, float_class__constructor, val);
                // std::cout << "JNI: float val = sqlite3_column_double(stmt, col); | " << val << std::endl;
                if (j_float == nullptr) {
                    std::cerr << "JNI: Failed create new j_float" << std::endl;
                    return NULL;
                }
                if (!env->CallBooleanMethod(inner_list, array_list__add, j_float)) {
                    std::cerr << "JNI: Failed add j_float to inner list" << std::endl;
                    return NULL;
                }
                env->DeleteLocalRef(j_float);
            }

        }
        if (inner_list == nullptr || !env->CallBooleanMethod(outer_list, array_list__add, inner_list)) {
            std::cerr << "JNI: Failed add inner list to outer list" << std::endl;
            return NULL;
        }
        env->DeleteLocalRef(inner_list);
    }
    sqlite3_close(db);

    jobject response_object = env->NewObject(response_class, response_class__constructor, outer_list);
    if (response_object == nullptr) {
        std::cerr << "JNI: Failed create new object for " << path_response_class << std::endl;
        return NULL;
    }
    env->DeleteLocalRef(outer_list);

    return response_object;
}
