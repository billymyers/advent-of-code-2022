import os, re, os.path
pattern = "^.*\.(exe|pdb|out|obj)$"

if __name__ == "__main__":
    for r, subdirs, files in os.walk(os.getcwd()):
        for file in filter(lambda x: re.match(pattern, x), files):
            os.remove(os.path.join(r, file))