
### This script was used to test the websocket


``
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
python websocket_client.py
``

output

``
--- request header ---
GET / HTTP/1.1
Upgrade: websocket
Host: localhost:8081
Origin: http://localhost:8081
Sec-WebSocket-Key: oh0ERqCGk2jm/JtzxRqT0w==
Sec-WebSocket-Version: 13
Connection: Upgrade


-----------------------
--- response header ---
HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: upgrade
Sec-WebSocket-Accept: 2CHSHzgZ3SdRkOS/dU0Iizhrtf0=
Server: Boost.Beast/313 websocket-server-async
-----------------------
on open
on message
2021-May-10 15:11:55.938503
on message
2021-May-10 15:12:00.939372
on message
2021-May-10 15:12:05.940433
on message
2021-May-10 15:12:10.941426
on message
2021-May-10 15:12:15.942130
on message
2021-May-10 15:12:20.942800
on message
2021-May-10 15:12:25.943459
on message
2021-May-10 15:12:30.944135
on message
2021-May-10 15:12:35.944818
on message
2021-May-10 15:12:40.945660
on message
2021-May-10 15:12:45.946504
on message
2021-May-10 15:12:50.947191
on message
2021-May-10 15:12:55.947863
on message
2021-May-10 15:13:00.948532
on message
2021-May-10 15:13:05.949231
on message
2021-May-10 15:13:10.949929
on message
2021-May-10 15:13:15.950600
on message
2021-May-10 15:13:20.951276
on message
2021-May-10 15:13:25.951972
on message
2021-May-10 15:13:30.952666
on message
2021-May-10 15:13:35.953402
on message
2021-May-10 15:13:40.954178
on message
2021-May-10 15:13:45.955145
on message
2021-May-10 15:13:50.955832
on message
2021-May-10 15:13:55.956494
on message
2021-May-10 15:14:00.957165
on message
2021-May-10 15:14:05.957870
on message
2021-May-10 15:14:10.958537
on message
2021-May-10 15:14:15.959274
on message
2021-May-10 15:14:20.960001
on message
2021-May-10 15:14:25.960731
^C
send: b'\x88\x82O\xa0M\xe5LH'
^C### closed ###
``

