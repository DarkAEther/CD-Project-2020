import re
import sys
'''
Operations Supported:
MOV
LD
ADD
SUB
MUL
DIV
B(LT,LTE,GT,GTE,E)
'''
c=""
t=""
mapping={
    "+":("ADD","",""),
    "-":("SUB","",""),
    "*":("MUL","",""),
    "/":("DIV","",""),
    "<":("CMP","LT","GTE"),
    "<=":("CMP","LTE","GT"),
    ">":("CMP","GT","LTE"),
    ">=":("CMP","GTE","LT"),
    "==":("CMP","E","NE"),
    "goto":("B","",""),
    "ifFalse":("B","",""),
    "if":("B","",""),
    "Label":("L","","")

}

registers={
    "r0":"",
    "r1":"",
    "r2":"",
    "r3":"",
    "r4":"",
    "r5":"",
    "r6":"",
    "r7":"",
    "r8":"",
    "r9":"",
    "r10":"",
    "r11":"",
    "r12":"",
    "r13":"",
    "r14":"",
    "r15":"",
    "r16":"",
    "r17":"",
    "r18":"",
    "r19":"",
    "r20":""
}

def findvar(var):
    for i in registers.keys():
        if registers[i]!="" and registers[i]!=1:
            #print("Yowza")
            if registers[i][0]==var:
                registers[i][1]=5
                return i
    return -1

def updatereg():
    for i in registers.keys():
        if registers[i]!="" and registers[i]!=1:
            if registers[i][1]==0:
                print(";Variable unused. Storing it back to free space")
                print("ST {mem},{reg}".format(reg=i,mem=registers[i][0]))
                registers[i]=""
            else:
                registers[i][1]-=1
    return -1

def setvar(var):
    reg=getReg()
    #print("Hi")
    registers[reg]=[var,5]
    return reg

def getReg():
    for i in registers.keys():
        if registers[i]=="":
            return i
    return -1

def release(reg):
    registers[reg]=""

def assignment(args):
    var=findvar(args[3])
    reg=0
    reg1=0
    if var==-1:
        var=setvar(args[3])
        if(args[3] in variables):
            print("LD {reg}, {val}".format(reg=var,val=args[3]))
        else:
            variables.append(args[3])
    if args[1].isidentifier():
        reg1=findvar(args[1])
        if reg1==-1:
            reg1=setvar(args[1])
            if(args[1] in variables):
                print("LD {reg}, {val}".format(reg=reg1,val=args[1]))
            else:
                variables.append(args[1])
        print("MOV {reg}, {val}".format(reg=var,val=reg1))
    else:
        reg=getReg()
        print("MOV {reg}, #{val}".format(reg=var,val=args[1].split(".")[0]))
    
    #print("MOV {var}, {reg}".format(var=var,reg=reg))
    if(reg!=0):
        release(reg)

def expression(args):
    op=mapping[args[0]]
    t1=0
    t2=0
    imm=0
    immval=""
    global c
    global t
    reg1=-1
    reg2=-1
    if(op[0]=="CMP"):
        t=op[1]
        c=op[2]
        if(re.search("^[0-9]",args[1])):
            reg1=getReg()
            print("MOV {reg1}, {val}".format(reg1=reg1,val=args[1].split(".")[0]))
            t1=1
        if args[1].isidentifier():
            reg1=findvar(args[1])
            if reg1==-1:
                reg1=setvar(args[1])
                if(args[1] in variables):
                    print("LD {reg}, {val}".format(reg=reg1,val=args[1]))
                else:
                    variables.append(args[1])
                #print("LD {reg}, {val}".format(reg=reg1,val=args[1]))

        if(re.search("^[0-9]",args[2])):
            reg2=getReg()
            print("MOV {reg2}, {val}".format(reg2=reg2,val=args[2].split(".")[0]))
            t2=1
        if args[2].isidentifier():
            reg2=findvar(args[2])
            if reg2==-1:
                #print("Yowza")
                reg2=setvar(args[2])
                if(args[2] in variables):
                    print("LD {reg}, {val}".format(reg=reg2,val=args[2]))
                else:
                    variables.append(args[2])
                #print("LD {reg}, {val}".format(reg=reg1,val=args[1]))
        print("CMP {reg1},{reg2}".format(reg2=reg2,reg1=reg1))
    elif (op[0][0]=="B"):
        if(args[0]=="ifFalse"):
            print(op[0]+c+" "+args[3])
            t=op[1]
            c=op[2]
        else:
            print(op[0]+t+" "+args[3])
            t=op[1]
            c=op[2]
    elif (op[0]=="L"):
        print(args[3]+":")
        t=op[1]
        c=op[2]
    else:
        if(re.search("^[0-9]",args[1])):
            imm=1
            immval="#"+args[1].split(".")[0]
        else:
            reg1=findvar(args[1])
            if reg1==-1:
                reg1=setvar(args[1])
                if(args[1] in variables):
                    print("LD {reg}, {val}".format(reg=reg1,val=args[1]))
                else:
                    variables.append(args[1])
                #print("LD {reg}, {val}".format(reg=reg1,val=args[1]))


        if(re.search("^[0-9]",args[2])):
            if(imm):
                reg2=getReg()
                registers[reg2]=1
                print("MOV {reg2}, #{val}".format(reg2=reg2,val=args[2].split(".")[0]))
                t2=1
            else:
                imm=1
                immval="#"+args[2].split(".")[0]
        else:
            reg2=findvar(args[2])
            if reg2==-1:
                reg2=setvar(args[2])
                if(args[1] in variables):
                    print("LD {reg}, {val}".format(reg=reg2,val=args[1]))
                else:
                    variables.append(args[1])
                #print("LD {reg}, {val}".format(reg=reg2,val=args[2]))
        reg3=findvar(args[3])
        if reg3==-1:
            reg3=setvar(args[3])
            if(args[3] in variables):
                print("LD {reg}, {val}".format(reg=reg3,val=args[3]))
            else:
                variables.append(args[3])
            #print("LD {reg}, {val}".format(reg=reg3,val=args[3]))
        if(imm):
            if(reg1!=-1):
                print("{expres} {reg3}, {reg1}, {reg2}".format(expres=op[0],reg3=reg3,reg1=reg1,reg2=immval))
            if(reg2!=-1):
                 print("{expres} {reg3}, {reg1}, {reg2}".format(expres=op[0],reg3=reg3,reg1=reg2,reg2=immval))
        else:
            print("{expres} {reg3}, {reg1}, {reg2}".format(expres=op[0],reg3=reg3,reg1=reg1,reg2=reg2))
        #print("ST {var}, {reg}".format(var=args[3],reg=reg3))
        if(t1==1):
            release(reg1)
        if(t2==1):
            release(reg2)
        

def get_icg():
    path=sys.argv[1]
    f=open(path,"r")
    x=f.read().split("@")[1]
    x=x.split('\n')
    x=list(map(lambda i:i.split(','),x))
    return x
variables=[]

x=get_icg()
for i in x:
    if(i[0]) != "":
        if i[0]=='=':
            assignment(i)
        else:
            expression(i)
    #print(variables)
    updatereg()

print("------------------------------Register Summary--------------------------------")
print("Register\tVar,Val")
for i in registers.keys():
    val=registers[i]
    if val=="":
        val="[None,None]"
    print(i,"\t",val)
print("------------------------------End of Register Summary--------------------------------")
print(";Program Terminated, storing all variables in registers back to memory")
for i in registers.keys():
    if registers[i]!="" and registers[i]!=1:
        print("ST {mem},{reg}".format(reg=i,mem=registers[i][0]))
        registers[i]=""