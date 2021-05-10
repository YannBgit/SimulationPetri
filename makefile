# MAIN
#######################################################################################################
runmain: main.o
	./main

main: 
	g++ -Wall main.o Echeancier.o GestionnaireDeFichiers.o InterfaceGraphique.o Moteur.o -o main

main.o:
	g++ -Wall main.cpp -o main.o -g


# CLASSES ANNEXES
#######################################################################################################

Echeancier.o:
	g++ -Wall Echeancier.hpp -o Echeancier.o -g

GestionnaireDeFichiers.o:
	g++ -Wall GestionnaireDeFichiers.hpp -o GestionnaireDeFichiers.o -g

InterfaceGraphique.o:
	g++ -Wall InterfaceGraphique.hpp -o InterfaceGraphique.o -g

Moteur.o:
	g++ -Wall Moteur.hpp -o Moteur.o -g


# DEBUG
#######################################################################################################
debug: main.o
	gdb ./main.o

memcheck: main.o
	valgrind ./main.o


# NETTOYAGE
#######################################################################################################
clean:
	rm -f *.o
	rm -f main
	clear