import os
import json

settings_file = os.path.abspath(os.path.join("settings", "settings.json"))

with open(settings_file,"w") as f:
    # a Python object (dict):
    settings_dict = {
    }
    nodes = input("How many nodes has network? ")

    for x in range(int(nodes)):
        name = input("Name of UAV"+str(x)+"? ")
        ip = input("IP of UAV"+str(x)+"? ")
        uav_dict = {
            "uav"+str(x):{ "id": x, "name":name, "ip": ip }
            }
        settings_dict.update(uav_dict)

    # convert into JSON:
    y = json.dumps(settings_dict, indent=4)

    # the result is a JSON string:
    f.write(y)