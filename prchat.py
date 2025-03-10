# so its easier to test and stuff

"""
PRCHAT ("Peer Chat") Protocol V0

using gpg keys to create subnets of discord-like and skype-like groups
udp over 6040


"""

import socket
import gpg

srv=socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
