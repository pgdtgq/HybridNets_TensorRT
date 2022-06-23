#include <bitset>
#include "HybridNets.h"
#include "cuda_runtime_api.h"
#include "opencv2/opencv.hpp"
#include "opencv2/dnn/dnn.hpp"

/**
 * @brief 构造函数
 */
HybridNets::HybridNets() {

}

HybridNets::~HybridNets() {
    delete mNet;
}

void HybridNets::run() {
    mNet->BuildEngine("../data/models/hybridnets-512-640.onnx", "../data/models/hybridnets-512-640.trt");
//    SetDevice(3);
//    mNet->DeserializeEngine("../data/models/hybridnets-512-640.trt");
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

    cv::Mat image = cv::imread("../data/images/1.jpg");
    cv::Mat image_origin = image.clone();
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    cv::resize(image, image, cv::Size(640, 512));
    float *input = normalize(image, Mean, StdDev);

    mNet->CopyFromHostToDevice(input, 0);
    mNet->Forward();

    vector<float> out_seg(image.rows * image.cols * image.channels(), 0.0f);
    vector<float> out_regression(61380 * 4, 0.0f);
    vector<float> out_classification(61380, 0.0f);
    vector<float> anchors(61380 * 4, 0.0f);
    mNet->CopyFromDeviceToHost(out_seg, 1);
    mNet->CopyFromDeviceToHost(out_regression, 2);
    mNet->CopyFromDeviceToHost(out_classification, 3);
    mNet->CopyFromDeviceToHost(anchors, 4);

    cv::Mat seg_mat;
    cv::Mat seg_decode;
    seg_mat.create(image.rows, image.cols, CV_32FC(3));
    seg_decode.create(image.rows, image.cols, CV_8UC3);


    //处理seg
    seg_mat = pointer2Mat(out_seg.data(), seg_mat);
    seg_decode = seg2decode(seg_mat, seg_decode);


    //处理detect
    pair<vector<cv::Rect>, vector<float>> boxs_scores = boxTransform(anchors, out_regression, out_classification,
                                                                     cv::Size(640, 512));
    vector<int> nms_result;
    cv::dnn::NMSBoxes(boxs_scores.first, boxs_scores.second, 0.25, 0.3, nms_result);

    //visualize
    cv::resize(seg_decode, seg_decode, cv::Size(image_origin.cols, image_origin.rows));
    cv::imwrite("./1_seg.jpg", seg_decode);

    for (int k = 0; k < nms_result.size(); ++k) {
        cv::rectangle(image, boxs_scores.first[nms_result[k]], cv::Scalar(239, 239, 239));
    }
    cv::resize(image, image, cv::Size(image_origin.cols, image_origin.rows));
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
    cv::imwrite("./1_det.jpg", image);

//    cv::namedWindow("origin");
//    cv::imshow("origin", image_origin);
//    cv::namedWindow("seg_decode");
//    cv::imshow("seg_decode", seg_decode);
//    if(cv::waitKey(10000000)==27) return;
    return;
}

/**
 * @brief 根据索引打印模型信息，包括名字，维度，大小，数据类型
 * @param index 索引
 */
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
