TARGET=file_decode.exe file_encode.exe

INCLUDE=../include
CXX=g++

all:$(TARGET)
$(TARGET):%.exe:%.o HuffmanTree.o
	$(CXX) -o $@ $^
	copy $@ ..\$@
%.o:%.cpp
	$(CXX) -I$(INCLUDE) -c $< -o $@
	
	
.PHONY:clean
clean:
	del *.o
	del file_*.exe