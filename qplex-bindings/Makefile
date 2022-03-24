desktop:
	gcc -o program source.c -lraylib -flto -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp

mobile:
	aarch64-linux-gnu-gcc -o program -Iraylib/src -Lraylib/src source.c -lraylib -flto -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp
	#aarch64-linux-gnu-gcc -o program source.c -lraylib -flto -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp
