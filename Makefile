CC = gcc
CFLAGS = -Wall -Wextra -O2 \
         -I/Users/subhashgottumukkala/Developer/packages/quiche/quiche/include/ \
         -I/opt/homebrew/Cellar/openssl@3/3.4.0/include/
LDFLAGS = -L/Users/subhashgottumukkala/Developer/packages/quiche/target/release/ \
          -L/opt/homebrew/Cellar/openssl@3/3.4.0/lib/ \
          -lssl -lcrypto -lquiche

SRCS = main.c server.c tls.c quic.c utils.c
OBJS = $(SRCS:.c=.o)

all: http3_server

http3_server: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o http3_server