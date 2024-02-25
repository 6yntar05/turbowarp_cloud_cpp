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

    data = json.dumps({'method': 'handshake', 'project_id': '228228', 'user': 'asd'})
    ws.send(data)
    m = ws.recv()
    print(json.loads(m))
    time.sleep(1)
    
    while(True):
        data = json.dumps({'method': 'set', 'name': 'setName', 'value': 'setValue'})
        ws.send(data)
        m = ws.recv()
        print(json.loads(m))
        time.sleep(1)
    

except Exception as e:
    print(f"Произошла ошибка при подключении: {e}")
finally:
    if ws:
        ws.close()
