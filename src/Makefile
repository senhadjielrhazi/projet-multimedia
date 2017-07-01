CC=gcc

GL=GL
GLU=GLU
XMU=Xmu
GLUT=glut
X11=X11
XI=Xi
XEXT=Xext
USEFILES=echiquier.c bras.c pion.c fonctions.c tga.c
THREAD=pthread

XPATH=/usr/X11R6/lib
XLIBRARIES=-L$(XPATH) -l$(GL) -l$(GLU) -l$(XMU) -l$(X11) -l$(XI) -l$(XEXT) -l$(THREAD)

GLUTPATH=/home/senhadjielrhazi/OpenGl/glut-3.6/lib/glut/
GLUTLIB=-L$(GLUTPATH) -l$(GLUT)

INCLUDE=-I/home/senhadjielrhazi/OpenGl/glut-3.6/include

.c:
	$(CC) -o $@ $(INCLUDE)  $@.c $(USEFILES) $(GLUTLIB) $(XLIBRARIES)
	rm -f $@.o
