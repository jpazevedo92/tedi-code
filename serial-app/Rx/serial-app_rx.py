import time
import serial
import socket
from scapy.all import *

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

ser.close()
ser.open()
ser.isOpen()

def mpls_send(mpls_label ,command):

    load_contrib("mpls")
    mpls_eth = Ether(src="08:00:27:a9:35:66", dst="08:00:27:5e:12:78", type=0x8847)
    
    mpls_lables=MPLS(label=16, s=0, ttl=255)/MPLS(label=18, s=0, ttl=255)/MPLS(label=18, s=0, ttl=255)/MPLS(label=16, s=1, ttl=255)
    
    mpls_ip = IP(src='10.0.3.4', dst='10.0.3.5')
    mpls_icmp = ICMP(type="echo-request")
    mpls_raw = Raw(load=command)
    mpls_frame=mpls_eth/mpls_lables/mpls_ip/mpls_icmp/mpls_raw
    
    Ether(str(mpls_frame))
    
    sendp(mpls_frame, iface="eth0")

while 1:
    print(socket.gethostbyname(socket.gethostname()))
    print("Waiting for data\r")
    data = ser.readline().decode()
    
    n_uav, command = data.split("-")
    
    print(data)



