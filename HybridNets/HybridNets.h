/**
 * @brief 
 * @author      xiaowenxuan
 * @date        2022/6/17 16:15      
 * @copyright   Copyright （C）2022 xiaowenxuan All rights reserved. 
 *              email:18710760109@163.com
 */

#ifndef HYBRIDNETS_TENSORRT_HYBRIDNETS_H
#define HYBRIDNETS_TENSORRT_HYBRIDNETS_H

#include "Trt.h"

class HybridNets {
private:
    Trt *mNet = new Trt();
public:
    HybridNets();

    virtual ~HybridNets();

    void run();

};


#endif //HYBRIDNETS_TENSORRT_HYBRIDNETS_H
