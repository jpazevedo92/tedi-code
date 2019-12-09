import os
import re
from uavsystem import *

settings_folder = os.path.abspath(os.path.join(__file__, "..", "settings"))

login_info = login("joaopedro7_11@hotmail.com", "24051992a")
print(login_info)

download_configuration_file(1, settings_folder)

