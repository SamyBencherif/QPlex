program: source.c qpcommons.h
	gcc -o program -Iraylib/src source.c -flto -lraylib -Lraylib/src  -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp

boot:
	sudo startx ./program
