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
BOOST_AUTO_TEST_SUITE( hybridnet_suite )

    BOOST_AUTO_TEST_CASE( run_case )
    {
        auto hybridnets = std::make_shared<HybridNets>();
        hybridnets->run();
    }
BOOST_AUTO_TEST_SUITE_END()


#endif //HYBRIDNETS_TENSORRT_HYBRIDNET_TEST_HPP
