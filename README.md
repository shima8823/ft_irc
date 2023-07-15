```                                                                                                                   
   ffffffffffffffff           tttt                                    iiii                                         
  f::::::::::::::::f       ttt:::t                                   i::::i                                        
 f::::::::::::::::::f      t:::::t                                    iiii                                         
 f::::::fffffff:::::f      t:::::t                                                                                 
 f:::::f       ffffffttttttt:::::ttttttt                            iiiiiiirrrrr   rrrrrrrrr       cccccccccccccccc
 f:::::f             t:::::::::::::::::t                            i:::::ir::::rrr:::::::::r    cc:::::::::::::::c
f:::::::ffffff       t:::::::::::::::::t                             i::::ir:::::::::::::::::r  c:::::::::::::::::c
f::::::::::::f       tttttt:::::::tttttt                             i::::irr::::::rrrrr::::::rc:::::::cccccc:::::c
f::::::::::::f             t:::::t                                   i::::i r:::::r     r:::::rc::::::c     ccccccc
f:::::::ffffff             t:::::t                                   i::::i r:::::r     rrrrrrrc:::::c             
 f:::::f                   t:::::t                                   i::::i r:::::r            c:::::c             
 f:::::f                   t:::::t    tttttt                         i::::i r:::::r            c::::::c     ccccccc
f:::::::f                  t::::::tttt:::::t                        i::::::ir:::::r            c:::::::cccccc:::::c
f:::::::f                  tt::::::::::::::t                        i::::::ir:::::r             c:::::::::::::::::c
f:::::::f                    tt:::::::::::tt                        i::::::ir:::::r              cc:::::::::::::::c
fffffffff                      ttttttttttt                          iiiiiiiirrrrrrr                cccccccccccccccc
                                            ________________________                                               
                                            _::::::::::::::::::::::_                                               
                                            ________________________                                               
```

### install IRC client

```
brew install irssi

or

sudo apt install irssi
```

### Usage

`make run` or `make && ./ircserv [PORT] [PASSWORD]` for server

`make c n=[NICKNAME]` or `irssi -c [HOST] -p [PORT] -w [PASSWORD] -n [NICKNAME]` for client(irssi)

default: port=6667 password=pass