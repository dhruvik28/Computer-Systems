all: Part_a Part_b Part_c2 Part_c3 Part2

Part_a: Part_a.c
	gcc Part_a.c -o Part_a

Part_b: Part_b.c
	gcc Part_b.c -o Part_b

Part_c2: Part_c2.c
	gcc Part_c2.c -o Part_c2

Part_c3: Part_c3.c
	gcc Part_c3.c -o Part_c3

Part2: Part2.c
	gcc Part2.c -pthread -o Part2

clean:
	rm Part_a Part_b Part_c2 Part_c3 Part2
