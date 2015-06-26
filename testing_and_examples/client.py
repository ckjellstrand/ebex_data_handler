#
#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back
#

import zmq

context = zmq.Context()

#  Socket to talk to server
socket = context.socket(zmq.PAIR)
socket.connect("tcp://127.0.0.1:9876")
#socket.connect("tcp://239.192.0.2:9876")

#  Do 10 requests, waiting each time for a response
#for request in range(100):
while True:
    #  Get the reply.
    message = socket.recv()
    print("Received [ %s ]" % (message))
