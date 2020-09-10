#libwsjcppjson20client

SomeClient Python Library for wsjcpp-jsonrpc20

## Install 

```
$ pip3 install libwsjcppjson20client --upgrade
```

## Example code

```
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from libwsjcppjson20client import SomeClient

client = SomeClient("ws://host/ws-api/")

resp = client.server_api({})

print(resp)
```

Full description API here: [API.md](./API.md)
