#!/usr/bin/python3
import cgi
import cgitb; cgitb.enable() # Optional; for debugging only
import socket

SOCK = "./led.soc"

print("Content-type: text/plain; charset=iso-8859-1\n")

args = cgi.FieldStorage()

with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
    s.connect(SOCK)
    if(args.getvalue("init")):
        s.sendall(b"init;")
    if(args.getvalue("gpio") and args.getvalue("val")):
        msg = f'{args.getvalue("gpio")}:{args.getvalue("val")};'
    s.sendall(msg.encode('utf-8'))

