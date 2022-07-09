//
// Created by jollu on 07.01.22.
//

#pragma once
#include <string>
#include <vector>
#include <algorithm>

class IpPool
{
    std::vector<std::vector<std::string>> _ipPool;

public:

    IpPool() = default;

    [[maybe_unused]] explicit IpPool(const std::vector<std::vector<std::string>> &ipPool);

    const std::vector<std::vector<std::string>>& reverseLexicographicallySort();

    [[nodiscard]] std::pair<bool, std::vector<std::string>> filter(int filter_1, int filter_2 = -1) const;

    [[nodiscard]] std::pair<bool, std::vector<std::vector<std::string>>> filter_any(int octet) const;

    void getLineIpPoll();



private:
    static std::vector<std::string> split(const std::string &str, char d);
    static std::vector<std::string> split(std::vector<std::vector<std::string>>::const_iterator found_first,
                                   std::vector<std::vector<std::string>>::const_iterator found_last) ;

};

struct PrintPool
{
    static void show(const std::vector<std::vector<std::string>> &pool) ;
    static void show(const std::vector<std::string> &pool) ;
};

template<class ForwardIt, class T>
std::pair<ForwardIt,ForwardIt>
myEqual_range(ForwardIt first, ForwardIt last, const T& value, int index)
{
    return std::make_pair(std::lower_bound(first, last, value, [index](const std::vector<std::string> &ip, const std::string &o)
    {
        return std::stoi(ip.at(index)) > std::stoi(o);
    }), std::upper_bound(first, last, value, [index](const std::string &o, const std::vector<std::string> &ip)
    {
        return std::stoi(ip.at(index)) < std::stoi(o);
    }));
}