#include "DevToDevJNI.h"

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#define LOG_TAG "DevToDev"

#define DTD_CLASS_NAME "com/devtodev/core/DevToDev"
#define DTD_SOCIAL_NETWORK_CLASS_NAME "com/devtodev/core/data/consts/SocialNetwork"
#define DTD_PEOPLE_CLASS_NAME "com/devtodev/core/logic/people/People"

namespace devtodev {
    extern "C" {
    void jni_initialize(const std::string& appKey, const std::string& appSecret) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "init";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V");

            if (jMethod) {
                jobject activity = FAndroidApplication::GetGameActivityThis();
                jstring j_appKey = env->NewStringUTF(appKey.c_str());
                jstring j_appSecret = env->NewStringUTF(appSecret.c_str());
                env->CallStaticVoidMethod(jClass, jMethod, activity, j_appKey, j_appSecret);
                env->DeleteLocalRef(j_appKey);
                env->DeleteLocalRef(j_appSecret);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_setActiveLog(bool isActive) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/log/CoreLog");
        const char* strMethod = "setLogEnabled";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Z)V");

            if (jMethod) {
                env->CallStaticVoidMethod(jClass, jMethod, isActive);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_sendBufferedEvents() {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "sendBufferedEvents";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "()V");

            if (jMethod) {
                env->CallStaticVoidMethod(jClass, jMethod);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_customEvent(const std::string& name, const std::map<std::string, std::string>& params) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "customEvent";

        if (jClass) {
            jmethodID jMethod =
                env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;Lcom/devtodev/core/data/metrics/aggregated/events/CustomEventParams;)V");

            if (jMethod) {
                jclass jParamsClass = FAndroidApplication::FindJavaClass("com/devtodev/core/data/metrics/aggregated/events/CustomEventParams");
                jmethodID jParamsInit = env->GetMethodID(jParamsClass, "<init>", "()V");
                jobject jParams = env->NewObject(jParamsClass, jParamsInit);

                jmethodID jPutString = env->GetMethodID(jParamsClass, "putString", "(Ljava/lang/String;Ljava/lang/String;)V");

                std::string key;
                std::string value;
                for (auto pair : params) {
                    key = pair.first;
                    value = pair.second;

                    jstring j_key = env->NewStringUTF(key.c_str());
                    jstring j_value = env->NewStringUTF(value.c_str());
                    env->CallVoidMethod(jParams, jPutString, j_key, j_value);

                    env->DeleteLocalRef(j_key);
                    env->DeleteLocalRef(j_value);
                }

                jstring j_name = env->NewStringUTF(name.c_str());

                env->CallStaticVoidMethod(jClass, jMethod, j_name, jParams);

                env->DeleteLocalRef(j_name);
                env->DeleteLocalRef(jParams);
                env->DeleteLocalRef(jParamsClass);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_startProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "startProgressionEvent";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(
                jClass, strMethod, "(Ljava/lang/String;Lcom/devtodev/core/data/metrics/aggregated/progression/params/ProgressionEventParams;)V");

            if (jMethod) {
                jclass jParamsClass = FAndroidApplication::FindJavaClass("com/devtodev/core/data/metrics/aggregated/progression/params/LocationEventParams");
                jmethodID jParamsInit = env->GetMethodID(jParamsClass, "<init>", "()V");
                jobject jParams = env->NewObject(jParamsClass, jParamsInit);

                std::string key;
                std::string value;
                for (auto pair : params) {
                    key = pair.first;
                    value = pair.second;

                    if (key == "difficulty") {
                        jmethodID jDifficulty = env->GetMethodID(jParamsClass, "setDifficulty", "(I)V");
                        env->CallVoidMethod(jParams, jDifficulty, atoi(value.c_str()));
                    } else if (key == "source") {
                        jstring j_source = env->NewStringUTF(value.c_str());
                        jmethodID jDifficulty = env->GetMethodID(jParamsClass, "setSource", "(Ljava/lang/String;)V");
                        env->CallVoidMethod(jParams, jDifficulty, j_source);
                        env->DeleteLocalRef(j_source);
                    }
                }

                jstring j_locationName = env->NewStringUTF(locationName.c_str());
                env->CallStaticVoidMethod(jClass, jMethod, j_locationName, jParams);
                env->DeleteLocalRef(j_locationName);
                env->DeleteLocalRef(jParams);
                env->DeleteLocalRef(jParamsClass);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_endProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params,
                                 const std::map<std::string, std::string>& earned, const std::map<std::string, std::string>& spent) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "endProgressionEvent";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(
                jClass, strMethod, "(Ljava/lang/String;Lcom/devtodev/core/data/metrics/aggregated/progression/params/ProgressionEventParams;)V");

            if (jMethod) {
                jclass jParamsClass = FAndroidApplication::FindJavaClass("com/devtodev/core/data/metrics/aggregated/progression/params/LocationEventParams");
                jmethodID jParamsInit = env->GetMethodID(jParamsClass, "<init>", "()V");
                jobject jParams = env->NewObject(jParamsClass, jParamsInit);

                std::string key;
                std::string value;

                if (params.size() > 0) {
                    for (auto pair : params) {
                        key = pair.first;
                        value = pair.second;

                        if (key == "success") {
                            jmethodID jDifficulty = env->GetMethodID(jParamsClass, "setSuccess", "(Z)V");
                            env->CallVoidMethod(jParams, jDifficulty, value == "true" ? true : false);
                        } else if (key == "duration") {
                            jmethodID jDuration = env->GetMethodID(jParamsClass, "setDuration", "(J)V");
                            env->CallVoidMethod(jParams, jDuration, (jlong)atol(value.c_str()));
                        }
                    }
                }

                if (earned.size() > 0) {
                    jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/ResourcesMapContainer");
                    jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                    jobject jContainer = env->NewObject(jContainerClass, init);

                    jmethodID putMethod = env->GetMethodID(jContainerClass, "put", "(Ljava/lang/String;I)V");

                    for (auto pair : earned) {
                        key = pair.first;
                        value = pair.second;

                        jstring j_key = env->NewStringUTF(key.c_str());
                        env->CallVoidMethod(jContainer, putMethod, j_key, atoi(value.c_str()));
                        env->DeleteLocalRef(j_key);
                    }

                    jmethodID jGetResources = env->GetMethodID(jContainerClass, "getResources", "()Ljava/util/HashMap;");
                    jobject jMap = env->CallObjectMethod(jContainer, jGetResources);

                    jmethodID jEarned = env->GetMethodID(jParamsClass, "setEarned", "(Ljava/util/HashMap;)V");
                    env->CallVoidMethod(jParams, jEarned, jMap);

                    env->DeleteLocalRef(jMap);
                    env->DeleteLocalRef(jContainerClass);
                }

                if (spent.size() > 0) {
                    jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/ResourcesMapContainer");
                    jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                    jobject jContainer = env->NewObject(jContainerClass, init);

                    jmethodID putMethod = env->GetMethodID(jContainerClass, "put", "(Ljava/lang/String;I)V");

                    for (auto pair : spent) {
                        key = pair.first;
                        value = pair.second;

                        jstring j_key = env->NewStringUTF(key.c_str());
                        env->CallVoidMethod(jContainer, putMethod, j_key, atoi(value.c_str()));
                        env->DeleteLocalRef(j_key);
                    }

                    jmethodID jGetResources = env->GetMethodID(jContainerClass, "getResources", "()Ljava/util/HashMap;");
                    jobject jMap = env->CallObjectMethod(jContainer, jGetResources);

                    jmethodID jSpent = env->GetMethodID(jParamsClass, "setSpent", "(Ljava/util/HashMap;)V");
                    env->CallVoidMethod(jParams, jSpent, jMap);

                    env->DeleteLocalRef(jMap);
                    env->DeleteLocalRef(jContainerClass);
                }

                jstring j_locationName = env->NewStringUTF(locationName.c_str());

                env->CallStaticVoidMethod(jClass, jMethod, j_locationName, jParams);
                env->DeleteLocalRef(j_locationName);
                env->DeleteLocalRef(jParams);
                env->DeleteLocalRef(jParamsClass);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_currencyAccrual(int amount, const std::string& currencyName, DTDAccrualType accrualType) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "currencyAccrual";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;ILcom/devtodev/core/data/consts/AccrualType;)V");

            if (jMethod) {
                jclass jAccrualWrapper = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/CurrencyAccrualWrapper");
                jmethodID jTypeMethod = env->GetStaticMethodID(jAccrualWrapper, "getTypeFromOrdinal", "(I)Lcom/devtodev/core/data/consts/AccrualType;");
                jobject jType = env->CallStaticObjectMethod(jAccrualWrapper, jTypeMethod, accrualType);

                jstring j_currencyName = env->NewStringUTF(currencyName.c_str());

                env->CallStaticVoidMethod(jClass, jMethod, j_currencyName, amount, jType);

                env->DeleteLocalRef(j_currencyName);
                env->DeleteLocalRef(jType);
                env->DeleteLocalRef(jAccrualWrapper);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }
            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_inAppPurchase(const std::string& purchaseId, const std::string& purchaseType, int purchaseAmount, int purchasePrice,
                           const std::string& purchaseCurrency) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "inAppPurchase";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;Ljava/lang/String;IILjava/lang/String;)V");

            if (jMethod) {
                jstring j_purchaseId = env->NewStringUTF(purchaseId.c_str());
                jstring j_purchaseType = env->NewStringUTF(purchaseType.c_str());
                jstring j_purchaseCurrency = env->NewStringUTF(purchaseType.c_str());

                env->CallStaticVoidMethod(jClass, jMethod, j_purchaseId, j_purchaseType, purchaseAmount, purchasePrice, j_purchaseCurrency);

                env->DeleteLocalRef(j_purchaseId);
                env->DeleteLocalRef(j_purchaseType);
                env->DeleteLocalRef(j_purchaseCurrency);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }
            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_tutorialCompleted(int state) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "tutorialCompleted";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(I)V");

            if (jMethod) {
                env->CallStaticVoidMethod(jClass, jMethod, state);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_levelUp(int level, const std::map<std::string, int>& resourses) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "levelUp";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(ILjava/util/HashMap;)V");

            if (jMethod) {
                jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/ResourcesMapContainer");
                jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                jobject jContainer = env->NewObject(jContainerClass, init);

                jmethodID putMethod = env->GetMethodID(jContainerClass, "put", "(Ljava/lang/String;I)V");

                std::string key;
                for (auto pair : resourses) {
                    key = pair.first;

                    jstring j_key = env->NewStringUTF(key.c_str());
                    env->CallVoidMethod(jContainer, putMethod, j_key, pair.second);
                    env->DeleteLocalRef(j_key);
                }

                jmethodID jGetResources = env->GetMethodID(jContainerClass, "getResources", "()Ljava/util/HashMap;");
                jobject jMap = env->CallObjectMethod(jContainer, jGetResources);

                env->CallStaticVoidMethod(jClass, jMethod, level, jMap);

                env->DeleteLocalRef(jMap);
                env->DeleteLocalRef(jContainer);
                env->DeleteLocalRef(jContainerClass);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_setCurrentLevel(int level) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "setCurrentLevel";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(I)V");

            if (jMethod) {
                env->CallStaticVoidMethod(jClass, jMethod, level);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_realPayment(const std::string& transactionId, float inAppPrice, const std::string& inAppName, const std::string& inAppCurrencyISOCode) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "realPayment";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;FLjava/lang/String;Ljava/lang/String;)V");

            if (jMethod) {
                jstring j_transactionId = env->NewStringUTF(transactionId.c_str());
                jstring j_inAppName = env->NewStringUTF(inAppName.c_str());
                jstring j_inAppCurrencyISOCode = env->NewStringUTF(inAppCurrencyISOCode.c_str());
                env->CallStaticVoidMethod(jClass, jMethod, j_transactionId, inAppPrice, j_inAppName, j_inAppCurrencyISOCode);
                env->DeleteLocalRef(j_transactionId);
                env->DeleteLocalRef(j_inAppName);
                env->DeleteLocalRef(j_inAppCurrencyISOCode);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_socialNetworkConnect(const std::string& name) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        jclass jSocialNetworkClass = FAndroidApplication::FindJavaClass(DTD_SOCIAL_NETWORK_CLASS_NAME);
        const char* strMethod = "socialNetworkConnect";
        const char* customMethod = "Custom";

        if (!jClass) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
            return;
        }

        if (!jSocialNetworkClass) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_SOCIAL_NETWORK_CLASS_NAME);
            env->DeleteLocalRef(jClass);
            return;
        }

        jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Lcom/devtodev/core/data/consts/SocialNetwork;)V");
        jmethodID jCustomMethod =
            env->GetStaticMethodID(jSocialNetworkClass, customMethod, "(Ljava/lang/String;)Lcom/devtodev/core/data/consts/SocialNetwork;");

        if (!jMethod) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            return;
        }

        if (!jCustomMethod) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", customMethod);
            return;
        }

