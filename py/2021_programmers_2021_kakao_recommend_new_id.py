import string

def solution(new_id):
    # 1
    new_id = new_id.lower()
    
    # 2
    new_id2 = ''
    for i in range(len(new_id)):
        if new_id[i] in list(string.ascii_lowercase) or new_id[i] in [str(num) for num in range(10)] or new_id[i] in ['-','_','.']:
            new_id2 = new_id2 + new_id[i]
    # 3
    new_id = ''
    for i in range(len(new_id2)):
        if new_id2[i] == '.' and new_id == '':
            new_id = new_id2[i]
        elif new_id2[i] == '.' and new_id[-1] != '.':
            new_id = new_id + new_id2[i]
        elif new_id2[i] != '.':
            new_id = new_id + new_id2[i]
            
    # 4
    if len(new_id) == 1 and new_id == '.':
        new_id = ''
    else:
        if new_id[0] == '.' :
            new_id = new_id[1:]
        if new_id[-1] == '.':
            new_id = new_id[:-1]

    # 5 
    if new_id == '':
        new_id = 'a'
        
    # 6
    if len(new_id) >= 16:
        new_id = new_id[:15]
        if new_id[-1] == '.':
            new_id = new_id[:-1]
    
    # 7
    if len(new_id) <= 2:
        while len(new_id) != 3:
            new_id = new_id + new_id[-1]
            

    return new_id