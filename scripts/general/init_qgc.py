import os
import subprocess

qgc_path = os.path.abspath(os.path.join(__file__, "..", "..", "..", "..", "..", ".."))
subprocess.call(qgc_path+"/QGroundControl.AppImage", shell=True);
