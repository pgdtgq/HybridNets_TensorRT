#include "HybridNets.h"

void HybridNets::init() {
    SetDevice(3);
//    net->BuildEngine("../data/models/hybridnets-512-640.onnx", "../data/models/hybridnets-512-640.trt");
    net->DeserializeEngine("../data/models/hybridnets-512-640.trt");
    printModelInfo();
}

void HybridNets::preProcess() {
    det_mat = image_origin.clone();
    cvtColor(det_mat, det_mat, COLOR_BGR2RGB);
    resize(det_mat, det_mat, Size(640, 512));
    float *input = normalizeMat(det_mat, Mean, StdDev);
    net->CopyFromHostToDevice(input, 0);
    delete input;
}

void HybridNets::postProcess() {
    net->CopyFromDeviceToHost(out_seg, 1);
    net->CopyFromDeviceToHost(out_regression, 2);
    net->CopyFromDeviceToHost(out_classification, 3);
    net->CopyFromDeviceToHost(anchors, 4);

    //处理seg
    seg_mat = pointer2Mat(out_seg.data(), seg_mat);
    seg_decode = seg2decode(seg_mat, seg_decode);

    //处理detect
    pair<vector<cv::Rect>, vector<float>> boxs_scores = boxTransform(anchors, out_regression, out_classification,
                                                                     cv::Size(640, 512));
    vector<int> nms_result;
    dnn::NMSBoxes(boxs_scores.first, boxs_scores.second, 0.25, 0.3, nms_result);

    box_scores_afternms.first.clear();
    box_scores_afternms.second.clear();
    for (int i = 0; i < nms_result.size(); ++i) {
        box_scores_afternms.first.emplace_back(boxs_scores.first[nms_result[i]]);
        box_scores_afternms.second.emplace_back(boxs_scores.second[nms_result[i]]);
    }

}

void HybridNets::saveResult(string fileName="./result", bool save = false) {
    //visualize
    cv::resize(seg_decode, seg_origin, cv::Size(image_origin.cols, image_origin.rows));
    Mat det_temp;
    cv::cvtColor(det_mat, det_temp, cv::COLOR_RGB2BGR);
    for (int k = 0; k < box_scores_afternms.first.size(); ++k) {
        cv::rectangle(det_temp, box_scores_afternms.first[k], cv::Scalar(255, 0, 0));
    }
    cv::resize(det_temp, det_temp, cv::Size(image_origin.cols, image_origin.rows));
    det_origin = det_temp;
    if (save) {
        cv::imwrite(fileName + "_det.jpg", det_origin);
        cv::imwrite(fileName + "_seg.jpg", seg_origin);
    }

}

void HybridNets::setInput(Mat &image) {
    this->image_origin = image;
}

HybridNets::HybridNets() : BaseNet() {
    seg_mat.create(512, 640, CV_32FC(3));
    seg_decode.create(512, 640, CV_8UC3);
    out_seg.resize(640 * 512 * 3);
    out_regression.resize(61380 * 4);
    out_classification.resize(61380);
    anchors.resize(61380 * 4);
    init();
}

HybridNets::~HybridNets() {

}


