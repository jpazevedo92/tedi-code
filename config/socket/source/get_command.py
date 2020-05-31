import os
import json
import re
import ipaddress


app_settings_dir = os.path.abspath(os.path.join(__file__,"..","..","..","..","app","settings"))

"""

    IP Section

"""

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

"""

    MPLS Section

"""
def get_mpls_command(id, iface):
    uav_out_id = str(int(iface[3:-2]) + int(iface[5:]))
    if id == 0:
        with open(app_settings_dir + "/base.json") as json_file:
            data = json.load(json_file)
            #Get Network
            json_out = open(app_settings_dir + "/uav"+ str(id + 1) +".json", 'r')
            network = get_network(json.load(json_out)["interfaces"], iface)
            #Get Out Tag
            routes = data["routes"]
            iface_out=iface[:4]
            tagOut = get_iface_label(routes, iface_out, "out", uav_out_id)
            arguments = "{}_{}_{}".format(network, tagOut, iface_out)
    return arguments


def get_iface_label(dict_objects, name, type, label_contains):
    count = 0
    for dict in dict_objects:
        if type == "in":
            if dict['in_if'] == name and label_contains in dict["in_label"]:
                result = dict["in_label"]
        else:
            if dict['out_if'] == name and label_contains in dict["out_label"]:
                result = dict["out_label"]
    return result


print(get_mpls_command(0, "tun1o3"))