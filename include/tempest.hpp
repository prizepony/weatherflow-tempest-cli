#ifndef TEMPEST_HPP
#define TEMPEST_HPP

#include <string>
#include <iostream>

#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>

class Tempest
{
    private:
        boost::asio::io_service io_service;

    public:
        std::string api_token;
        std::string station_id;
        std::string device_id;

        Tempest(void);

        void set_token(const std::string);
        void set_station(const std::string);
        void set_device(const std::string);

        int get_station_meta_data(void);
        std::string get_station_observation(void);
        std::string get_device_observation(void);

        ~Tempest(void);
};

#endif