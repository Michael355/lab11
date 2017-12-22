#include <print.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

void PrintInFile(std::string const& filename)
{
    std::string text;
    while(std::cin >> text) {
        std::ofstream out(filename, std::ios_base::app);
        print(text, out);
        out << std::endl;
    }
}

bool PrintFromArgs(int argc, char** argv)
{
    po::options_description bash_options("Bash options");
    bash_options.add_options()
        ("output", po::value<std::string>(), "set output file")
    ;

    po::variables_map bash_vm;
    po::store(po::parse_command_line(argc, argv, bash_options), bash_vm);
    po::notify(bash_vm);

    if (bash_vm.count("output")) {
        PrintInFile(bash_vm["output"].as<std::string>());
        return true;
    }
    else {
        return false;
    }
}

bool PrintFromConfig(std::string const& filename)
{
    std::string confPath;
    po::options_description config_options("Configuration");
    config_options.add_options()
        ("output", po::value<std::string>(&confPath), "set output file")
    ;

    std::ifstream configFile(filename);

    po::variables_map config_vm;
    po::store(po::parse_config_file(configFile, config_options), config_vm);
    po::notify(config_vm);

    if (config_vm.count("output")) {
        PrintInFile(config_vm["output"].as<std::string>());
        return true;
    }
    else {
        return false;
    }
}

bool PrintFromEnvironment()
{
    char* envOutput{ std::getenv("DEMO_OUTPUT") };
    if (envOutput != nullptr) {
        PrintInFile(envOutput);
        return true;
    }
    else {
        return false;
    }
}


int main(int argc, char** argv)
{
    if (!PrintFromArgs(argc, argv)) {
        if (!PrintFromEnvironment()) {
            if (!PrintFromConfig( std::string{ std::getenv("HOME") } + "/.config/demo.cfg" )) {
                PrintInFile("default.log");
            }
        }
    }
    return 0;
}
