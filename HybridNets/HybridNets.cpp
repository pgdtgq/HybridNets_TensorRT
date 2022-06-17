/**
 * @brief 
 * @author      xiaowenxuan
 * @date        2022/6/17 16:15      
 * @copyright   Copyright （C）2022 xiaowenxuan All rights reserved. 
 *              email:18710760109@163.com
 */

#include "HybridNets.h"

HybridNets::HybridNets() {

}

HybridNets::~HybridNets() {

}

void HybridNets::run() {
    mNet->BuildEngine("../models/hybridnets_512x640.onnx", "../models/hybridnets_512x640.trt");
}
