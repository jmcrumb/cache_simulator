# Makefile for COMP280 Project 5
 
CC = gcc
CFLAGS = -g -Wall -Werror -std=c11 -D_XOPEN_SOURCE=700

all: csim.o cachelab.o fileio.o load.o init_cache.o save.o linked_list.o
	$(CC) $(CFLAGS) -o csim csim.o cachelab.o fileio.o load.o init_cache.o linked_list.o save.o 
	
csim.o: csim.c
	$(CC) $(CFLAGS) -c csim.c

cachelab.o: cachelab.c cachelab.h
	$(CC) $(CFLAGS) -c cachelab.c

fileio.o: fileio.h fileio.c
	$(CC) $(CFLAGS) -c fileio.c

load.o: load.c load.h
	$(CC) $(CFLAGS) -c load.c

init_cache.o: init_cache.h init_cache.c
	$(CC) $(CFLAGS) -c init_cache.c

save.o : save.c save.h
	$(CC) $(CFLAGS) -c save.c

linked_list.o : linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

upload:
	sshpass -f '/Users/Swgityswag/Desktop/Stuff/passwd' rsync -av -e ssh --exclude='*.git' /Users/Swgityswag/Desktop/p05 jiayelu@BEC307DL09:/home/jiayelu/projects
sync:
	sshpass -f '/Users/MaxonCrumb/Documents/vsWorkspace/usd_ssh_pass.txt' scp -r @BEC307DL14.sandiego.edu:/home/jcrumb/comp280/projects/p05/csim.c /Users/Swgityswag/Desktop/comp280_projects/p05/
#
# Clean the src dirctory
#
clean:
	rm -rf *.o
	rm -f csim
	rm -f trace.all trace.f*
	rm -f .csim_results .marker
