def solution(m, musicinfos):
    answer_list = []
    for musicinfo in musicinfos:
        splited =  musicinfo.split(',')

        t1 = splited[0].split(':')
        t2 = splited[1].split(':')
        t = (int(t2[0]) - int(t1[0])) * 60 + int(t2[1]) - int(t1[1]) 
        
        music = []
        s3s = splited[3].split('#')
        for i, s3 in enumerate(s3s):
            for si in range(len(s3)-1):
                music.append(s3[si])
            if i == len(s3s)-1:
                music.append(s3[len(s3)-1])
            else:
                music.append(s3[len(s3)-1] + '#')
        
        music_concat = []
        for ti in range(t):   
            music_concat.append(music[ti%len(music)])
   
        m_list = []
        mls = m.split('#')
        for i, ms in enumerate(mls):
            for si in range(len(ms)-1):
                    m_list.append(ms[si])
                    
            if i == len(mls)-1:
                m_list.append(ms[len(ms)-1])
            else:
                m_list.append(ms[len(ms)-1] + '#')
        
        idx = 0
        for mi in range(len(music_concat)):
            if music_concat[mi] == m_list[idx]:
                idx += 1
                if idx == len(m_list):
                    answer_list.append([splited[2], t])
                    break
            else:
                idx = 0 

    if len(answer_list) == 0:
        return "(None)"
    elif len(answer_list) > 1:
        max_time = 0
        answer = ''
        for a in answer_list:
            if max_time < a[1]:
                max_time = a[1]
                answer = a[0]
        
        return answer
    else:
        return answer_list[0][0]
