import os
from pyfbx import Fbx

def search_fbx_files(folder_path, selections, output_file):
    with open(output_file, 'a') as f:
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                if file.lower().endswith('.fbx'):
                    fbx_file_path = os.path.join(root, file)
                    if contains_selection(fbx_file_path, selections):
                        f.write(fbx_file_path + '\n')

def contains_selection(fbx_file, selections):
    fbx = Fbx(fbx_file)
    fbx.load()
    objects = fbx.get_objects()
    for obj in objects:
        if obj.name in selections:
            return True
    return False

folder_path = "test"
selections = ["fireselector", "slide", "ejector"]
output_file = "output.txt"

search_fbx_files(folder_path, selections, output_file)
