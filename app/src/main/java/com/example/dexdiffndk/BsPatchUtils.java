package com.example.dexdiffndk;

public class BsPatchUtils {

    static{
        System.loadLibrary("dexdiffndk");   // 此处传入生成后的so文件名字
    }
//
    public static native int patch(String oldApk,String newApk,String patchFile);  // 从上面so文件中去找该方法. alter+回车，让as自动生成代码(在CMakeLists中)


}
