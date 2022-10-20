# Ft_irc  

### Notes

Sur netcat (`nc`) pour tapper un `\r` saisir `ctrl+v`

Sur weechat:

- Ajouter le serveur `/server add name server/port`
- Connexion au serveur `/connect name -password=pass`
- Déconnecion du serveur `/disconnect name`
- Changer de fenetre `ctrl+x`


```
[X] PASS
[X] USER
[X] NICK
[X] VERSION
[X] LUSERS
[X] INFO
[ ] MODE  //progress need make test
[X] PRIVMSG
[X] NOTICE
[X] PING
[X] PONG
[ ] JOIN //work in error
[X] QUIT
[X] OPER //need test
[ ] PART
[S] TOPIC
[ ] NAMES // in progress
[X] TIME
[ ] INVITE
[X] KICK
[X] HELP
```

## Liens

[Modern IRC Client Protocol](https://modern.ircdocs.horse/)

[List of Internet Relay Chat commands](https://en.wikipedia.org/wiki/List_of_Internet_Relay_Chat_commands)

[University Chicago Project](http://chi.cs.uchicago.edu/chirc/index.html)

[c++](https://cplusplus.com/) ou [c++ (old version)](https://legacy.cplusplus.com/)

### RFC

[Internet Relay Chat Protocol](https://www.rfc-editor.org/info/rfc1459) - [Internet Relay Chat Protocol [fr]](http://abcdrfc.free.fr/rfc-vf/rfc1459.html#412)

[Internet Relay Chat: Architecture](https://www.rfc-editor.org/info/rfc2810)

[Internet Relay Chat: Channel Management](https://www.rfc-editor.org/info/rfc2811)

[Internet Relay Chat: Client Protocol](https://www.rfc-editor.org/info/rfc2812)

[Internet Relay Chat: Server Protocol](https://www.rfc-editor.org/info/rfc2813)
