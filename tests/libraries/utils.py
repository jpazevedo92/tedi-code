import os, shutil
from robot.libraries.BuiltIn import BuiltIn

def clean_log_files(logs_dir="logs"):
    path = os.getcwd()+"/"+logs_dir
    for filename in os.listdir(path):
        file_path = os.path.join(path, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print('Failed to delete %s. Reason: %s' % (file_path, e))
            BuiltIn().log_to_console('Failed to delete %s. Reason: %s' % (file_path, e))