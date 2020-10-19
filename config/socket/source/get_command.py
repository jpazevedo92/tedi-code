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
    list_ids = [int(s) for s in re.findall(r'\d+', iface)]
    id_out = list_ids[1]
    dif = int(iface[5:]) - int(iface[3:-2])
    if dif > 1:
        uav_out_id = str(int(iface[3:-2]) + int(iface[5:]))
    else:
        uav_out_id = str(int(iface[5:])+1)
    id_in = int(iface[3:-2])
    if id == 0:
        with open(app_settings_dir + "/base.json") as json_file:
            data = json.load(json_file)
            #Get Network
            json_out = open(app_settings_dir + "/uav"+ str(id_out) +".json", 'r')
            network = get_network(json.load(json_out)["interfaces"], iface)
            #Get Out Tag
            routes = data["routes"]
            if dif > 1:
                iface_out=iface[:4]
            else:
                if int(iface[3:-2]) > 1:
                    iface_out=iface[:3]+str(int(iface[3:-2])-1)
                else:   
                    iface_out=iface[:4]                
            tagOut = get_iface_label(routes, "none" ,iface_out, uav_out_id)
            arguments = "{}_{}_{}".format(network, tagOut, iface_out)
    else:
        with open(app_settings_dir + "/uav"+ str(id) +".json") as json_file:
            data = json.load(json_file)
            routes = data["routes"]
            if id_in > id:
                iface_in = iface[:3]+str(id)
                iface_out = iface[:3]+str(id)+iface[4:5]+str(id_in)
            elif id_in == id and id_in > 1:
                iface_in = iface[:3]+str(id-1)+iface[4:5]+str(id_in)
                iface_out = iface
            elif id_out == id and id_in > 1:
                iface_in = iface[:3]+str(id-2)
                iface_out = iface        
            else:
                iface_in = iface[:4]
                iface_out = iface
            json_out = open(app_settings_dir + "/base.json", 'r')
            uav_network = get_network(data["interfaces"], iface_out)
            if operation == "switch":
                base_to_uav_ip = str(ipaddress.IPv4Address(get_ip(data["interfaces"], iface_out)) + 1)
                uav_to_base_ip = str(ipaddress.IPv4Address(get_ip(data["interfaces"], iface_in)) - 1)
                if int(uav_out_id) > 3 and dif == 1 and id < 2 :
                    base_data = json.load(json_out)
                    base_network = get_network(base_data["interfaces"], iface_in)
                    tagsOut3 = get_iface_label(routes, iface_in, iface_out, uav_out_id)
                    base_tagOut = get_iface_label(routes, "none", iface_out)
                    uav_json_out = open(app_settings_dir + "/uav"+ str(id_out) +".json")
                    uav_out_data = json.load(uav_json_out)
                    uav_network_out = get_network(uav_out_data["interfaces"], iface)
                    uav_tagOut = get_iface_label(routes, "none", iface_out, uav_out_id)
                    arguments = "{}_{}_{}|{}_{}_{}".format(iface_out, uav_network_out, base_tagOut[1], iface_out, tagsOut3[1], base_to_uav_ip)
                else:
                    arguments = ""
                    tagsOut = get_iface_label(routes, iface_in, iface_out, uav_out_id, id)
                    tagsOut2 = get_iface_label(routes, iface_out ,iface_in, uav_out_id)
                    for tagOut in tagsOut:
                        arguments = arguments + "{}_{}_{}|".format(iface_out,tagOut, base_to_uav_ip)
                    for tagOut2 in tagsOut2:
                        arguments = arguments + "{}_{}_{}|".format(iface_in, tagOut2, uav_to_base_ip)
                    arguments = arguments[:-1]

            else:
                base_data = json.load(json_out)
                base_network = get_network(base_data["interfaces"], iface_in)
                if operation == "lastNode":
                    base_tagsOut = get_iface_label(routes, "none", iface_out)
                    uav_tagOut = get_iface_label(routes, "none", iface)
                else:
                    #base_network = get_network(base_data["interfaces"], iface_in)    
                    base_tagsOut = get_iface_label(routes, "none", iface_out)
                arguments = ""
                count = 0
                if id_in > 1:
                    for tagOut in base_tagsOut:
                        if count > 0:
                            if dif == 1 and id_in > 1:
                                base_network = get_network(base_data["interfaces"], iface_in)
                                if count == 2:
                                    uav_json_out = open(app_settings_dir + "/uav"+ str(id_in) +".json", 'r')
                                    uav_data = json.load(uav_json_out)
                                    base_network = get_network(uav_data["interfaces"], iface[:3]+str(id-2)+iface[4:5]+str(id_in))
                                arguments = arguments + "{}_{}_{}|".format(iface_out, base_network, tagOut)
                        count += 1
                    arguments = arguments[:-1]  
                else:
                    arguments = "{}_{}_{}".format(iface_out, base_network, base_tagsOut[1])
    return arguments

def get_iface_label(dict_objects, in_if, out_if, label_contains="None", id="None"):
    count = 0
    tags = []
    for dict in dict_objects:
        if dict['out_if'] == out_if and dict['in_if'] == "none" and label_contains in dict["out_label"]:
            result = dict["out_label"]
        if dict['out_if'] == out_if and dict['in_if'] == "none" and label_contains == "None":
            tags.append(dict["out_label"])
            result = tags
        if dict['out_if'] == out_if and dict['in_if'] != "none" and dict['in_if'] == in_if:
            count += 1
            if count == id:
                tags.append(dict["in_label"]+ "_" + dict["out_label"])
                result = tags
                return result
            else:
                tags.append(dict["in_label"]+ "_" + dict["out_label"])
                result = tags
    return result

print(get_mpls_command(1, "tun2o3"))

