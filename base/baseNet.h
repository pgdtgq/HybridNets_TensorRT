/**
 * @brief 
 * @author      xiaowenxuan
 * @date        2022/6/24 9:53      
 * @copyright   Copyright （C）2022 xiaowenxuan All rights reserved. 
 *              email:18710760109@163.com
 */

#ifndef HYBRIDNETS_TENSORRT_BASE_NET_H
#define HYBRIDNETS_TENSORRT_BASE_NET_H

#include "trt/Trt.h"
#include "cuda_runtime_api.h"
#include "opencv2/opencv.hpp"
#include "opencv2/dnn/dnn.hpp"
#include "header.hpp"
#include "process_image.hpp"

using namespace cv;
using namespace std;

class BaseNet {
protected:
    Trt *net;
public:
    BaseNet()  {
        net = new Trt();
    }

    virtual ~BaseNet() {
        delete net;
    }

    BaseNet(const BaseNet &) = delete;

    BaseNet &operator=(const BaseNet &) = delete;

    virtual void init() = 0;

    virtual void preProcess() = 0;

    virtual void postProcess() = 0;

    virtual void forward() {
        this->preProcess();
        net->Forward();
        this->postProcess();
    }

    virtual void setInput(Mat & image) = 0;

public:
    virtual void printModelInfo() {
        int input_size = net->GetNbInputBindings();
        int output_size = net->GetNbOutputBindings();

        std::cout << "============================" << std::endl;
        std::cout << "input_size:" << input_size << std::endl;
        for (int i = 0; i < input_size; ++i) {
            this->printBindings(i);
        }
        std::cout << "============================" << std::endl;
        std::cout << "output_size:" << output_size << std::endl;
        for (int j = input_size; j < input_size + output_size; ++j) {
            this->printBindings(j);
        }
    }

    /**
     * @brief 根据索引打印模型信息，包括名字，维度，大小，数据类型
     * @param index 索引
     */
    virtual void printBindings(int index) {
        std::string name;
        nvinfer1::DataType dataType;
        size_t size;
        nvinfer1::Dims dims;
        name = net->GetBindingName(index);
        dims = net->GetBindingDims(index);
        size = net->GetBindingSize(index);
        dataType = net->GetBindingDataType(index);
        cout << string_format("{name %d:%s}", index, name.c_str());
        cout << string_format("{Dims:%d}", dims.nbDims);
        cout << string_format("{size:%d}", size) << endl;
    }

};

#endif //HYBRIDNETS_TENSORRT_BASE_NET_H
