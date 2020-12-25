from setMonitor.mpdu import  *
import os
import socket


sock = socket.socket(socket.AF_INET , socket.SOCK_DGRAM)
dest_ip,dest_port = ('127.0.0.1',10086)


if __name__ == '__main__':
    v = MpduWeb.getCfg().get("mCfg", "version")

    if(3 == int(v)):
        app = Mpdu()
        app.start_fun(sock , dest_ip , dest_port)
        app.close()
    else:
        app = Mpdu()
        app.start_fun(sock , dest_ip , dest_port)
        app.close()

