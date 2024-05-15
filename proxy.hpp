#ifndef PROXY_HPP
#define PROXY_HPP

#include <string>

class ProxyServer {
private:
    std::string configPath;
    
public:
    ProxyServer(const std::string &configPath) : configPath(configPath) {}
    void start();
};

#endif
