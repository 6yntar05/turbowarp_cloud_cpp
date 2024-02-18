import ssl
import time
import sys

import websocket # install websocket-client, not websocket

ssl_context = ssl.create_default_context()
ssl_context.check_hostname = False

try:
    ws = websocket.WebSocket(sslopt={"ssl_context": ssl_context})
    ws.connect(sys.argv[1])
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
