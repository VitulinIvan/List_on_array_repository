file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${ArrayList} STATIC ${srcs} ${hdrs}) 

