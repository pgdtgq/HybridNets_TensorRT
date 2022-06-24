/**
 * @brief 
 * @author      xiaowenxuan
 * @date        2022/6/21 10:25      
 * @copyright   Copyright （C）2022 xiaowenxuan All rights reserved. 
 *              email:18710760109@163.com
 */

#ifndef HYBRIDNETS_TENSORRT_HYBRIDNET_TEST_HPP
#define HYBRIDNETS_TENSORRT_HYBRIDNET_TEST_HPP
#define BOOST_TEST_MODULE example

#include <HybridNets/HybridNets.h>
#include "boost/test/included/unit_test.hpp"

BOOST_AUTO_TEST_SUITE(hybridnet_suite)

    BOOST_AUTO_TEST_CASE(image_case) {
        auto hybridnets = std::make_shared<HybridNets>();
        Mat image = cv::imread("../data/images/1.jpg");
        hybridnets->setInput(image);
        hybridnets->forward();
        hybridnets->saveResult("./result", true);
        fusionSeg(hybridnets->det_origin, hybridnets->seg_origin);
        imwrite("./fusion.jpg", hybridnets->det_origin);

    }

    BOOST_AUTO_TEST_CASE(real_case) {
        auto hybridnets = std::make_shared<HybridNets>();
        namedWindow("detResult");
        VideoCapture capture("../data/videos/1.mp4");
        if (!capture.isOpened()) {
            cout << "fail open file" << endl;
        }
        Mat image;

        int count = 0;
        float duration = 0.0f;
        while (true) {
            capture >> image;
            if (image.empty()) {
                break;
            }
            count++;
            hybridnets->setInput(image);
            auto time1 = chrono::steady_clock::now();
            hybridnets->forward();
            auto time2 = chrono::steady_clock::now();
            duration += (float) std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000;
            hybridnets->saveResult("./result", false);
            imshow("detResult", hybridnets->det_origin);
            if (cv::waitKey(1) >= 0)
                break;
        }
        std::cout << "hybridnets enqueue done, time: " << (duration / count) << " ms." << std::endl;
        capture.release();
    }

    BOOST_AUTO_TEST_CASE(video_case) {
        auto hybridnets = std::make_shared<HybridNets>();

        VideoCapture capture("../data/videos/1.mp4");
        VideoWriter detWriter;
        VideoWriter segWriter;
        VideoWriter fusionWriter;
        if (!capture.isOpened()) {
            cout << "fail open file" << endl;
        }
        Mat image;
        double fps = capture.get(CAP_PROP_FPS);
        Size size((int) capture.get(CAP_PROP_FRAME_WIDTH), (int) capture.get(CAP_PROP_FRAME_HEIGHT));
        detWriter.open("./det.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size);
        segWriter.open("./seg.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size);
        fusionWriter.open("./fusion.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size);
        int count = 0;
        float duration = 0.0f;
        while (true) {
            capture >> image;
            if (image.empty()) {
                break;
            }

            count++;

            hybridnets->setInput(image);
            auto time1 = chrono::steady_clock::now();
            hybridnets->forward();
            auto time2 = chrono::steady_clock::now();
            duration += (float) std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000;
            hybridnets->saveResult("./result", false);

            detWriter << hybridnets->det_origin;
            segWriter << hybridnets->seg_origin;
            fusionSeg(hybridnets->det_origin, hybridnets->seg_origin);
            fusionWriter << hybridnets->det_origin;
        }
        std::cout << "hybridnets enqueue done, time: " << (duration / count) << " ms." << std::endl;

        detWriter.release();
        segWriter.release();
        fusionWriter.release();
        capture.release();
    }

    BOOST_AUTO_TEST_CASE(time_case) {
        auto hybridnets = std::make_shared<HybridNets>();
        Mat image = imread("../data/images/1.jpg");
        hybridnets->setInput(image);
        float duration = 0.0f;
        int epoch = 500;
        for (int i = 0; i < epoch; ++i) {
            auto time1 = chrono::steady_clock::now();
            hybridnets->forward();
            auto time2 = chrono::steady_clock::now();
            duration += (float) std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000;
        }
        std::cout << "hybridnets enqueue done, time: " << (duration / epoch) << " ms." << std::endl;
    }

    BOOST_AUTO_TEST_CASE(fusion_case) {
        Mat image1 = cv::imread("../data/images/1.jpg");
        Mat image2 = cv::imread("../data/images/2.jpg");
        fusionSeg(image1, image2);
        imwrite("fusion.jpg", image1);
    }

BOOST_AUTO_TEST_SUITE_END()


#endif //HYBRIDNETS_TENSORRT_HYBRIDNET_TEST_HPP
