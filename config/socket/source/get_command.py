import os
import json
import re
import ipaddress


app_settings_dir = os.path.abspath(os.path.join(__file__,"..","..","..","..","app","settings"))

#print(app_settings_dir)

def get_command(id, iface, option="route"):
    list_ids = [int(s) for s in re.findall(r'\d+', iface)]
    id_out = list_ids[1]
    if option == "route":
        if id == 0:
            with open(app_settings_dir + "/base.json") as json_file:
                data = json.load(json_file)
                host_info = data["interfaces"][id]
                if_out = host_info["name"]
                json_out = open(app_settings_dir + "/uav"+ str(id_out) +".json", 'r')
                network = get_network(json.load(json_out)["interfaces"], iface)
                ip_out = str(ipaddress.IPv4Address(host_info["ip"])+1)
                arguments = "{}_{}_{}".format(if_out, network, ip_out)

        else:
            with open(app_settings_dir + "/uav"+ str(id) +".json") as json_file:
                data = json.load(json_file)
                json_out = open(app_settings_dir + "/base.json", 'r')
                network = get_network(json.load(json_out)["interfaces"], "tun1")
                ip_out =  str(ipaddress.IPv4Address(get_ip(data["interfaces"], iface))-1)
                arguments = "{}_{}_{}".format(iface, network, ip_out)
    else:
        if id > 1:
            with open(app_settings_dir + "/uav"+ str(id) +".json") as json_file:
                data = json.load(json_file)
                host_info = data["interfaces"]
                if_in = host_info[1]["name"]    
                arguments = "{}_{}".format(if_in, iface)
        else:
            with open(app_settings_dir + "/uav"+ str(id) +".json") as json_file:
                data = json.load(json_file)
                host_info = data["interfaces"]
                if_in = host_info[0]["name"]    
                arguments = "{}_{}".format(if_in, iface)      
    return arguments

def get_network(dict_objects, name):
    for dict in dict_objects:
        if dict['name'] == name:
            return dict['network'] + dict['network_mask']

def get_ip(dict_objects, name):
    for dict in dict_objects:
        if dict['name'] == name:
            return dict['ip']

    #print(dict_objects)

# def turn_off_tunnel(in_tun):

#     return result

print(get_command(1, "tun1o2", "tables"))
