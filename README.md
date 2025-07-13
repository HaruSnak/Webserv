<img src="readme/Webserv.png" alt="Webserv" width="900"/>

---

# WebServ
So here we are at the first group project with the CPP. WebServ is an *HTTP/1.1* server written in **C++98** that implements the essential features of a modern web server.

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

---

## 📒 Index

- [About](#about)
    - [Implemented Features](#implemented-features)
	- [Configuration File Format](#configuration-file-format)
	- [Implemented HTTP Status Codes](#implemented-http-status-codes)
- [Installation](#installation)
- [Testing](#testing)
- [Development](#development)
  - [File Structure](#file-structure)
 <!-- - [Diagram Architecture](#diagram-architecture)  -->
- [Notes](#notes)
- [Credits](#credits)

---

## About

I worked on this project with my teammate, **Astoll**, shortly after completing the *C++ modules at 42 (CPP98)*. For people who had just been introduced to *object-oriented programming*, Webserv was a real challenge but despite our initial doubts, it turned out to be a rather enjoyable project.

**Astoll** mainly handled the parsing of **HTTP requests** and the generation of responses.
As for me, I focused on parsing the configuration file, as well as setting up the initial structure for processing **HTTP requests**.

The rest of the project was split between pair programming especially the core structure of Webserv and individual tasks, such as test tools and certain specific features.

## Implemented Features

### 1. **HTTP Core Server**
- **HTTP/1.1 Parser** : Complete request analysis
- **HTTP Responses** : Response generation with status codes
- **Keep-Alive** : Persistent connection management
- **Headers** : Complete header processing

### 2. **HTTP Methods**

#### GET
- Serve static files
- Directory listing (autoindex)
- CGI execution
- Index management (index.html)

#### POST
- Simple file upload
- Body processing
- CGI execution with POST data

#### DELETE
- File deletion
- Permission verification
- 204 No Content response

### 3. **CGI (Common Gateway Interface)**
- **PHP-CGI** : PHP script execution
- **Environment variables** : REQUEST_METHOD, SCRIPT_FILENAME, etc.
- **Pipe** : Communication with CGI process
- **Error handling** : CGI crashes don't crash the server

### 4. **File Management**
- **MIME Types** : Automatic detection (HTML, CSS, JS, etc.)
- **Static files** : Serve all file types
- **Upload** : Save uploaded files
- **Permissions** : Access rights verification

### 5. **Advanced Configuration**
- **Multi-server** : Multiple servers on different ports
- **Virtual hosts** : server_name for different domains
- **Limitation** : Maximum body size
- **Routes** : Path configuration
- **Errors** : Custom error pages

## Configuration File Format

The configuration file follows the NGINX syntax:

```nginx
server {
    # MANDATORY: Server must listen on at least one port
    listen 127.0.0.1:8080;                 # IP:Port bindin (REQUIRED)
    
    # OPTIONAL: Server name for virtual host routing
    server_name localhost;                  # Virtual host identifier (OPTIONAL)
    
    # MANDATORY: Root directory for serving files
    root /path/to/webserv/www;             # Document root (REQUIRED)
    
    # OPTIONAL: Default file to serve when requesting a directory
    index index.html index.htm;            # Default files (OPTIONAL)
    
    # OPTIONAL: Maximum client request body size
    client_max_body_size 1000000;         # Body size limit in bytes (OPTIONAL)
    
    # OPTIONAL: Custom error pages
    error_page 404 /errors/404.html;      # Custom 404 page (OPTIONAL)
    error_page 500 /errors/500.html;      # Custom 500 page (OPTIONAL)
    
    # MANDATORY: HTTP methods allowed globally
    http_methods GET POST DELETE;          # Allowed methods (REQUIRED)
    
    # OPTIONAL: CGI configuration
    cgi .php /usr/bin/php-cgi;            # CGI extension mapping (OPTIONAL)
    cgi .py /usr/bin/python3;             # Multiple CGI types (OPTIONAL)
    
    # OPTIONAL: Directory listing
    autoindex on;                          # Enable directory browsing (OPTIONAL)
    
    # OPTIONAL: Location-specific configurations
    location /api {
        # OPTIONAL: Location-specific root
        root /path/to/webserv/www/api;     # Override root for this location
        
        # OPTIONAL: Location-specific methods
        http_methods GET POST;             # Restrict methods for this location
        
        # OPTIONAL: Location-specific CGI
        cgi .php /usr/bin/php-cgi;        # CGI for this location only
        
        # OPTIONAL: Location-specific index
        index api.php index.php;           # Default files for this location
    }
    
    location /uploads {
        # OPTIONAL: Upload-specific configuration
        root /path/to/webserv/uploads;     # Upload directory
        http_methods POST DELETE;          # Only allow upload/delete
        upload on;                         # Enable file upload (OPTIONAL)
        client_max_body_size 5000000;     # Higher limit for uploads
    }
    
    location /static {
        # OPTIONAL: Static files configuration
        root /path/to/webserv/static;      # Static assets directory
        http_methods GET;                  # Read-only access
        autoindex on;                      # Allow directory listing
        
        # OPTIONAL: HTTP redirection
        return 301 /new-static-location;   # Redirect (BONUS FEATURE)
    }
}

# OPTIONAL: Multiple servers configuration
server {
    listen 127.0.0.1:8081;                # Second server on different port
    server_name api.example.com;           # Different server name
    root /path/to/webserv/api;            # Different root directory
    http_methods GET POST PUT DELETE;      # Different allowed methods
    
    location / {
        cgi .php /usr/bin/php-cgi;        # API-specific CGI
        autoindex off;                     # Disable directory listing
    }
}
```

## Implemented HTTP Status Codes

| Code | Statut | Utilisation |
|------|--------|-------------|
| 200 | OK | Request successful |
| 201 | Created | File created (upload) |
| 204 | No Content | Deletion successful |
| 400 | Bad Request | Malformed query |
| 404 | Not Found | File not found |
| 405 | Method Not Allowed | Unauthorized method |
| 413 | Request Entity Too Large | Body too bulky |
| 500 | Internal Server Error | Server error |

---

## Installation

### Compilation
```bash
# Clone this repository
$ git clone https://github.com/HaruSnak/Webserv.git

# Go into the repository
$ cd Webserv

# To compile the program
$ make

# Removes all generated files and the executable for a thorough cleanup.
$ make fclean

# Removes generated object files and the executable.
$ make clean
```

### Starting the Server

```bash
# With configuration file
./webserv confs/eval.conf

# The server starts and displays:
# WebServer started successfully
# Listening on socket 3
```

## Testing

### Minimal Test Suite

The project includes a test suite that covers all evaluation points:

```bash
# Run all tests (basic HTTP, configuration and CGI)
./run_minimal_tests.sh
```

### Manual Tests

#### Basic HTTP Tests
```bash
# Start the server
./webserv confs/eval.conf &

# Test GET
curl -v http://localhost:8080/
# Expected: 200 OK with index.html content

# Test POST Upload
curl -X POST -d "test data" http://localhost:8080/upload
# Expected: 201 Created

# Test DELETE
echo "test" > www/test.txt
curl -X DELETE http://localhost:8080/test.txt
# Expected: 204 No Content

# Test unknown method
curl -X PATCH http://localhost:8080/
# Expected: 405 Method Not Allowed
```

#### CGI Tests
```bash
# Test PHP GET
curl http://localhost:8080/test.php
# Expected: 200 OK with PHP output

# Test PHP POST
curl -X POST -d "data=test" http://localhost:8080/test.php
# Expected: 200 OK with PHP output
```

---

## Development
### File Structure

```
.
└── 📁webnul
    └── 📁confs
        ├── eval.conf
    └── 📁includes
        └── 📁config
            ├── ConfigParser.hpp
            ├── GenericConfigParser.hpp
            ├── GenericConfigParser.tpp
            ├── LocationConfig.hpp
            ├── LocationConfigParser.hpp
            ├── ServerConfig.hpp
            ├── ServerConfigParser.hpp
        └── 📁core
            ├── Client.hpp
            ├── WebServ.hpp
        └── 📁http
            ├── HttpParser.hpp
            ├── HttpResponse.hpp
            ├── RequestHandler.hpp
        ├── utils.hpp
    └── 📁obj
        └── 📁srcs
            └── 📁config
                ├── ConfigParser.o
                ├── LocationConfig.o
                ├── LocationConfigParser.o
                ├── ServerConfig.o
                ├── ServerConfigParser.o
            └── 📁core
                ├── WebServ.o
            └── 📁http
                ├── HttpParser.o
                ├── HttpResponse.o
                ├── RequestHandler.o
            └── 📁utils
                ├── errors.o
            ├── main.o
    └── 📁srcs
        └── 📁config
            ├── ConfigParser.cpp
            ├── LocationConfig.cpp
            ├── LocationConfigParser.cpp
            ├── ServerConfig.cpp
            ├── ServerConfigParser.cpp
        └── 📁core
            ├── WebServ.cpp
        └── 📁http
            ├── HttpParser.cpp
            ├── HttpResponse.cpp
            ├── RequestHandler.cpp
        └── 📁utils
            ├── errors.cpp
        ├── main.cpp
    └── 📁www
        └── 📁api
            ├── index.php
            ├── test.py
        └── 📁errors
            ├── 404.html
        └── 📁static
            ├── index.html
            ├── script.js
            ├── style.css
        └── 📁uploads
            ├── upload_1752089165.dat
            ├── upload_1752090522.dat
        ├── index.htlm
        ├── index.html
        ├── test.php
        ├── upload.html
    ├── Makefile
    ├── README.md
    ├── tester.sh
    └── webserv
```

<!--### Diagram Architecture
Write the build Instruction here.-->
---

## Notes
Soon

---

## Credits

Below you will find the links used for this project:

- [Norm 42](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- [CPPReference](https://en.cppreference.com/w/)
- [NGinx - Beginner’s Guide](https://nginx.org/en/docs/beginners_guide.html#conf_structure)
- [HTTP request methods](https://developer.mozilla.org/fr/docs/Web/HTTP/Reference/Methods)
- [IBM - Nonblocking I/O and select()](https://www.ibm.com/docs/en/i/7.2.0?topic=designs-example-nonblocking-io-select)

[contributors-shield]: https://img.shields.io/github/contributors/HaruSnak/CPP-Module-ALL.svg?style=for-the-badge
[contributors-url]: https://github.com/HaruSnak/CPP-Module-ALL/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/HaruSnak/CPP-Module-ALL.svg?style=for-the-badge
[forks-url]: https://github.com/HaruSnak/CPP-Module-ALL/network/members
[stars-shield]: https://img.shields.io/github/stars/HaruSnak/CPP-Module-ALL.svg?style=for-the-badge
[stars-url]: https://github.com/HaruSnak/CPP-Module-ALL/stargazers
[issues-shield]: https://img.shields.io/github/issues/HaruSnak/CPP-Module-ALL.svg?style=for-the-badge
[issues-url]: https://github.com/HaruSnak/CPP-Module-ALL/issues
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/shany-moreno-5a863b2aa
