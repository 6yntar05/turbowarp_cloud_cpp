import ssl
import websocket
import sys
# from websocket import create_connection

args = sys.argv
path = args[1]
# ws = create_connection('wss://localhost:30001' + path)
ws = websocket.WebSocket(sslopt={"cert_reqs": ssl.CERT_NONE})
ws.connect("wss://localhost:30001" + path)

while True:
    msg = input('Enter a message: ')
    if msg == 'quit':        
        ws.close()
        break
    ws.send(msg)
    result =  ws.recv()
    print ('> ', result)
