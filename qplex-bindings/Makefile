program: source.c
	gcc -o program -Iraylib/src source.c -flto -lraylib -Lraylib/src  -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp

boot:
	gcc -o program -Iraylib/src source.c -flto -lraylib -Lraylib/src  -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp
	sudo startx ./program
