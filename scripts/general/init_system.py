import os
import subprocess
from uavsystem import *


def init_qgc():
    qgc_path = os.path.abspath(os.path.join(__file__, "..", "..", "..", "..", "..", ".."))
    subprocess.Popen(qgc_path+"/QGroundControl.AppImage", shell=True)


def config_base():
    ### Start qGroundControl
    init_qgc()

    login_info = login("joaopedro7_11@hotmail.com", "24051992a")
    print(login_info)
    
    download_configuration_file(1)


config_base()

