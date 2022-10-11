#ifndef TEMPEST_HPP
#define TEMPEST_HPP

#include <string>

class Tempest
{
    private:
        std::string api_token;
        std::string station_id;

    public:
        Tempest(){};
        void setToken(std::string){};
        void setStation(std::string){};
};

#endif