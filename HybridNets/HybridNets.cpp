/**
 * @brief 
 * @author      xiaowenxuan
 * @date        2022/6/17 16:15      
 * @copyright   Copyright （C）2022 xiaowenxuan All rights reserved. 
 *              email:18710760109@163.com
 */

#include <bitset>
#include "HybridNets.h"
#include "cuda_runtime_api.h"
#include "opencv2/opencv.hpp"
HybridNets::HybridNets() {

}

HybridNets::~HybridNets() {
    delete mNet;
}

void HybridNets::run() {
//    mNet->BuildEngine("../models/hybridnets_512x640.onnx", "../models/hybridnets_512x640.trt");
    SetDevice(3);

//    mNet->AddDynamicShapeProfile("input",{1,3,128,128}, {1,3,256,256}, {1,3,512,640});
    mNet->DeserializeEngine("../models/hybridnets_512x640.trt");
    int input_size = mNet->GetNbInputBindings();
    int output_size = mNet->GetNbOutputBindings();

    std::cout << "============================" << std::endl;
    std::cout << "input_size:" << input_size << std::endl;
    for (int i = 0; i < input_size; ++i) {
        this->print_info(i);
    }
    std::cout << "============================" << std::endl;
    std::cout << "output_size:" << output_size << std::endl;
    for (int j = input_size; j < input_size + output_size; ++j) {
        this->print_info(j);
    }

    float *image = (float*)cv::imread("../data/images/1.jpg").data;

    mNet->Forward();
}

void HybridNets::print_info(int index) {
    std::string name;
    nvinfer1::DataType dataType;
    size_t size;
    nvinfer1::Dims dims;
    name = mNet->GetBindingName(index);
    dims = mNet->GetBindingDims(index);
    size = mNet->GetBindingSize(index);
    dataType = mNet->GetBindingDataType(index);
    cout << string_format("{name %d:%s}", index, name.c_str());
    cout << string_format("{Dims:%d}", dims.nbDims);
    cout << string_format("{size:%d}", size) << endl;
}
