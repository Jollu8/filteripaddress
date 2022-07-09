#include <iostream>
#include "lib.h"
#include "ip_pool.h"


int main(int, char **) {

    try {
        IpPool ipPool;
        PrintPool print;

        ipPool.getLineIpPoll();

        // TODO reverse lexicographically sort
        auto ip = ipPool.reverseLexicographicallySort();

        print.show(ip);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        if (auto [ok, pool] = ipPool.filter(1); ok) {
            print.show(pool);
        }
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        if (auto [ok, pool] = ipPool.filter(46, 70); ok) {
            print.show(pool);
        }
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        if (auto [ok, pool] = ipPool.filter_any(46); ok) {
            print.show(pool);
        }

    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}