import websocket
import sys, getopt



print ("The script has the name %s" % (sys.argv[0]))

short_options = "h:p:"
try:
    opts, args = getopt.getopt(sys.argv[1:], short_options)
except getopt.GetoptError:
    print("python websocket_client.py -h <hostname>")
    sys.exit(2)


host = "localhost"
port = 8081
for opt, arg in opts:
    if opt == '-h':
        print("arg = " + arg)
        host = arg
    elif opt == '-p':
        print("arg = " + arg)
        port = arg
    else:
        sys.exit(1)

print("host = " + host)
try:
    import thread
except ImportError:
    import _thread as thread
import time

def on_message(ws, message):
    print("on message")
    print(message)

def on_error(ws, error):
    print(error)

def on_close(ws):
    print("### closed ###")

def on_open(ws):
    print("on open")

if __name__ == "__main__":
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp("ws://{}:{}".format(host, port),
                              on_open = on_open,
                              on_message = on_message,
                              on_error = on_error,
                              on_close = on_close)

    ws.run_forever()
