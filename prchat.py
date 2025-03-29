# so its easier to test and stuff

"""
PRCHAT ("Peer Chat") Protocol V0

using gpg keys to create subnets of discord-like and skype-like groups
udp over 6040


"""

import socket
import threading
import gpg

closing = False

peers = []

def broadcast(): # Tracker
  srv=socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
  srv.bind(("localhost:5050"))

def talk():
  pass

broadcastth = threading.Thread(broadcast)
talkth = threading.Thread(talk)

broadcastth.start()
talkth.start()
