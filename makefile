file_encoder.exe: file_encode.o
	g++ -o file_encoder.exe file_encode.o
file_encode.o:file_encode.cpp
	g++ -c file_encode.cpp