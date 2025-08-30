## 编译
需要NDK21、JDK11，编译完成后会在`libraries/mars_xlog_sdk/libs`目录下生成.so文件
```
export NDK_ROOT=~/dev/Android/sdk/ndk/21.4.7075529
export JAVA_HOME=/Library/Java/JavaVirtualMachines/temurin-11.jdk/Contents/Home
export PATH=$JAVA_HOME/bin:$PATH

# 选择3. Clean && build xlog.
python build_android.py
```

## 发布到本地
发布到本地后，输出构建物在`~/.m2/repository/com/tencent/mars`，可复制到本地工程`mavenLocal`文件夹
```
./gradlew --stop        # 杀掉旧的 Gradle Daemon
./gradlew -v            # 确认 JVM 已经是 11.x
./gradlew :libraries:mars_xlog_sdk:publishToMavenLocal -PskipJavadoc
```

## 使用
```
implementation("com.tencent.mars:mars-xlog:1.2.7-beta01")
```