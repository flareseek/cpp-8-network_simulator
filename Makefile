CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = echo_service_installer.o echo_service.o host.o link_installer.o link.o manual_router.o message_service_installer.o message_service.o node.o packet.o router.o service_installer.o service.o address.o simulator.o object.o packet_sink_service.o packet_sink_service_installer.o bulk_send_service.o bulk_send_service_installer.o auto_router.o nat.o firewall.o

all: first second third forth fifth sixth

first: first.o $(OBJECTS)
	$(CC) $(CFLAGS) -o first first.o $(OBJECTS)

second: second.o $(OBJECTS)
	$(CC) $(CFLAGS) -o second second.o $(OBJECTS)

third: third.o $(OBJECTS)
	$(CC) $(CFLAGS) -o third third.o $(OBJECTS)

forth: forth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o forth forth.o $(OBJECTS)

fifth: fifth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o fifth fifth.o $(OBJECTS)

sixth: sixth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o sixth sixth.o $(OBJECTS)

first.o: scenarios/first.cpp 
	$(CC) $(CFLAGS) -c scenarios/first.cpp 

second.o: scenarios/second.cpp 
	$(CC) $(CFLAGS) -c scenarios/second.cpp 

third.o: scenarios/third.cpp 
	$(CC) $(CFLAGS) -c scenarios/third.cpp 

forth.o: scenarios/forth.cpp 
	$(CC) $(CFLAGS) -c scenarios/forth.cpp 

fifth.o: scenarios/fifth.cpp 
	$(CC) $(CFLAGS) -c scenarios/fifth.cpp 

sixth.o: scenarios/sixth.cpp 
	$(CC) $(CFLAGS) -c scenarios/sixth.cpp 

address.o: address.cpp address.h
	$(CC) $(CFLAGS) -c address.cpp

echo_service_installer.o: echo_service_installer.cpp echo_service_installer.h
	$(CC) $(CFLAGS) -c echo_service_installer.cpp

echo_service.o: echo_service.cpp echo_service.h
	$(CC) $(CFLAGS) -c echo_service.cpp

host.o: host.cpp host.h
	$(CC) $(CFLAGS) -c host.cpp

link_installer.o: link_installer.cpp link_installer.h
	$(CC) $(CFLAGS) -c link_installer.cpp

link.o: link.cpp link.h
	$(CC) $(CFLAGS) -c link.cpp

manual_router.o: manual_router.cpp manual_router.h
	$(CC) $(CFLAGS) -c manual_router.cpp

message_service_installer.o: message_service_installer.cpp message_service_installer.h
	$(CC) $(CFLAGS) -c message_service_installer.cpp

message_service.o: message_service.cpp message_service.h
	$(CC) $(CFLAGS) -c message_service.cpp

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp

packet.o: packet.cpp packet.h
	$(CC) $(CFLAGS) -c packet.cpp

router.o: router.cpp router.h
	$(CC) $(CFLAGS) -c router.cpp

service_installer.o: service_installer.cpp service_installer.h
	$(CC) $(CFLAGS) -c service_installer.cpp

service.o: service.cpp service.h
	$(CC) $(CFLAGS) -c service.cpp

simulator.o: simulator.cpp simulator.h
	$(CC) $(CFLAGS) -c simulator.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp

packet_sink_service.o: packet_sink_service.cpp packet_sink_service.h
	$(CC) $(CFLAGS) -c packet_sink_service.cpp

packet_sink_service_installer.o: packet_sink_service_installer.cpp packet_sink_service_installer.h
	$(CC) $(CFLAGS) -c packet_sink_service_installer.cpp

bulk_send_service.o: bulk_send_service.cpp bulk_send_service.h
	$(CC) $(CFLAGS) -c bulk_send_service.cpp

bulk_send_service_installer.o: bulk_send_service_installer.cpp bulk_send_service_installer.h
	$(CC) $(CFLAGS) -c bulk_send_service_installer.cpp

auto_router.o: auto_router.cpp auto_router.h
	$(CC) $(CFLAGS) -c auto_router.cpp

nat.o: nat.cpp nat.h
	$(CC) $(CFLAGS) -c nat.cpp

firewall.o: firewall.cpp firewall.h
	$(CC) $(CFLAGS) -c firewall.cpp


clean:
	rm -f *.o first second third forth fifth sixth
