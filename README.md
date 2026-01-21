# ft_IRC

*This project was created as part of the 42 curriculum by cgouveia, dvemba.*

---

## Description

**ft_IRC** is a C++ project that implements a simplified **IRC (Internet Relay Chat) server**.

The main goal is to understand and apply:

- Network programming with **TCP/IP**
- The **sockets API** (socket, bind, listen, accept, recv, send)
- I/O multiplexing with **epoll** (or poll/select)
- Client–server architecture
- The fundamentals of the IRC protocol (RFC 1459)

The server allows multiple clients to connect simultaneously, join channels, send private and channel messages, and manage users through standard IRC commands.

---

## Features

- Non‑blocking TCP server
- Supports multiple simultaneous clients using **epoll**
- Supports basic IRC commands:

  - PASS, NICK, USER, QUIT
  - JOIN, PART, PRIVMSG
  - PING / PONG
  - MODE (i,t,k,l,o), TOPIC, INVITE, KICK
- Channel management (#channel)
- Nickname validation
- Proper error handling according to the IRC protocol

---

## Instructions

### 1. Build

```bash
make
```

This will generate the executable:

```bash
./ircserv
```

### 2. Run

```bash
./ircserv <port> <password>
```

Example:

```bash
./ircserv 6667 my_password
```

### 3. Connect with a client

Using **netcat**:

```bash
nc localhost 6667
```

Using **irssi** (recommended):

```bash
irssi
```

Then, inside irssi:

```text
/connect localhost 6667 my_password
/join #42
/msg #42 Hello world!
```

---

## Project Structure

```text
ft_irc/
├── Makefile
├── inc/
|   ├── Commands/
│   |   ├── CAP.hpp
│   |   ├── Command.hpp
│   |   ├── INVITE.hpp
│   |   ├── JOIN.hpp
│   |   ├── KICK.hpp
│   |   ├── MODE.hpp
│   |   ├── NICK.hpp
│   |   ├── NOTICE.hpp
│   |   ├── PART.hpp
│   |   ├── PASS.hpp
│   |   ├── PING.hpp
│   |   ├── PRIVMSG.hpp
│   |   ├── QUIT.hpp
│   |   ├── TOPIC.hpp
│   |   ├── USER.hpp
│   |   ├── WHO.hpp
│   ├── Channel.hpp
│   ├── Client.hpp
│   ├── IRC.hpp
│   ├── Parser.hpp
│   ├── Server.hpp
│   └── utils.hpp
│   └── Validate.hpp
├── src/
|   ├── Commands/
│   |   ├── CAP.cpp
│   |   ├── Command.cpp
│   |   ├── INVITE.cpp
│   |   ├── JOIN.cpp
│   |   ├── KICK.cpp
│   |   ├── MODE.cpp
│   |   ├── NICK.cpp
│   |   ├── NOTICE.cpp
│   |   ├── PART.cpp
│   |   ├── PASS.cpp
│   |   ├── PING.cpp
│   |   ├── PRIVMSG.cpp
│   |   ├── QUIT.cpp
│   |   ├── TOPIC.cpp
│   |   ├── USER.cpp
│   |   ├── WHO.cpp
│   ├── Channel.cpp
│   ├── Client.cpp
│   ├── IRC.cpp
│   ├── main.cpp
│   ├── Parser.cpp
│   ├── Server.cpp
│   └── utils.cpp
│   └── Validate.cpp
├── Makefile
└── README.md
```

---

## Technical Choices

- **Language:** C++
- **Sockets:** POSIX API (IPv4/IPv6)
- **Multiplexing:** epoll for high performance
- **Architecture:**
  - `Server` → manages sockets and the epoll loop
  - `Client` → represents a connected user
  - `Channel` → manages users inside a channel
  - `Commands` → parses and executes IRC commands

---

## Resources

### Classic References

- RFC 1459 – Internet Relay Chat Protocol
- Linux manual: `man epoll`, `man socket`
- Beej’s Guide to Network Programming
- cppreference – C++ standard library documentation

### Use of AI

AI (ChatGPT) was used for:

- Understanding the IRC protocol and RFC 1459
- Clarifying socket, epoll and non‑blocking I/O concepts
- Supporting the architecture design (Server, Client, Channel, Commands)
- Helping debug network errors and edge cases

All implementation decisions and the final code were produced and validated by the team.

---

## Authors

* cgouveia
* dvemba