#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import logging
import json
import sys
sys.path.insert(1, '../example-of-exported/py3/')

from some_websocket_server import SomeWebsocketServer
from libwsjcppjson20client import SomeClient


TEST_TOKEN = "ctxHhT0wCeC9tZljd3mf"

# start server
# Called for every client connecting (after handshake)
def new_client(client, server):
    print("New client connected and was given id %d" % client['id'])
    nptifyJson = {
        "id": "n0",
        "jsonrpc": "2.0",
        "method": "notification",
        "result": {
            "name": "server",
            "app_name": "simulation_server",
            "app_version": "v0.0.1",
        }
    }
    resp = json.dumps(nptifyJson);
    server.send_message(client, resp)
    # server.send_message_to_all("Hey all, a new client has joined us")

# Called for every client disconnecting
def client_left(client, server):
    print("Client(%d) disconnected" % client['id'])


# Called when a client sends a message
def message_received(client, server, message):
    if len(message) > 200:
        message = message[:200]+'..'
    print("%d >>>  %s" % (client['id'], message))
    recvJson = json.loads(message)
    method = ''
    if 'method' not in recvJson:
        method = recvJson['method']
    responseJson = {
        "id": recvJson['id'],
        "jsonrpc": "2.0",
        "method": method,
    }
    if method == 'server_api':
        responseJson['result'] = {
            "data": [{
                "method": "server_api",
                "description": "Some descr",
                "access_unauthorized": True,
                "access_user": True,
                "access_tester": True,
                "access_admin": True
            }],
            "data_length": 1,
            "version":"v0.0.2",
        }
    elif method == 'auth_login':
        responseJson['result'] = {
            "token": TEST_TOKEN
        }
    elif method == 'auth_token':
        responseJson['result'] = {
            "message": "USER_SESSION_RESTORED",
            "token": TEST_TOKEN
        }
    elif method == 'auth_logoff':
        responseJson['result'] = {
            "message": "USER_SESSION_DESTROYED"
        }
    else:
        responseJson['id'] = recvJson['id']
        responseJson['jsonrpc'] = '2.0'
        responseJson['method'] = method
        responseJson['error'] = {
            "code": 404,
            "message": "NOT_FOUND",
        }
    resp = json.dumps(responseJson);
    print("%d <<< %s" % (client['id'], resp))
    server.send_message(client, resp)

PORT=1234
print("Start server on " + str(PORT))
server = SomeWebsocketServer(PORT, host='0.0.0.0', loglevel=logging.INFO)
server.set_fn_new_client(new_client)
server.set_fn_client_left(client_left)
server.set_fn_message_received(message_received)
# server.run_server_without_waiting()
server.run_forever()
print("Server runned on port " + str(PORT))
