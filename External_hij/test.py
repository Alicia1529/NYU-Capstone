import os  
main = "./external_hij"  + " hi hello"
# if os.path.exists(main):  
#     rc, out = commands.getstatusoutput(main + " hi tiy")  
  
# print('*'*10  ) 
f = os.popen(main)    
data = f.readlines()    
f.close()    
for line in data:
    print(line)
  
print ('*'*10  )
# os.system(main)  