# libwsjcppjson20client

 Automatically generated by wsjcpp-jsonrpc20. 
 * Version: v0.0.4
 * Date: 07 Oct 2020

 Include script ```dist/libwsjcppjson20client.js```
 Example connect:
```
var client = new SomeClient();
client.bind('server', function(data) { console.log('server', data)})
client.bind('notify', function(data) { console.log('notify', data)})
client.bind('chat', function(data) { console.log('chat', data)})
client.bind('connected', function(data) { console.log('connected', data)})
client.bind('reconnecting', function(data) { console.log('reconnecting', data)})
client.bind('disconnected', function(data) { console.log('disconnected', data)})
client.bind('broken', function(data) { console.log('broken', data)})
client.bind('userdata', function(data) { console.log('userdata', data)})
client.bind('connected', function(data) { console.log('connected', data)})
// connect
client.init({'baseUrl': 'ws://localhost:1234/'})
// disconnect
client.deinit()
```

<details>
<summary>auth_login</summary>

## auth_login

Auth by login and password

Access: unauthorized - **yes**,  user - **no**,  tester - **no**,  admin - **no**

 #### Input params 

 * login - string, required; User Login
 * password - string, required; User Password
 * client_app_name - string, optional; Client app name
 * client_app_version - string, optional; Client app version


 #### example call method 

```
client.auth_login({
    "login": "",
    "password": "",
    "client_app_name": "",
    "client_app_version": ""
}).done(function(r) {
    console.log('Success: ', r);
}).fail(function(err) {
    console.error('Error:', err);
});
```

</details>

<details>
<summary>auth_logoff</summary>

## auth_logoff

Logoff

Access: unauthorized - **no**,  user - **yes**,  tester - **yes**,  admin - **yes**

 #### Input params 



 #### example call method 

```
client.auth_logoff({

}).done(function(r) {
    console.log('Success: ', r);
}).fail(function(err) {
    console.error('Error:', err);
});
```

</details>

<details>
<summary>auth_token</summary>

## auth_token

Auth by token

Access: unauthorized - **yes**,  user - **no**,  tester - **no**,  admin - **no**

 #### Input params 

 * token - string, required; Token
 * client_app_name - string, optional; Client app name
 * client_app_version - string, optional; Client app version


 #### example call method 

```
client.auth_token({
    "token": "",
    "client_app_name": "",
    "client_app_version": ""
}).done(function(r) {
    console.log('Success: ', r);
}).fail(function(err) {
    console.error('Error:', err);
});
```

</details>

<details>
<summary>game_create</summary>

## game_create

Some example of description

Access: unauthorized - **no**,  user - **yes**,  tester - **yes**,  admin - **yes**

 #### Input params 

 * uuid - string, required; object uuid
 * name - string, optional; Name of object
 * cost - integer, required; Name of object
 * age - integer, optional; Name of object
 * public - boolean, required; True if object is public
 * activated - boolean, optional; If object can handle
 * custom - json, optional; Some custom json


 #### example call method 

```
client.game_create({
    "uuid": "",
    "name": "",
    "cost": 0,
    "age": 0,
    "public": "",
    "activated": "",
    "custom": ""
}).done(function(r) {
    console.log('Success: ', r);
}).fail(function(err) {
    console.error('Error:', err);
});
```

</details>

<details>
<summary>server_api</summary>

## server_api

This method Will be return list of all handlers

Access: unauthorized - **yes**,  user - **yes**,  tester - **yes**,  admin - **yes**

 #### Input params 



 #### example call method 

```
client.server_api({

}).done(function(r) {
    console.log('Success: ', r);
}).fail(function(err) {
    console.error('Error:', err);
});
```

</details>
