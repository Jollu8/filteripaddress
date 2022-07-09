#include "lib.h"
#include "ip_pool.h"
#include <gtest/gtest.h>

std::vector<std::vector<std::string>> initPoolIp();

std::vector<std::vector<std::string>> initReversSortPoolIp();

std::vector<std::string> initPoolIp1Octet1();

std::vector<std::string> initPoolIpFilterTwoOctet46and70();

std::vector<std::vector<std::string>> initPoolIpFilterAny46();

TEST(testVersionGoogle, testValidVersion) {

    EXPECT_GT(version(), 0);
}

TEST(ipPoolTests, reverseLexicographicallySortInIpool) {

    IpPool testPool(initPoolIp());

    EXPECT_TRUE(initReversSortPoolIp() == testPool.reverseLexicographicallySort()) << "IpPoolIp not sorted";
}

TEST(ipPoolTests, filterOneOctetIN1) {

    IpPool testPool(initPoolIp());

    EXPECT_TRUE(initReversSortPoolIp() == testPool.reverseLexicographicallySort()) << "IpPoolIp not sorted";

    EXPECT_TRUE(initPoolIp1Octet1() == testPool.filter(1).second) << "Filter for octet 1 not work";
}

TEST(ipPoolTests, filterTwoOctetIN46and70) {
    IpPool testPool(initPoolIp());

    EXPECT_TRUE(initReversSortPoolIp() == testPool.reverseLexicographicallySort()) << "IpPoolIp not sorted";

    EXPECT_TRUE(initPoolIpFilterTwoOctet46and70() == testPool.filter(46, 70).second)
                        << "Filter for two octet 46 and 70 not work";

}

TEST(ipPoolTests, filterAny46) {
    IpPool testPool(initPoolIp());

    EXPECT_TRUE(initReversSortPoolIp() == testPool.reverseLexicographicallySort()) << "IpPoolIp not sorted";

    EXPECT_TRUE(initPoolIpFilterAny46() == testPool.filter_any(46).second) << "Filter for any octet 46 not work";
}

std::vector<std::vector<std::string>> initPoolIp() {
    std::vector<std::vector<std::string>> ipPool
            {
                    {"222", "173", "235", "246"},
                    {"1",   "29",  "168", "152"},
                    {"222", "82",  "198", "61"},
                    {"46",  "70",  "29",  "76"},
                    {"222", "130", "177", "64"},
                    {"1",   "70",  "44",  "170"},
                    {"46",  "70",  "147", "26"},
                    {"1",   "1",   "234", "8"},
                    {"46",  "70",  "225", "39"},
                    {"46",  "70",  "113", "73"},
                    {"5",   "189", "203", "46"},
                    {"39",  "46",  "86",  "85"}
            };
    return ipPool;
}

std::vector<std::vector<std::string>> initReversSortPoolIp() {
    std::vector<std::vector<std::string>> ipPool
            {

                    {"222", "173", "235", "246"},
                    {"222", "130", "177", "64"},
                    {"222", "82",  "198", "61"},
                    {"46",  "70",  "225", "39"},
                    {"46",  "70",  "147", "26"},
                    {"46",  "70",  "113", "73"},
                    {"46",  "70",  "29",  "76"},
                    {"39",  "46",  "86",  "85"},
                    {"5",   "189", "203", "46"},
                    {"1",   "70",  "44",  "170"},
                    {"1",   "29",  "168", "152"},
                    {"1",   "1",   "234", "8"},
            };
    return ipPool;
}

std::vector<std::string> initPoolIp1Octet1() {
    std::vector<std::string> ipPool
            {
                    {"1.70.44.170"},
                    {"1.29.168.152"},
                    {"1.1.234.8"}
            };
    return ipPool;
}

std::vector<std::string> initPoolIpFilterTwoOctet46and70() {
    std::vector<std::string> ipPool
            {
                    {"46.70.225.39"},
                    {"46.70.147.26"},
                    {"46.70.113.73"},
                    {"46.70.29.76"}
            };
    return ipPool;
}

std::vector<std::vector<std::string>> initPoolIpFilterAny46() {
    std::vector<std::vector<std::string>> ipPool
            {
                    {"46", "70",  "225", "39"},
                    {"46", "70",  "147", "26"},
                    {"46", "70",  "113", "73"},
                    {"46", "70",  "29",  "76"},
                    {"39", "46",  "86",  "85"},
                    {"5",  "189", "203", "46"}
            };
    return ipPool;
}