#include <iostream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char const *argv[]) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(std::stoi(argv[1]));

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (true) {
        std::cout << "Server is running on port " << argv[1] << std::endl;
        std::cout << "Waiting for connections..." << std::endl;
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        const char *hello = "HTTP/1.1 200 OK\n\nHello, World!";
        send(new_socket, hello, strlen(hello), 0);
        close(new_socket);
    }

    return 0;
}