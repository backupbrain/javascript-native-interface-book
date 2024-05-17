#include <jni.h>
#include <jsi/jsi.h>
// #include <android/log.h>
#include "exampleJsiLibrary.h"
#include <iostream>

using namespace facebook::jsi;
using namespace std;

extern "C" JNIEXPORT void JNICALL
Java_com_yourprojectname_ExampleModule_initialize(JNIEnv *env, jobject clazz, jlong jsiPtr)
{
    // __android_log_write(ANDROID_LOG_ERROR, "Tag", "installing JSI functions");
    // Runtime *runtime = reinterpret_cast<Runtime *>(jsiPtr);
    Runtime *runtime = reinterpret_cast<Runtime *>(jsiPtr);
    cout << runtime << endl;
    if (runtime)
    {
        MyJsiNamespace::installExampleJsiLibrary(*runtime);
    }
}
