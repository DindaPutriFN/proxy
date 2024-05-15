#include "proxy.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    std::string configPath = "config.json";
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "-c" || arg == "-config") {
            if (argc > 2) {
                configPath = argv[2];
            } else {
                std::cerr << "Usage: " << argv[0] << " -c/-config <path/to/config.json>\n";
                return 1;
            }
        } else {
            std::cerr << "Unknown option: " << arg << "\n";
            return 1;
        }
    }

    ProxyServer proxy(configPath);
    proxy.start();

    return 0;
}