        jstring j_name = env->NewStringUTF(name.c_str());
        jobject j_socialNetwork = env->CallStaticObjectMethod(jSocialNetworkClass, jCustomMethod, j_name);

        env->CallStaticVoidMethod(jClass, jMethod, j_socialNetwork);
        env->DeleteLocalRef(j_name);

        env->DeleteLocalRef(jClass);
        env->DeleteLocalRef(jSocialNetworkClass);
    }

    void jni_socialNetworkPost(const std::string& name, const std::string& reason) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        jclass jSocialNetworkClass = FAndroidApplication::FindJavaClass(DTD_SOCIAL_NETWORK_CLASS_NAME);
        const char* strMethod = "socialNetworkPost";
        const char* customMethod = "Custom";

        if (!jClass) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
            return;
        }

        if (!jSocialNetworkClass) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_SOCIAL_NETWORK_CLASS_NAME);
            env->DeleteLocalRef(jClass);
            return;
        }

        jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Lcom/devtodev/core/data/consts/SocialNetwork;Ljava/lang/String;)V");
        jmethodID jCustomMethod =
            env->GetStaticMethodID(jSocialNetworkClass, customMethod, "(Ljava/lang/String;)Lcom/devtodev/core/data/consts/SocialNetwork;");

        if (!jMethod) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            return;
        }

        if (!jCustomMethod) {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", customMethod);
            return;
        }

        jstring j_name = env->NewStringUTF(name.c_str());
        jstring j_reason = env->NewStringUTF(reason.c_str());
        jobject j_socialNetwork = env->CallStaticObjectMethod(jSocialNetworkClass, jCustomMethod, j_name);

        env->CallStaticVoidMethod(jClass, jMethod, j_socialNetwork, j_reason);
        env->DeleteLocalRef(j_name);

        env->DeleteLocalRef(jClass);
        env->DeleteLocalRef(jSocialNetworkClass);
    }

    void jni_setUserId(const std::string& name) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "setUserId";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;)V");

            if (jMethod) {
                jstring j_name = env->NewStringUTF(name.c_str());
                env->CallStaticVoidMethod(jClass, jMethod, j_name);
                env->DeleteLocalRef(j_name);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_replaceUserId(const std::string& from, const std::string& to) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "replaceUserId";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/lang/String;Ljava/lang/String;)V");

            if (jMethod) {
                jstring j_from = env->NewStringUTF(from.c_str());
                jstring j_to = env->NewStringUTF(to.c_str());
                env->CallStaticVoidMethod(jClass, jMethod, j_from, j_to);
                env->DeleteLocalRef(j_from);
                env->DeleteLocalRef(j_to);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_referrer(const std::map<std::string, std::string>& entries) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "referrer";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Ljava/util/HashMap;)V");

            if (jMethod) {
                jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/ReferrerWrapper");
                jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                jobject jContainer = env->NewObject(jContainerClass, init);

                jmethodID putMethod = env->GetMethodID(jContainerClass, "addProperty", "(Ljava/lang/String;Ljava/lang/String;)V");

                std::string key;
                std::string value;
                for (auto pair : entries) {
                    key = pair.first;
                    value = pair.second;

                    jstring j_key = env->NewStringUTF(key.c_str());
                    jstring j_value = env->NewStringUTF(value.c_str());
                    env->CallVoidMethod(jContainer, putMethod, j_key, j_value);
                    env->DeleteLocalRef(j_key);
                    env->DeleteLocalRef(j_value);
                }

                jmethodID jGetResources = env->GetMethodID(jContainerClass, "getMap", "()Ljava/util/HashMap;");
                jobject jMap = env->CallObjectMethod(jContainer, jGetResources);

                env->CallStaticVoidMethod(jClass, jMethod, jMap);

                env->DeleteLocalRef(jMap);
                env->DeleteLocalRef(jContainer);
                env->DeleteLocalRef(jContainerClass);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_setTrackingAvailability(bool isAllowed) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "setTrackingAvailability";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Z)V");

            if (jMethod) {
                env->CallStaticVoidMethod(jClass, jMethod, isAllowed);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    const char* jni_getUserId() {
        std::string result;

        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jClass = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);
        const char* strMethod = "getUserId";

        if (jClass) {
            jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "()Ljava/lang/String;");

            if (jMethod) {
                jstring j_userId = (jstring)env->CallStaticObjectMethod(jClass, jMethod);
                const char* s = env->GetStringUTFChars(j_userId, 0);
                result = s;
                env->ReleaseStringUTFChars(j_userId, s);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", strMethod);
            }

            env->DeleteLocalRef(jClass);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }

        return result.c_str();
    }

    void jni_people_cheater(bool cheater) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jCheaterMethod = env->GetMethodID(jPeopleClass, "setCheater", "(Z)V");

                    if (jCheaterMethod) {
                        env->CallVoidMethod(people, jCheaterMethod, cheater); 
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "setCheater");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_age(int age) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jAgeMethod = env->GetMethodID(jPeopleClass, "setAge", "(I)V");

                    if (jAgeMethod) {
                        env->CallVoidMethod(people, jAgeMethod, age); 
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "setAge");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_gender(DTDGender gender) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jGenderMethod = env->GetMethodID(jPeopleClass, "setGender", "(Lcom/devtodev/core/data/consts/Gender;)V");

                    if (jGenderMethod) {
                        jclass jGenderWrapper = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/GenderWrapper");
                        jmethodID jTypeMethod = env->GetStaticMethodID(jGenderWrapper, "getGenderFromOrdinal", "(I)Lcom/devtodev/core/data/consts/Gender;");
                        jobject jType = env->CallStaticObjectMethod(jGenderWrapper, jTypeMethod, gender);

                        env->CallVoidMethod(people, jGenderMethod, jType);
                        env->DeleteLocalRef(jType);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "setGender");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_email(const std::string& email) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jEmailMethod = env->GetMethodID(jPeopleClass, "setEmail", "(Ljava/lang/String;)V");

                    if (jEmailMethod) {
                        jstring j_email = env->NewStringUTF(email.c_str());
                        env->CallVoidMethod(people, jEmailMethod, j_email); 
                        env->DeleteLocalRef(j_email);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "setEmail");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_phone(const std::string& phone) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jPhoneMethod = env->GetMethodID(jPeopleClass, "setPhone", "(Ljava/lang/String;)V");

                    if (jPhoneMethod) {
                        jstring j_string = env->NewStringUTF(phone.c_str());
                        env->CallVoidMethod(people, jPhoneMethod, j_string); 
                        env->DeleteLocalRef(j_string);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "setPhone");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_photo(const std::string& photo) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jPhotoMethod = env->GetMethodID(jPeopleClass, "setPhoto", "(Ljava/lang/String;)V");

                    if (jPhotoMethod) {
                        jstring j_string = env->NewStringUTF(photo.c_str());
                        env->CallVoidMethod(people, jPhotoMethod, j_string); 
                        env->DeleteLocalRef(j_string);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "setPhoto");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_name(const std::string& name) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jNameMethod = env->GetMethodID(jPeopleClass, "setName", "(Ljava/lang/String;)V");

                    if (jNameMethod) {
                        jstring j_string = env->NewStringUTF(name.c_str());
                        env->CallVoidMethod(people, jNameMethod, j_string); 
                        env->DeleteLocalRef(j_string);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "setName");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_setUserData(const std::map<std::string, std::string>& Attributes) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jSetMethod = env->GetMethodID(jPeopleClass, "setUserData", "(Ljava/util/Map;)V");

                    if (jSetMethod) {
                        jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/StringMapContainer");
                        jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                        jobject jContainer = env->NewObject(jContainerClass, init);

                        jmethodID putMethod = env->GetMethodID(jContainerClass, "put", "(Ljava/lang/String;Ljava/lang/String;)V");

                        std::string key;
                        std::string value;
                        for (auto pair : Attributes) {
                            key = pair.first;
                            value = pair.second;

                            jstring j_key = env->NewStringUTF(key.c_str());
                            jstring j_value = env->NewStringUTF(value.c_str());
                            env->CallVoidMethod(jContainer, putMethod, j_key, j_value);
                            env->DeleteLocalRef(j_key);
                            env->DeleteLocalRef(j_value);
                        }

                        jmethodID jGetResources = env->GetMethodID(jContainerClass, "getResources", "()Ljava/util/HashMap;");
                        jobject jMap = env->CallObjectMethod(jContainer, jGetResources);

                        env->CallVoidMethod(people, jSetMethod, jMap);

                        env->DeleteLocalRef(jMap);
                        env->DeleteLocalRef(jContainer);
                        env->DeleteLocalRef(jContainerClass);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "setUserData");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_unsetUserData(const std::vector<std::string>& Attributes) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jUnsetMethod = env->GetMethodID(jPeopleClass, "unsetUserData", "(Ljava/util/List;)V");

                    if (jUnsetMethod) {
                        jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/StringListWrapper");
                        jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                        jobject jContainer = env->NewObject(jContainerClass, init);

                        jmethodID addMethod = env->GetMethodID(jContainerClass, "add", "(Ljava/lang/String;)V");

                        for (std::string key : Attributes) {
                            jstring j_key = env->NewStringUTF(key.c_str());
                            env->CallVoidMethod(jContainer, addMethod, j_key);
                            env->DeleteLocalRef(j_key);
                        }

                        jmethodID jGetList = env->GetMethodID(jContainerClass, "getList", "()Ljava/util/List;");
                        jobject jList = env->CallObjectMethod(jContainer, jGetList);

                        env->CallVoidMethod(people, jUnsetMethod, jList);

                        env->DeleteLocalRef(jList);
                        env->DeleteLocalRef(jContainer);
                        env->DeleteLocalRef(jContainerClass);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "unsetUserData");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_clearUserData() {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jClearMethod = env->GetMethodID(jPeopleClass, "clearUserData", "()V");

                    if (jClearMethod) {
                        env->CallVoidMethod(people, jClearMethod); 
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "clearUserData");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_incrementUserData(const std::map<std::string, int>& Attributes) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jIncrementMethod = env->GetMethodID(jPeopleClass, "increment", "(Ljava/util/Map;)V");

                    if (jIncrementMethod) {
                        jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/ResourcesMapContainer");
                        jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                        jobject jContainer = env->NewObject(jContainerClass, init);

                        jmethodID putMethod = env->GetMethodID(jContainerClass, "put", "(Ljava/lang/String;I)V");

                        std::string key;
                        for (auto pair : Attributes) {
                            key = pair.first;

                            jstring j_key = env->NewStringUTF(key.c_str());
                            env->CallVoidMethod(jContainer, putMethod, j_key, pair.second);
                            env->DeleteLocalRef(j_key);
                        }

                        jmethodID jGetResources = env->GetMethodID(jContainerClass, "getResources", "()Ljava/util/HashMap;");
                        jobject jMap = env->CallObjectMethod(jContainer, jGetResources);

                        env->CallVoidMethod(people, jIncrementMethod, jMap);

                        env->DeleteLocalRef(jMap);
                        env->DeleteLocalRef(jContainer);
                        env->DeleteLocalRef(jContainerClass);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "increment");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_appendUserData(const std::map<std::string, std::string>& Attributes) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jSetMethod = env->GetMethodID(jPeopleClass, "append", "(Ljava/util/Map;)V");

                    if (jSetMethod) {
                        jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/StringMapContainer");
                        jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                        jobject jContainer = env->NewObject(jContainerClass, init);

                        jmethodID putMethod = env->GetMethodID(jContainerClass, "put", "(Ljava/lang/String;Ljava/lang/String;)V");

                        std::string key;
                        std::string value;
                        for (auto pair : Attributes) {
                            key = pair.first;
                            value = pair.second;

                            jstring j_key = env->NewStringUTF(key.c_str());
                            jstring j_value = env->NewStringUTF(value.c_str());
                            env->CallVoidMethod(jContainer, putMethod, j_key, j_value);
                            env->DeleteLocalRef(j_key);
                            env->DeleteLocalRef(j_value);
                        }

                        jmethodID jGetResources = env->GetMethodID(jContainerClass, "getResources", "()Ljava/util/HashMap;");
                        jobject jMap = env->CallObjectMethod(jContainer, jGetResources);

                        env->CallVoidMethod(people, jSetMethod, jMap);

                        env->DeleteLocalRef(jMap);
                        env->DeleteLocalRef(jContainer);
                        env->DeleteLocalRef(jContainerClass);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "append");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }

    void jni_people_unionUserData(const std::map<std::string, std::string>& Attributes) {
        JNIEnv* env = FAndroidApplication::GetJavaEnv();
        jclass jDevToDev = FAndroidApplication::FindJavaClass(DTD_CLASS_NAME);

        if (jDevToDev) {
            jmethodID jPeopleMethod = env->GetStaticMethodID(jDevToDev, "getActivePlayer", "()Lcom/devtodev/core/logic/people/People;");

            if (jPeopleMethod) {
                jobject people = env->CallStaticObjectMethod(jDevToDev, jPeopleMethod);
                jclass jPeopleClass = FAndroidApplication::FindJavaClass(DTD_PEOPLE_CLASS_NAME);

                if (jPeopleClass) {
                    jmethodID jSetMethod = env->GetMethodID(jPeopleClass, "union", "(Ljava/util/Map;)V");

                    if (jSetMethod) {
                        jclass jContainerClass = FAndroidApplication::FindJavaClass("com/devtodev/core/utils/ue4/StringMapContainer");
                        jmethodID init = env->GetMethodID(jContainerClass, "<init>", "()V");
                        jobject jContainer = env->NewObject(jContainerClass, init);

                        jmethodID putMethod = env->GetMethodID(jContainerClass, "put", "(Ljava/lang/String;Ljava/lang/String;)V");

                        std::string key;
                        std::string value;
                        for (auto pair : Attributes) {
                            key = pair.first;
                            value = pair.second;

                            jstring j_key = env->NewStringUTF(key.c_str());
                            jstring j_value = env->NewStringUTF(value.c_str());
                            env->CallVoidMethod(jContainer, putMethod, j_key, j_value);
                            env->DeleteLocalRef(j_key);
                            env->DeleteLocalRef(j_value);
                        }

                        jmethodID jGetResources = env->GetMethodID(jContainerClass, "getResources", "()Ljava/util/HashMap;");
                        jobject jMap = env->CallObjectMethod(jContainer, jGetResources);

                        env->CallVoidMethod(people, jSetMethod, jMap);

                        env->DeleteLocalRef(jMap);
                        env->DeleteLocalRef(jContainer);
                        env->DeleteLocalRef(jContainerClass);
                    } else {
                        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "union");
                    }

                    env->DeleteLocalRef(jPeopleClass);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_PEOPLE_CLASS_NAME);
                }
                env->DeleteLocalRef(people);
            } else {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", "getActivePlayer");
            }

            env->DeleteLocalRef(jDevToDev);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", DTD_CLASS_NAME);
        }
    }
    }
} // namespace devtodev
