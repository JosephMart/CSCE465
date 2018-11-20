INC=/usr/local/opt/openssl/include
LIB=/usr/local/opt/openssl/lib

all:
	g++ -I$(INC) -L$(LIB) -o enc main.cpp -lcrypto -std=c++17

test: test.cpp
	gcc test.cpp \
		-o test \
		-I /usr/local/opt/openssl/include \
		-L /usr/local/opt/openssl/lib \
		-lcrypto
