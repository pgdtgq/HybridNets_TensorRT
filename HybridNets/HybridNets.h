/**
 * @brief 
 * @author      xiaowenxuan
 * @date        2022/6/24 10:33      
 * @copyright   Copyright （C）2022 xiaowenxuan All rights reserved. 
 *              email:18710760109@163.com
 */

#ifndef HYBRIDNETS_TENSORRT_HYBRIDNETS_H
#define HYBRIDNETS_TENSORRT_HYBRIDNETS_H

#include "baseNet.h"

class HybridNets : public BaseNet {
private:
    vector<float> out_seg;
    vector<float> out_regression;
    vector<float> out_classification;
    vector<float> anchors;
    float Mean[3] = {0.485f, 0.456f, 0.406f};
    float StdDev[3] = {0.229f, 0.224f, 0.225f};
public:
    Mat image_origin;
    Mat det_origin;
    Mat seg_origin;
    Mat det_mat;
    Mat seg_mat;
    Mat seg_decode;

    pair<vector<cv::Rect>, vector<float>> box_scores_afternms;
public:
    HybridNets();

    virtual ~HybridNets();

    void init() override;

    void preProcess() override;

    void postProcess() override;

    void saveResult(string fileName,bool save);

    void setInput(Mat &image) override;

};


#endif //HYBRIDNETS_TENSORRT_HYBRIDNETS_H
