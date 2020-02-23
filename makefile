all:
	cd src&&make

.PHONY:clean cleandata cleanall
cleanall:clean cleandata
clean:
	del file_*.exe
	cd src&&make clean
cleandata:
	del codefile
	del hfmtree
	del textfile.txt
	del treeprint.txt
	del codeprint.txt