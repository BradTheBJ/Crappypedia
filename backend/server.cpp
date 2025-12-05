#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iterator>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    // require port argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }

    // create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    // allow quick reuse of the address
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_fd);
        return 1;
    }

    // server address structure
    struct sockaddr_in address;
    std::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    // convert port argument to integer safely
    int port = 0;
    try {
        port = std::stoi(argv[1]);
    } catch (...) {
        std::cerr << "Invalid port number.\n";
        close(server_fd);
        return 1;
    }
    address.sin_port = htons(port);

    // bind socket to address:port
    if (bind(server_fd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // start listening
    if (listen(server_fd, 8) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    // read index.html from the backend folder (FIXED PATH)
    std::ifstream file("backend/index.html", std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open backend/index.html\n";
        close(server_fd);
        return 1;
    }
    std::string html((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    file.close();

    // build HTTP response with proper headers and CRLFs
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: " + std::to_string(html.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" + html;

    std::cout << "Server is running on port " << port << "\n";

    // accept loop
    socklen_t addrlen = sizeof(address);
    while (true) {
        std::cout << "Waiting for connections...\n";
        int new_socket = accept(server_fd, reinterpret_cast<struct sockaddr*>(&address), &addrlen);
        if (new_socket < 0) {
            perror("accept");
            // continue accepting after transient errors
            continue;
        }

        // send the prepared response
        ssize_t sent = send(new_socket, response.c_str(), response.size(), 0);
        if (sent < 0) {
            perror("send");
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}