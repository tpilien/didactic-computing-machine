CC = g++
CFLAGS = -Wall -Werror -std=c++98 -g

TARGET = beehives equalizer lcm \
	rna old_school robots spiders \
	shares moon countdown

all: $(TARGET)

beehives: 1_beehives.cpp
	$(CC) $(CFLAGS) -o beehives 1_beehives.cpp

equalizer: 2_equalizer.cpp
	$(CC) $(CFLAGS) -o equalizer 2_equalizer.cpp

lcm: 3_lcm.cpp
	$(CC) $(CFLAGS) -o lcm 3_lcm.cpp

rna: 4_rna.cpp
	$(CC) $(CFLAGS) -o rna 4_rna.cpp

old_school: 5_old_school.cpp
	$(CC) $(CFLAGS) -o old_school 5_old_school.cpp

robots: 6_robots.cpp
	$(CC) $(CFLAGS) -o robots 6_robots.cpp

spiders: 7_spiders.cpp
	$(CC) $(CFLAGS) -o spiders 7_spiders.cpp

shares: 8_rna.cpp
	$(CC) $(CFLAGS) -o shares 8_shares.cpp

moon: 9_moon.cpp
	$(CC) $(CFLAGS) -o moon 9_moon.cpp

countdown: 10_countdown.cpp
	$(CC) $(CFLAGS) -o countdown 10_countdown.cpp

clean:
	$(RM) $(TARGET)
