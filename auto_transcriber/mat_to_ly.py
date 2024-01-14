import scipy

dataz = scipy.io.loadmat("./data.mat")['dataz'][0]


# data = scipy.io.loadmat("../data1.mat")['A'][0]
tempo = int(dataz[0][0][0])

# data = dataz[0][1]

end_begin = r"\score{\unfoldRepeats"
end_end = r"\layout { } \midi {\tempo 4 = "+str(tempo)+"}}"


final_res = ""

final_seg = ""

ins = ["cymcb", "sn"]

updown = ["\stemUp", "\stemDown"]

music_begin = r'music = \new DrumStaff \with {instrumentName = "drums" }<<'

# matlab -nodisplay -nosplash -nodesktop -r "run('path/to/your/script.m');exit;"

for i in range(0,2):
    res = ""
    data = dataz[1][0][i][0]
    for x in data[1:]:
        if x == 0:
            continue
        else:
            offset = ""
            if x > 16:
                offset = (x-(x%16))/16 * "r2"
                x=x%16
            if x == 16:
                res = res + ins[i]+"2"
            elif x == 14:
                res = res + ins[i]+"4" + "r8" + "r16"
            elif x == 12:
                res = res + ins[i]+"4" + "r8"
            elif x == 10:
                res = res + ins[i]+"4" + "r16"
            elif x == 8:
                res = res + ins[i]+"4"
            elif x == 6:
                res = res + ins[i]+"8"+"r16"
            elif x == 4:
                res = res + ins[i]+"8"
            elif x == 2:
                res = res + ins[i]+"16"
            # res = res + ins[i] + str(round(x/4) * 4)            

            # if x%16 == 0:
            #     res = res + ins[i] + str(round(x/4) * 4)
            # elif x%8 == 0:
            #     res = res + ins[i] + "8"
            # elif x%4 == 0:
            #     res = res + ins[i] + "16"    
            # else:
                
            # res = res + "sn16\n"
            # res = res + "r16\n"*(x-1)
            res = res + str(offset)
    res = res + ins[i]# +"4\n"
    final_res += r'\new DrumVoice{ \drummode{'+ updown[i] + r'\drummode{'+res + r'}}}'

end = r'>> \score{ \unfoldRepeats \music \layout { }  \midi { \tempo 4 = '+str(tempo)+r' }}'

print(tempo)

with open("output.ly","w") as f:
    f.write(music_begin + final_res+ end)

