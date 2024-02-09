import ssl
import websocket # install websocket-client, not websocket

ws_url = "wss://localhost:8080"

print(ssl.OPENSSL_VERSION) #

# import urllib3; urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

ssl_context = ssl.create_default_context()
ssl_context.check_hostname = False
ssl_context.verify_mode = ssl.CERT_NONE

try:
    ws = websocket.WebSocket(sslopt={"ssl_context": ssl_context, "cert_reqs": ssl.CERT_NONE})
    ws.connect(ws_url)
    ws.send("hi")
    print("Подключено к серверу")
except Exception as e:
    print(f"Произошла ошибка при подключении: {e}")
finally:
    if ws:
        ws.close()
