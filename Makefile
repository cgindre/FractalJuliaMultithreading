GPP=g++
CPPFLAGS=-Wall --std=c++98 -g
# -g for GDB

all: fractalJulia

rgb.o: rgb.cpp
	$(GPP) $(CPPFLAGS) -c -o rgb.o rgb.cpp

colorScale.o: colorScale.cpp rgb.o rgb.h
	$(GPP) $(CPPFLAGS) -c -o colorScale.o colorScale.cpp

fractalJulia.o: fractalJulia.cpp
	$(GPP) $(CPPFLAGS) -c -o fractalJulia.o fractalJulia.cpp

areaThread.o: areaThread.cpp
	$(GPP) $(CPPFLAGS) -c -o areaThread.o areaThread.cpp

fractalJulia: fractalJulia.o colorScale.o colorScale.h rgb.o rgb.h areaThread.o areaThread.h
	$(GPP) $(CPPFLAGS) -lpthread -o fractalJulia areaThread.o fractalJulia.o colorScale.o rgb.o

clean:
	rm fractalJulia *.ppm *.o

