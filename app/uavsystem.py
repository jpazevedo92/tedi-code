import os
import requests
import re



def login(username, password):
    URL = 'http://uavsystem.com/login'
    session = requests.session()
    front = session.get(URL)
    csrf_token = re.findall('<meta name="csrf-token" content="(.*)"', front.text)[0]
    cookies = session.cookies
    payload = {
        'email': username,
        'password': password,
        '_token': csrf_token,
    }
    
    r = requests.post(URL, data=payload, cookies=cookies)
    return r.headers

def download_configuration_file(id, settings_folder = os.path.abspath(os.path.join(__file__, "..", "settings"))):
    ###GET Request
    download_cfg_url = "http://uavsystem.com/download_cfg/"+str(id)
    r = requests.get(download_cfg_url, allow_redirects=True)
    ##Write to file
    fileName = r.headers.get("content-disposition").split("; ")[1].split("=")[1]
    open(settings_folder+"/"+fileName, 'wb').write(r.content)


