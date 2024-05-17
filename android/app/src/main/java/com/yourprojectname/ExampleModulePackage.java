package com.yourprojectname;

import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ViewManager;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class ExampleModulePackage implements ReactPackage {

    @NonNull
    @Override
    public List<NativeModule> createNativeModules(@NonNull ReactApplicationContext reactContext) {

        Log.d("ExampleModulePackage", "createNativeModules()");
        return Arrays.<NativeModule>asList(new ExampleModule(reactContext));
    }

    @NonNull
    @Override
    public List<ViewManager> createViewManagers(@NonNull ReactApplicationContext reactContext) {
        Log.d("ExampleModulePackage", "createViewManagers()");
        return Collections.emptyList();
    }
}

