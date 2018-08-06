import socket
import sys

def send_map(conn):
    conn.sendall("msz 10 5\n")
    conn.sendall("bct 0 0 1\n")
    conn.sendall("bct 0 1 1\n")
    conn.sendall("bct 1 1 1\n")
    conn.sendall("bct 0 2 0\n")
    conn.sendall("bct 2 2 1\n")
    conn.sendall("done\n")

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_addr = ('localhost', 1337)

print >> sys.stderr, 'starting up on %s port %s' % server_addr

sock.bind(server_addr)

sock.listen(2)

while True:
    print >> sys.stderr, 'waiting for connection'
    connection , client_addr = sock.accept()

    try:
        print >>sys.stderr, 'connection from', client_addr

        while True:
            data = connection.recv(2000)
            print >>sys.stderr, 'received [%s]' % data

            if (data and data.strip() == "car"):
                print >> sys.stderr, 'sending data back to client'
                send_map(connection)
            else:
                print >> sys.stderr, 'no more data from ', client_addr
                break
    finally:
        connection.close()


