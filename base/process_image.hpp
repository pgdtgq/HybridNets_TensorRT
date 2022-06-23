/**
 * @brief 
 * @author      xiaowenxuan
 * @date        2022/6/21 18:28      
 * @copyright   Copyright （C）2022 xiaowenxuan All rights reserved. 
 *              email:18710760109@163.com
 */

#ifndef HYBRIDNETS_TENSORRT_PROCESS_IMAGE_HPP
#define HYBRIDNETS_TENSORRT_PROCESS_IMAGE_HPP

#include "opencv2/opencv.hpp"
#include "opencv2/dnn/dnn.hpp"

static const int map_[7][3] = {{0,   0,   0},
                               {128, 0,   0},
                               {0,   128, 0},
                               {0,   0,   128},
                               {128, 128, 0},
                               {128, 0,   128},
                               {0,   128, 0}};

float *normalize(cv::Mat img, float mean[], float std[]) {
    float *data;
    data = static_cast<float *>(calloc(img.rows * img.cols * img.channels(), sizeof(float)));

    for (int c = 0; c < img.channels(); ++c) {
        for (int i = 0; i < img.rows; ++i) {
            cv::Vec3b *p1 = img.ptr<cv::Vec3b>(i);
            for (int j = 0; j < img.cols; ++j) {
                data[c * img.rows * img.cols + i * img.cols + j] = ((float) p1[j][c] / 255. - mean[c]) / std[c];
            }
        }
    }
    return data;
}

cv::Mat pointer2Mat(float *prob, cv::Mat out) {
    int rows = out.rows;
    int cols = out.cols;
    for (int i = 0; i < rows; ++i) {
        cv::Vec<float, 3> *p1 = out.ptr<cv::Vec<float, 3>>(i);
        for (int j = 0; j < cols; ++j) {
            for (int c = 0; c < 3; ++c) {
                p1[j][c] = prob[c * rows * cols + i * cols + j];
            }
        }
    }
    return out;
}

cv::Mat seg2decode(cv::Mat seg_mat, cv::Mat decode) {
    for (int i = 0; i < seg_mat.rows; ++i) {
        cv::Vec<float, 3> *p1 = seg_mat.ptr<cv::Vec<float, 3>>(i);
        cv::Vec3b *p2 = decode.ptr<cv::Vec3b>(i);
        for (int j = 0; j < seg_mat.cols; ++j) {
            int index = 0;
            float swap = 0;
            for (int c = 0; c < seg_mat.channels(); ++c) {
                if (p1[j][0] < p1[j][c]) {
                    swap = p1[j][0];
                    p1[j][0] = p1[j][c];
                    p1[j][c] = swap;
                    index = c;
                }
            }
            p2[j][0] = map_[index][2];
            p2[j][1] = map_[index][1];
            p2[j][2] = map_[index][0];
        }

    }
    return decode;
}

pair<vector<cv::Rect>, vector<float>>
boxTransform(vector<float> anchors, vector<float> regression, vector<float> classfications, cv::Size imageSize,
             float scoreThreshold = 0.25) {
    pair<vector<cv::Rect>, vector<float>> result;
    cv::Rect temp;
    float height = imageSize.height;
    float width = imageSize.width;
    for (int i = 0; i < classfications.size(); i ++) {
        if (classfications[i] > scoreThreshold) {
            int index = i * 4;
            float y_centers_a = (anchors[index] + anchors[index + 2]) / 2;
            float x_centers_a = (anchors[index + 1] + anchors[index + 3]) / 2;
            float ha = anchors[index + 2] - anchors[index];
            float wa = anchors[index + 3] - anchors[index + 1];

            float w = exp(regression[index + 3]) * wa;
            float h = exp(regression[index + 2]) * ha;
            float y_centers = regression[index] * ha + y_centers_a;
            float x_centers = regression[index + 1] * wa + x_centers_a;

            float ymin = y_centers - h / 2;
            float xmin = x_centers - w / 2;
            float ymax = y_centers + h / 2;
            float xmax = x_centers + w / 2;

            if (ymin < 0) ymin = 0;
            if (xmin < 0) xmin = 0;
            if (ymax > (height - 1)) ymax = height - 1;
            if (xmax > (width - 1)) xmax = width - 1;

            temp.x = ceil(xmin);
            temp.y = ceil(ymin);
            temp.width = ceil(xmax - xmin);
            temp.height = ceil(ymax - ymin);

            result.first.emplace_back(temp);
            result.second.emplace_back(classfications[i]);
        }
    }
    return result;
}


#endif //HYBRIDNETS_TENSORRT_PROCESS_IMAGE_HPP
