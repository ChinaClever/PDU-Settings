from ctrlset_xrpdu.xrpdu import  *
import os
import socket
import datetime
#import sys


sock = socket.socket(socket.AF_INET , socket.SOCK_DGRAM)
dest_ip,dest_port = ('127.0.0.1',10086)


if __name__ == '__main__':
    print(datetime.datetime.now())
    app = XRpdu()
    app.start_fun(sock , dest_ip , dest_port)
    app.close()
   

