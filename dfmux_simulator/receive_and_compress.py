from __future__ import division
import socket
import struct
import blosc

MCAST_GRP = '239.192.0.2'
MCAST_PORT = 9876

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', MCAST_PORT))  # use MCAST_GRP instead of '' to listen only
                             # to MCAST_GRP, not all groups on MCAST_PORT
mreq = struct.pack("4sl", socket.inet_aton(MCAST_GRP), socket.INADDR_ANY)

sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

i = 0
recv = ''

while i<10000:
    recv += sock.recv(560)
    i+=1

compressed_recv = blosc.compress(recv, typesize=8)
print len(recv)
print len(compressed_recv)/len(recv)
