# Python Proxy Server

This Python-based multi-threaded proxy server supports both HTTP and SOCKS5 protocols. It handles WebSocket connections and provides secure tunneling capabilities.

## Features

- **SOCKS5 Support**: Acts as a SOCKS5 proxy, forwarding client connections to any target server.
- **HTTP Proxy**: Manages HTTP requests and WebSocket connections, supporting HTTP upgrade mechanisms.
- **Multi-threaded**: Efficiently handles each connection in a separate thread.
- **Logging**: Logs connection details, errors, and data transfer activities.
- **Customizable**: Easily configure the listening address, port, and target server settings.

## Example Usage

## Configuration

Update the following configuration settings in your Python script:

```python
DEFAULT_HOST = '127.0.0.1:22'  # Target server (e.g., OpenSSH server on port 22)
LISTENING_ADDR = '127.0.0.1'   # Address where the proxy listens
LISTENING_PORT = 700            # Port on which the proxy server will run
```

- **DEFAULT_HOST**: The target server to which the proxy will forward connections.
- **LISTENING_ADDR**: The address the proxy server will bind to (e.g., 127.0.0.1 for localhost).
- **LISTENING_PORT**: The port on which the proxy server will listen for incoming connections.

Note: `Modify these values based on your server's requirements.`

## Nginx
```Nginx
server {
    listen 80;
    listen [::]:80;
    listen 443 ssl http2 reuseport;
    listen [::]:443 http2 reuseport;

    ssl_certificate /path/to/cert.crt;
    ssl_certificate_key /path/to/key.key;
    ssl_ciphers EECDH+CHACHA20:EECDH+CHACHA20-draft:EECDH+ECDSA+AES128:EECDH+aRSA+AES128:RSA+AES128:EECDH+ECDSA+AES256:EECDH+aRSA+AES256:RSA+AES256:EECDH+ECDSA+3DES:EECDH+aRSA+3DES:RSA+3DES:!MD5;
    client_max_body_size 50M;
    ssl_protocols TLSv1.1 TLSv1.2 TLSv1.3;

    location / {
        proxy_pass http://127.0.0.1:700;
        proxy_http_version 1.1;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "upgrade";
        proxy_set_header Host $http_host;
        proxy_set_header User-Agent $http_user_agent;
        proxy_set_header Accept-Encoding '';
        proxy_buffering off;
    }
}
```

- **listen 80**: Nginx will handle connections on port 80 for HTTP and WebSocket connections.
- **listen 443 ssl http2 reuseport**: Nginx will handle connections on port 443 for HTTPS and secure WebSocket connections.
- **ssl_certificate and ssl_certificate_key**: Paths to your SSL certificate and key files.
- **location /**: Directs traffic from the root path to the proxy server.proxy_pass: Forwards connections to the Python proxy server running on 127.0.0.1:700.

Note: Adjust the configuration to fit your server setup.

## Service
```Service
[Unit]
Description=Proxy Server By FN Project
Documentation=https://t.me/fn_project
After=network.target nss-lookup.target

[Service]
Type=simple
User=root
CapabilityBoundingSet=CAP_NET_ADMIN CAP_NET_BIND_SERVICE
AmbientCapabilities=CAP_NET_ADMIN CAP_NET_BIND_SERVICE
NoNewPrivileges=true
Restart=on-failure
ExecStart=/usr/bin/python3 -O /path/to/server.py

[Install]
WantedBy=multi-user.target
```

- **Path server.py**: replace the path to server.py with the appropriate path within your server.


## Requirements
- Python 3.xx

## Contact
- [@Rerechan02](https://t.me/Rerechan02)

## License

And of course:

MIT: <https://rem.mit-license.org>