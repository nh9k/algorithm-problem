import os
import json

if __name__ == '__main__':
    dirlist = os.listdir('.')

    inspect_dir = []
    for dirname in dirlist:
        if dirname.find('.') != -1:
            continue

        inspect_dir.append(dirname)
        globals()[dirname] = [0 for _ in range(5)]

        sourcelist = next(os.walk(dirname))[2]
        globals()[dirname][0] = len(sourcelist)
        for source in sourcelist:
            if source.find('baek') != -1:
                globals()[dirname][1] += 1
            elif source.find('programmers') != -1:
                globals()[dirname][2] += 1
            elif source.find('swex') != -1:
                globals()[dirname][3] += 1
            else:
                globals()[dirname][4] += 1

    mdfile = 'README.md'
    f = open(mdfile, 'r', encoding='UTF8')
    lines = f.readlines()
    dir_idx = 0

    for i, line in enumerate(lines):

        if line.find('problems in directories') != -1:
            line = str(sum([sum(globals()[x]) for x in inspect_dir])) + ' problems in directories:   \n'
        elif line.find(inspect_dir[dir_idx]) != -1:
            for l in range(0, 5 if dir_idx != 2 else 1):
                stpoint = lines[i+l].find('(')
                enpoint = lines[i+l].find(')')

                lines[i+l] = lines[i+l][:stpoint+1] + '+' + str(globals()[inspect_dir[dir_idx]][l]) + lines[i+l][enpoint:]

            dir_idx += 1
            if dir_idx == 3:
                break

    with open(mdfile, 'w', encoding='UTF8') as f:
        for i, line in enumerate(lines):
            f.write(line)




