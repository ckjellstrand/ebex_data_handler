import time
import zmq

context = zmq.Context()
socket = context.socket(zmq.PAIR)
socket.bind("tcp://127.0.0.1:9876")
#socket.bind("tcp://239.192.0.2:9876")

i = 0

while True:
    socket.send(str(i))
    i += 1
