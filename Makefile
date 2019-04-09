compile = g++ -c -o
link = g++ -o
primary = driver
secondary = encoder
rm = rm -f
tar = tar -cvf
zip = jar -cMf
archives = tar zip
stuno = WLFJAD001
flags = -std=c++11 -fPIC

$(primary): $(secondary).o $(primary).o
	$(link) $(primary) $(primary).o $(secondary).o $(flags)

$(primary).o:
	$(compile) $(primary).o $(primary).cpp $(flags)

$(secondary).o:
	$(compile) $(secondary).o $(secondary).cpp $(flags)

run: $(primary)
	./driver

clean:
	$(rm) $(primary) $(primary).o $(secondary).o
