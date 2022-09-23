#include "tempest.hpp"

#include <boost/program_options.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp> 

#include <string>
#include <iostream>

bool verbose = false;

using namespace boost::program_options;
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
    Tempest a;

    try {
        options_description desc ("All options below:");

         desc.add_options ()
         ("help,h", "Help screen")
         ("verbose,v", "Verbose")
         ("token,t", "API Token")
         ("station,s","Station ID");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.size() == 0 || vm.count("help"))
            std::cout << desc << '\n';
        else if(vm.count("v") || vm.count("verbose")) {
            verbose = true;
        }
        init_logging();
    }
    catch(const error &ex) {
        std::cerr << ex.what() << '\n';
    }

    return 0;   
}