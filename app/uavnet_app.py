#!/usr/bin/env python3
# -*- coding: utf-8 -*-
 
"""A short description of the module -- called a docstring."""
 
# Imports
import os
import subprocess
import shlex
import json
import ipaddress
 
# Global variables

app_scripts_dir = os.path.abspath(os.path.join(__file__,"..","scripts"))
app_settings_dir = os.path.abspath(os.path.join(__file__,"..","settings"))

# Class definitions
 
# Function definitions

def powerup_vm(vm_name):
	print("Scripts dir: " + app_scripts_dir)
	print("Power up " + vm_name)
	print("Script to run: " + app_scripts_dir + "/start_vm " + vm_name)
	#subprocess.Popen(shlex.split("sh " + app_scripts_dir + "/start_vm " + vm_name))

def config_tunnel(host):
	if host == "Host":
		with open(app_settings_dir + "/base.json") as json_file:
			data = json.load(json_file)
			host_info = data["interfaces"][0]
			remote_ip = ipaddress.IPv4Address(data["local_ip"])+100
			arguments = host_info["name"] + " " + data["local_ip"] + " " + str(remote_ip) + " " + host_info["ip"] + " " + host_info["network"] + host_info["network_mask"]
			print(arguments)
			subprocess.run(shlex.split("sh " + app_scripts_dir + "/tunnel_config -a " + arguments))

#	else

def main():
	""" Launch uavnet_app. """
	print("Launching UAVnet App")
	powerup_vm("TEDI-GUEST1")
	config_tunnel("Host")
	
	

main()



