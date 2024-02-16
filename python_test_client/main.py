import ssl
import time

import websocket # install websocket-client, not websocket

ws_url = "wss://localhost:8080"

ssl_context = ssl.create_default_context()
ssl_context.check_hostname = False
ssl_context.verify_mode = ssl.CERT_NONE

try:
    ws = websocket.WebSocket(sslopt={"ssl_context": ssl_context, "cert_reqs": ssl.CERT_NONE})
    ws.connect(ws_url)
    print("Подключено к серверу")

    ws.send("hi")
    while(True):
        m = ws.recv()
        print(m)
        time.sleep(5)
        ws.send(m)

except Exception as e:
    print(f"Произошла ошибка при подключении: {e}")
finally:
    if ws:
        ws.close()
