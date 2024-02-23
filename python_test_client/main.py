import ssl
import time
import sys
import json

import websocket # install websocket-client, not websocket

ssl_context = ssl.create_default_context()
ssl_context.check_hostname = False

try:
    ws = websocket.WebSocket(sslopt={"ssl_context": ssl_context})
    ws.connect(sys.argv[1])
    print("Подключено к серверу")

    # data = json.dumps(['foo', {'bar': ('baz', None, 1.0, 2)}])
    data = json.dumps({'method': 'handshake', 'project_id': 'qwe', 'user': 'asd'})
    # data = "asd"
    ws.send(data)
    # while(True):
    #     m = ws.recv()
    #     print(json.loads(m))
    #     time.sleep(5)
    #     ws.send(m)

except Exception as e:
    print(f"Произошла ошибка при подключении: {e}")
finally:
    if ws:
        ws.close()
