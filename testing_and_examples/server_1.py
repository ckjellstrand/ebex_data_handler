import time
import zmq

context = zmq.Context()
socket = context.socket(zmq.PAIR)
socket.bind("tcp://*:9876")

i = 0

while True:
    socket.send(str(i))
    i += 1
