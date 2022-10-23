#include "include/logger.hpp"
#include "include/tempest.hpp"

#include <boost/program_options.hpp>

#include <iostream>
#include <string>

bool verbose = false;

namespace po = boost::program_options;

int main(int argc, const char *argv[])
{
    Tempest tempest_ctx;

    try {
        po::options_description desc ("All options below:");

         desc.add_options ()
         ("help,h", "Help screen")
         ("verbose,v", "Verbose")
         ("token,t", po::value<std::string>(), "API Token")
         ("station,s", po::value<std::string>(), "Station ID");

        po::variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.size() == 0 || vm.count("help")) {
            std::cout << desc << '\n';
            return 0;
        }
        else {
            if(vm.count("v") || vm.count("verbose")) {
                verbose = true;
            }

            if(vm.count("t") || vm.count("token")) {
                std::string token = vm["token"].as<std::string>();
                INFO << "Setting API token: \"" << token << "\"";     
                tempest_ctx.set_token(token);
            }

            if(vm.count("s") || vm.count("station")) {
                std::string station = vm["station"].as<std::string>();
                INFO << "Setting station ID: \"" << station << "\"";     
                tempest_ctx.set_station(station);
            }
        }
    }
    catch(const po::error &ex) {
        std::cerr << ex.what() << '\n';
    }

    tempest_ctx.get_station_meta_data();

    return 0;   
}