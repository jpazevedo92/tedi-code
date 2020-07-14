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
def get_mpls_command(id, iface, operation="switch"):
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
            tagOut = get_iface_label(routes, "none" ,iface_out, uav_out_id)
            arguments = "{}_{}_{}".format(network, tagOut, iface_out)
    else:
        with open(app_settings_dir + "/uav"+ str(id) +".json") as json_file:
            data = json.load(json_file)
            routes = data["routes"]
            iface_in=iface[:4]
            json_out = open(app_settings_dir + "/base.json", 'r')
            uav_network = get_network(data["interfaces"], iface)
            print("uav_network: ", uav_network)
            if operation == "switch":
                base_to_uav_ip = str(ipaddress.IPv4Address(get_ip(data["interfaces"], iface)) + 1)
                uav_to_base_ip = get_ip(data["interfaces"], iface_in)
                tagOut = get_iface_label(routes, "none", iface, uav_out_id)
                tagsOut = get_iface_label(routes, iface_in, iface, uav_out_id)
                tagsOut2 = get_iface_label(routes, iface ,iface_in, uav_out_id)
                arguments = "{}_{}_{}|{}_{}_{}|{}_{}_{}".format(iface, uav_network, tagOut, 
                                                iface,tagsOut, base_to_uav_ip,
                                                iface, tagsOut2, uav_to_base_ip)
            else:
                base_data = json.load(json_out)
                base_network = get_network(base_data["interfaces"], iface_in)
                base_tagOut = get_iface_label(routes, "none", iface)
                uav_tagOut = get_iface_label(routes, "none", iface, uav_out_id)
                arguments = "{}_{}_{}|{}_{}_{}".format(iface, base_network, base_tagOut, iface, uav_network, uav_tagOut)            
    return arguments


def get_iface_label(dict_objects, in_if, out_if, label_contains="None"):
    for dict in dict_objects:
        if dict['out_if'] == out_if and dict['in_if'] == "none" and label_contains in dict["out_label"]:
            result = dict["out_label"]
        if dict['out_if'] == out_if and dict['in_if'] == "none" and label_contains == "None":
            result = dict["out_label"]
        if dict['out_if'] == out_if and dict['in_if'] != "none" and dict['in_if'] == in_if:
            result = dict["in_label"]+ "_" + dict["out_label"]
    return result



