#include "proxy.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using json = nlohmann::json;

void ProxyServer::start() {

    json config;
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        std::cerr << "Failed to open " << configPath << "\n";
        exit(EXIT_FAILURE);
    }
    configFile >> config;

    std::string address = config["address"];
    int port = config["port"];
  
    int server_fd, new_socket;
    struct sockaddr_in server_address;
    int opt = 1;
    int addrlen = sizeof(server_address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed\n";
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Setsockopt failed\n";
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(address.c_str());
    server_address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address))<0) {
        std::cerr << "Bind failed\n";
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Proxy server listening on " << address << ":" << port << std::endl;

    // Menerima koneksi masuk
    if ((new_socket = accept(server_fd, (struct sockaddr *)&server_address, (socklen_t*)&addrlen))<0) {
        std::cerr << "Accept failed\n";
        exit(EXIT_FAILURE);
    }

    close(new_socket);
    close(server_fd);
}
