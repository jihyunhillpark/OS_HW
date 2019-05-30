all:
        gcc -o abba abba.c -pthread
        gcc -shared -fPIC -o ddetector.so ddetector.c -ldl -pthread
        gcc -o dinning_deadlock dinning_deadlock.c -pthread
