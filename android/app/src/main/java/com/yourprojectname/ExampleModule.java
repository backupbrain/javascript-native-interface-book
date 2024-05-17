package com.yourprojectname;

import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;

class ExampleModule extends ReactContextBaseJavaModule {
    static {
        System.loadLibrary("exampleJsiLibrary");
    }

    private static native void initialize(long jsiPtr, String docDir);
    private static native void destruct();

    public ExampleModule(ReactApplicationContext reactContext) {
        super(reactContext);
        Log.d("ExampleModule", "instantiating ExampleModulePackage");
    }

    @NonNull
    @Override
    public String getName() {
        return "ExampleJsiModuleName";
    }


    @NonNull
    @Override
    public void initialize() {
        Log.d("ExampleModule", "initializing ExampleModule.super");
        super.initialize();

        Log.d("ExampleModule", "initializing ExampleModule");
        ExampleModule.initialize(
                this.getReactApplicationContext().getJavaScriptContextHolder().get(),
                this.getReactApplicationContext().getFilesDir().getAbsolutePath()
        );
    }

    @Override
    public void onCatalystInstanceDestroy() {
        ExampleModule.destruct();
    }
}