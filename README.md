<!--
 * @Author: https://github.com/haohaoalt
 * @Date: 2023-08-16 14:59:37
 * @LastEditors: haohaoalt haohaoalt@163.com
 * @LastEditTime: 2023-08-16 17:35:09
 * @FilePath: /someip_demo/README.md
 * @Description: 
 * Copyright (c) 2023 by haohaoalt@163.com, All Rights Reserved. 
-->
# someip_demo
可作为vsomeip的使用示例

Dependencies
编译和安装boost：
```
cd boost_1_72_0
./bootstrap.sh
./b2 
```
The Boost C++ Libraries were successfully built!

The following directory should be added to compiler include paths:

    /home/slam007/Dev/someip_demo/boost_1_72_0

The following directory should be added to linker library paths:

    /home/slam007/Dev/someip_demo/boost_1_72_0/stage/lib

编译和安装vsomeip：
```
git clone https://github.com/GENIVI/vsomeip.git
cd vsomeip
mkdir build
cd build
cmake -DENABLE_SIGNAL_HANDLING=1 -DDIAGNOSIS_ADDRESS=0x10 ..
make
sudo make install

```

Compilation
```
mkdir build
cd build
cmake ..
make
```
export LD_LIBRARY_PATH=":/usr/local/lib/:/home/slam007/Dev/someip_demo/vsomeip/build/:/home/slam007/Dev/someip_demo/boost_1_72_0/stage/lib"