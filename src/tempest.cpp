#include "logger.hpp"
#include "tempest.hpp"

#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;

const std::string hostname = "swd.weatherflow.com";
const int api_port = 443;

const std::string rest_endpoint ="/swd/rest/";

const std::string station_meta = "stations";
const std::string station_observation = "observations/station/";
const std::string device_observation = "observations/";

const std::string web_socket = "wss://ws.weatherflow.com/swd/data?";

// Constructor
Tempest::Tempest(void)
{
    api_token = "";
    station_id = "";
    device_id = "";
}

void Tempest::set_token(const std::string src_token)
{
    api_token = src_token;
    boost::algorithm::trim_left(api_token);
}

void Tempest::set_station(const std::string src_station)
{
    station_id = src_station;
}

void Tempest::set_device(const std::string src_device)
{
    device_id = src_device;
}

int Tempest::get_station_meta_data(void)
{
    if(this->api_token.empty()) {
      ERROR << "No API token provided";
      return -1;
    }

    std::string str_response;

    TRACE << "get_station_meta_data()";

    std::string header_path = rest_endpoint + station_meta + "?token=" + this->api_token;

    tcp::resolver resolver(io_service);
    
    // Get a list of endpoints corresponding to the server name.
    tcp::resolver::query query(hostname, "http");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // Try each endpoint until we successfully establish a connection.
    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    // Form the request. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET " << header_path << " HTTP/1.1\r\n";
    request_stream << "Host: " << hostname << "\r\n";
    request_stream << "Accept: application/json\r\n";
    request_stream << "Connection: close\r\n";
    request_stream << "\r\n";

    // Send the request.
    boost::asio::write(socket, request);

    // Read the response status line. The response streambuf will automatically
    // grow to accommodate the entire line. The growth may be limited by passing
    // a maximum size to the streambuf constructor.
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    // Check that response is OK.
    std::istream response_stream(&response);
    std::string http_version;

    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;

    std::string status_message;
    std::getline(response_stream, status_message);

    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
      INFO << "Invalid response\n";
      return 1;
    }
    if (status_code != 200)
    {
      INFO << "Response returned with status code " << status_code << "\n";
      return 1;
    }

    // Read the response headers, which are terminated by a blank line.
    boost::asio::read_until(socket, response, "\r\n\r\n");

    // Process the response headers.
    std::string header;
    
    while (std::getline(response_stream, header) && header != "\r") {
      DEBUG << header << "\n";
    }
    DEBUG << "\n";

    // Write whatever content we already have to output.
    if (response.size() > 0) {
        DEBUG << &response;
        //std::cout << &response;
    }

    // Read until EOF, writing data to output as we go.
    boost::system::error_code error;
    while (boost::asio::read(socket, response,
          boost::asio::transfer_at_least(1), error))

      DEBUG << &response;
      //std::cout << &response;
    if (error != boost::asio::error::eof)
      throw boost::system::system_error(error);

    //INFO << response;

    return 0;
}

std::string Tempest::get_station_observation(void)
{
    std::string response;

    return response;
}

std::string Tempest::get_device_observation(void)
{
    std::string response;

    return response;
}

// Deconstructor
Tempest::~Tempest(void)
{

}