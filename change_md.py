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
        problem_name = {'baek':1,'programmers':2, 'kakao':2, 'swex':3, 'basic':4}
        for source in sourcelist:
            for k, v in problem_name.items():
                if k in source:
                    globals()[dirname][v] += 1
                    break

    mdfile = 'README.md'
    f = open(mdfile, 'r', encoding='UTF8')
    lines = f.readlines()
    dir_idx = 0

    for i, line in enumerate(lines):

        if line.find('problems in directories') != -1:
            lines[i] = str(sum([globals()[x][0] for x in inspect_dir])) + ' problems in directories:   \n'
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

    print('completed')




