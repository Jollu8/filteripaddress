//
// Created by jollu on 07.07.22.
//

#include "ip_pool.h"
#include <iostream>
#include <utility>
#include <ranges>


[[maybe_unused]] IpPool::IpPool(const std::vector<std::vector<std::string>> & ipPool)
{
    std::ranges::copy(ipPool, std::back_inserter(_ipPool));
}



const std::vector<std::vector<std::string>>& IpPool::reverseLexicographicallySort()
{
    std::ranges::sort(_ipPool, [](const auto &ip1, const auto &ip2)
    {
        for (auto ip_one = ip1.cbegin(), ip_two = ip2.cbegin(); ip_one != ip1.cend() && ip_two != ip2.cend(); ++ip_one, ++ip_two)
        {
            if (ip_one->size() > ip_two->size())
                return true;
            else if (ip_one->size() < ip_two->size())
                return false;
            else
            {
                for (auto s = ip_one->cbegin(), st = ip_two->cbegin(); s != ip_one->cend() && st != ip_two->cend(); ++s, ++st)
                {
                    if (*s > *st)
                        return true;
                    else if (*s < *st)
                        return false;
                }
            }
        }

        return false;
    });

    return _ipPool;
}

std::pair<bool, std::vector<std::string>> IpPool::filter(int filter_1, int filter_2) const
{
    std::string f1 = std::to_string(filter_1);

    auto found_ip = myEqual_range(_ipPool.cbegin(), _ipPool.cend(), f1, 0);

    if(filter_2 != -1)
    {
        std::string f2 = std::to_string(filter_2);
        found_ip = myEqual_range(found_ip.first, found_ip.second, f2, 1);
    }

    std::vector<std::string> pool;

    pool = split(found_ip.first, found_ip.second);

    return std::make_pair((!pool.empty()), pool);
}

std::pair<bool, std::vector<std::vector<std::string>>> IpPool::filter_any(int octet) const
{
    std::string oct = std::to_string(octet);
    std::vector<std::vector<std::string>> pool;

    for (auto &it : _ipPool)
    {
        for(auto &ip_it :it)
        {
            if(ip_it == oct)
            {
                pool.push_back(it);
                break;
            }
        }
    }
    return std::make_pair((!pool.empty()), pool);
}

std::vector<std::string> IpPool::split(std::vector<std::vector<std::string>>::const_iterator found_first,
                                       std::vector<std::vector<std::string>>::const_iterator found_last)
{
    std::vector<std::string> pool;
    for(auto i = found_first; i != found_last; ++i)
    {
        std::string ip;
        for(auto j = i->cbegin(); j != i->cend(); ++j)
        {
            if (j != i->cbegin())
            {
                ip+= ".";
            }
            ip+= *j;
        }
        pool.push_back(ip);
    }
    return pool;
}

std::vector<std::string> IpPool::split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void IpPool::getLineIpPoll()
{
    for (std::string line; std::getline(std::cin, line);)
    {
        if (line.empty() || line == "end")
            break;
        std::vector<std::string> v = split(line, '\t');
        _ipPool.push_back(split(v.at(0), '.'));
    }
}

void PrintPool::show(const std::vector<std::vector<std::string>> &pool)
{
    for (const auto & ip : pool)
    {
        for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
        {
            if (ip_part != ip.cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

void PrintPool::show(const std::vector<std::string> &pool)
{
    for(const auto &s: pool)
        std::cout << s << std::endl;
}