import os 
  
print('*'*10  ) 

os.system("cmake External_hij/CMakeLists.txt")
os.system("(cd External_hij && make)") 
os.system("./External_hij/external_hij")     
  
print ('*'*10  ) 