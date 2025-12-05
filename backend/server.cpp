#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

// Helper function to get Content-Type based on file extension
std::string getContentType(const std::string& path) {
    if (path.size() >= 5 && path.substr(path.size() - 5) == ".html") {
        return "text/html; charset=UTF-8";
    } else if (path.size() >= 3 && path.substr(path.size() - 3) == ".js") {
        return "application/javascript";
    } else if (path.size() >= 4 && path.substr(path.size() - 4) == ".css") {
        return "text/css";
    } else if (path.size() >= 4 && path.substr(path.size() - 4) == ".png") {
        return "image/png";
    } else if ((path.size() >= 4 && path.substr(path.size() - 4) == ".jpg") ||
               (path.size() >= 5 && path.substr(path.size() - 5) == ".jpeg")) {
        return "image/jpeg";
    }
    return "text/plain";
}

// Helper function to parse the request path from HTTP request
std::string parseRequestPath(const std::string& request) {
    std::istringstream iss(request);
    std::string method, path, version;
    if (iss >> method >> path >> version) {
        return path;
    }
    return "/";
}

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

        // read HTTP request
        char buffer[4096] = {0};
        ssize_t bytes_read = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read < 0) {
            perror("recv");
            close(new_socket);
            continue;
        }

        std::string request(buffer, bytes_read);
        std::string request_path = parseRequestPath(request);

        // determine file path based on request
        std::string file_path;
        if (request_path == "/" || request_path == "/index.html") {
            file_path = "backend/index.html";
        } else {
            // remove leading slash and serve from project root
            file_path = request_path.substr(1);
        }

        // read the requested file
        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        std::string response;
        
        if (!file.is_open()) {
            // file not found - 404 response
            response = "HTTP/1.1 404 Not Found\r\n"
                      "Content-Type: text/plain\r\n"
                      "Content-Length: 13\r\n"
                      "Connection: close\r\n"
                      "\r\n404 Not Found";
        } else {
            // read file contents
            std::string content((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
            file.close();

            // build HTTP response with proper headers
            std::string content_type = getContentType(file_path);
            response = "HTTP/1.1 200 OK\r\n"
                      "Content-Type: " + content_type + "\r\n"
                      "Content-Length: " + std::to_string(content.size()) + "\r\n"
                      "Connection: close\r\n"
                      "\r\n" + content;
        }

        // send the response
        ssize_t sent = send(new_socket, response.c_str(), response.size(), 0);
        if (sent < 0) {
            perror("send");
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}