#include "tempest.hpp"
#include <Poco/Net/HTTPRequest.h>

// Constructor
Tempest::Tempest()
{
};

void Tempest::setToken(std::string token)
{
    api_token = token;
};

void Tempest::setStation(std::string station)
{
    station_id = station;
};