# 🖥️ Minimal C++ HTTP Server (Sockets)

This is a **website template** featuring a minimal web server written in C++ that uses the standard **POSIX Sockets API** to demonstrate the fundamental server lifecycle: **socket creation, binding, listening, and serving a static file** (`index.html`).

It's designed as a starter template for building websites with a C++ backend, perfect for those beginning C++ network programming or looking for a simple foundation to build upon.

---

## 1. Project Structure

The server is designed for a separate build directory. The static asset (`index.html`) is hardcoded to be read from `backend/index.html` relative to the execution path.

```
/ProjectRoot  
├── backend/  
│   ├── index.html  ← Static asset served by the server  
│   └── server.cpp  ← The server source code  
└── build/  
    └── (Compiled binary goes here)
```

## 2. Compilation Guide

The compilation step must be run **from the `ProjectRoot`** to correctly target the `build/` directory for the output executable.

### 🔨 Compile Command

```bash
g++ backend/server.cpp -o build/server.out 
# .exe if you are on Windows
```

## 3. Running the Server

The executable must be launched from the **ProjectRoot** and requires you to manually specify the desired port number as a command-line argument.

### ▶️ Run Command

```bash
./build/server.out <YOUR_PORT>
# Again .exe if you are on Windows
```

## 4. Accessing the Server

After successfully running the server, you can access the served content (**index.html**) using either **localhost** or the loopback IP in your web browser:

| Access Method   | URL                         |
|-----------------|----------------------------|
| Localhost       | `http://localhost:<YOUR_PORT>` |
| Loopback IP     | `http://127.0.0.1:<YOUR_PORT>` |

### Example Access (using port 8080)

- Localhost: `http://localhost:8080`  
- Loopback IP: `http://127.0.0.1:8080`

## 5. Getting Started

If you want to work with this template, just clone or fork it and get started:

```bash
git clone <repository-url>
```