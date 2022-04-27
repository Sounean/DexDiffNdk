#include <jni.h>
#include <string>

//告诉在某个地方有实现patch方法(外层还套一个是告诉c++兼容c)
extern "C"{
extern int patchMain(int argc,char * argv[]);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_dexdiffndk_BsPatchUtils_patch(JNIEnv *env, jclass clazz,
                                               jstring old_apk,jstring new_apk,
                                               jstring patch_) {
    //bspatch oldfile newfile patchfile 其实bspatch也算一个参数了
    int argc = 4;
    char * argv[argc];
    argv[0] = "bspatch";

    argv[1] = (char *) (env->GetStringUTFChars(old_apk, 0));    // 如果是java方式传进来的，要这么转换成c++的
    argv[2] = (char *) (env->GetStringUTFChars(new_apk, 0));    // char*相当于c++中的字符串
    argv[3] = (char *) (env->GetStringUTFChars(patch_, 0));

    //此处executePathch()就是上面我们修改出的
    int result = patchMain(argc, argv);  // 返回0才表示成功

    // 上面把c转成c++的，用完后要释放一下
    env->ReleaseStringUTFChars(old_apk, argv[1]);
    env->ReleaseStringUTFChars(new_apk, argv[2]);
    env->ReleaseStringUTFChars(patch_, argv[3]);

    return result;
}