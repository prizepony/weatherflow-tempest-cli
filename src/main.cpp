#include "include/tempest.hpp"

#include <boost/program_options.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp> 

#include <iostream>
#include <string>
#include <vector>

bool verbose = false;

namespace po = boost::program_options;
namespace logging = boost::log;

void init_logging() {
    if(verbose) {
        logging::core::get()->set_filter (logging::trivial::severity >= logging::trivial::debug);
        BOOST_LOG_TRIVIAL(debug) << "Verbose mode enabled";     
    } else {
        logging::core::get()->set_filter (logging::trivial::severity >= logging::trivial::info);
    }
}

int main(int argc, const char *argv[])
{
    Tempest ctx;

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

        if (vm.size() == 0 || vm.count("help"))
            std::cout << desc << '\n';
        else {
            if(vm.count("v") || vm.count("verbose")) {
                verbose = true;
            }

            init_logging();

            if(vm.count("t") || vm.count("token")) {
                std::string token = vm["token"].as<std::string>();
                BOOST_LOG_TRIVIAL(debug) << "Using API token: " << token;     
                ctx.setToken(token);
            }

            if(vm.count("s") || vm.count("station")) {
                std::string station = vm["station"].as<std::string>();
                BOOST_LOG_TRIVIAL(debug) << "Using station ID: " << station;     
                ctx.setStation(station);
            }
        }
    }
    catch(const po::error &ex) {
        std::cerr << ex.what() << '\n';
    }

    return 0;   
}