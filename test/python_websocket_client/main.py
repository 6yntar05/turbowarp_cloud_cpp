# import ssl
# import websocket
import sys
from websocket import create_connection

args = sys.argv
path = args[1]
ws = create_connection('ws://localhost:30001' + path)

while True:
    msg = input('Enter a message: ')
    if msg == 'quit':        
        ws.close()
        break
    ws.send(msg)
    result =  ws.recv()
    print ('> ', result)
