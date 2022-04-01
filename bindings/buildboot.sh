
while true ; do
  gcc -o program -Iraylib/src source.c -flto -lraylib -Lraylib/src  -lm -ldl -lpthread -lX11 -lxcb -lGL -lGLX -lXext -lGLdispatch -lXau -lXdmcp
  if [ "$?" = "0" ] ; then
    sudo startx ./program
  else
    read pause
    clear
  fi
done
