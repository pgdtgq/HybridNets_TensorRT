<a name="W6OJo"></a>
# HybridNets_TensorRT
本项目基于HybridNets（[github](https://github.com/datvuthanh/HybridNets)）和tiny-tensorrt（[github](https://github.com/zerollzeng/tiny-tensorrt)）完成HybridNets模型的推理，包括输入预处理和模型输出后处理，以及可视化。
<a name="GzLN1"></a>
## 1.HybridNets Network Architecture
![image.png](https://cdn.nlark.com/yuque/0/2022/png/1531709/1655979601366-c4b0f517-63b8-4206-a060-9ea03837285c.png#clientId=u6fc22222-4637-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=964&id=ubf14a469&margin=%5Bobject%20Object%5D&name=image.png&originHeight=964&originWidth=1946&originalType=binary&ratio=1&rotation=0&showTitle=false&size=570590&status=done&style=none&taskId=u96400899-05c8-4b91-8d3b-84026494802&title=&width=1946)
<a name="cqDDM"></a>
## 2.Structure
```
./
├── base							基础util
│   ├── header.hpp
│   └── process_image.hpp
├── bin								二进制文件目录
│   ├── 1_det.jpg
│   ├── 1_seg.jpg
│   ├── HybridNets_TensorRT
│   ├── libhybridnetsd.so
│   └── log
├── cmake							cmake module目录
├── CMakeLists.txt				
├── data										
│   ├── images
│   ├── models
│   └── videos
├── doc								api文档
│   └── html
├── Doxyfile
├── HybridNets
│   ├── HybridNets.cpp
│   └── HybridNets.h
├── main
│   └── main.cpp
├── test
│   └── hybridnet_test.hpp			boost test
└── trt
```
<a name="K68bi"></a>
## 3.Usage
3..1参考cmake目录安装指定库，并在CmakeLists.txt指定库路径
```
set(LIB_PATH /opt/lib)
```
3.2导出onnx模型
参考[https://zenn.dev/pinto0309/scraps/b077a1bcac9ff4](https://zenn.dev/pinto0309/scraps/b077a1bcac9ff4)，导出onnx模型
可以直接使用data/models/hybridnets-512-640.onnx的模型
3.3编译
```
mkdir build
cd build
cmake ..
make
```
3.4运行
```
./bin/HybridNets_TensorRT --run_test=hybridnet_suite/run_case
```
<a name="SYKVN"></a>
## 4.结果
原图
![1.jpg](https://cdn.nlark.com/yuque/0/2022/jpeg/1531709/1655983975788-cdb40e56-9d1d-4b3e-96e5-23b240bd36a8.jpeg#clientId=u6fc22222-4637-4&crop=0&crop=0&crop=1&crop=1&from=drop&id=u88c2637c&margin=%5Bobject%20Object%5D&name=1.jpg&originHeight=720&originWidth=1280&originalType=binary&ratio=1&rotation=0&showTitle=false&size=210488&status=done&style=none&taskId=ub5f510c0-1370-408c-a264-c5990a370dc&title=)
检测结果![1_det.jpg](https://cdn.nlark.com/yuque/0/2022/jpeg/1531709/1655983958476-f8f47089-018f-4c66-9456-1b015610b776.jpeg#clientId=u6fc22222-4637-4&crop=0&crop=0&crop=1&crop=1&from=drop&id=ubca00c0d&margin=%5Bobject%20Object%5D&name=1_det.jpg&originHeight=720&originWidth=1280&originalType=binary&ratio=1&rotation=0&showTitle=false&size=219473&status=done&style=none&taskId=ue1177235-5556-447b-a25b-f27efeb8ce8&title=)
分割结果![1_seg.jpg](https://cdn.nlark.com/yuque/0/2022/jpeg/1531709/1655983958381-f6aaf618-36c3-415b-a3f1-d8bdaa2604e4.jpeg#clientId=u6fc22222-4637-4&crop=0&crop=0&crop=1&crop=1&from=drop&id=u7feb0236&margin=%5Bobject%20Object%5D&name=1_seg.jpg&originHeight=720&originWidth=1280&originalType=binary&ratio=1&rotation=0&showTitle=false&size=28113&status=done&style=none&taskId=u76a51a06-3fad-46ba-a0d0-88d450ace13&title=)
<a name="dES6o"></a>
## 5.API 文档
本项目采用doxygen生成api 文档
```
doxygen Doxyfile
```
打开doc/html/index.html就可查看api文档
<a name="C2osG"></a>
## Acknowledgements

- [https://github.com/datvuthanh/HybridNets](https://github.com/datvuthanh/HybridNets)
- [https://github.com/zerollzeng/tiny-tensorrt](https://github.com/zerollzeng/tiny-tensorrt)
- [https://github.com/ibaiGorordo/ONNX-HybridNets-Multitask-Road-Detection](https://github.com/ibaiGorordo/ONNX-HybridNets-Multitask-Road-Detection)
- [https://github.com/PINTO0309/PINTO_model_zoo/tree/main/276_HybridNets](https://github.com/PINTO0309/PINTO_model_zoo/tree/main/276_HybridNets)
- [https://zenn.dev/pinto0309/scraps/b077a1bcac9ff4](https://zenn.dev/pinto0309/scraps/b077a1bcac9ff4)

