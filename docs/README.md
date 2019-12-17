lnewt
----
Newt bindings library for Lua 5.3

This is a simple [newt][newt] binding library for lua 5.3.

This Library was first forked from [luanewt][luanewt] by [DavidFeng][1st_fork]..
Later, it was forked by me from [luanewt][luanewt]

It has not yet been tested, but will in Devuan..

## TODO

* Test functionalities..
* continue refactoring code
* complete the empty binding functions
* improve the Lua api
* add documentation with [LDoc][LDoc]

### Devuan/Ubuntu

###### 1. Install Dependencies.
 * Install Automatically( method A.1,A.2 in 'Install' section bellow )
   ```lua
   apt-get install lua5.3 lua5.3-dev libnewt-dev gcc make
   update-alternatives --install /usr/bin/lua lua /usr/bin/lua5.3 1
   update-alternatives --install /usr/bin/luac luac /usr/bin/luac5.3 1
   apt-get install luarocks
   ```
 * Install Manually( method B.1,B.2, in 'Install' section bellow )
   ```lua
   apt-get install lua5.3 lua5.3-dev libnewt-dev gcc make
   
   Nota:
   You can also add git, to download the code..
   ```

### Install or Remove
----
2 independent Build Options: Automatic,  Manual.

##### A. Using Luarocks 
 1. Install from master( last code, but more prone to errors.. )
    * `luarocks build https://raw.githubusercontent.com/tuxd3v/lnewt/master/lnewt-master-0.rockspec`
 2. Remove using LuaRocks
    * `luarocks remove lnewt`

##### B. Compile/Install/Remove manually, using make ( need to download first the code ie: with git, by browser).
 1. Compile
    *  ```lua
    make
    #or
    make all
    ```
 2. Install
    * `make install`
 3. Clean local Objects
    * `make clean`
 4. Remove the downloaded code..
    * Not yet implemented..
 5. Remove lnewt
    * Not yet implemented..


[newt]: https://en.wikipedia.org/wiki/Newt_(programming_library)
[luanewt]: https://github.com/SnarkyClark/luanewt
[1st_fork]: https://github.com/DavidFeng/lnewt
[LDoc]: https://github.com/stevedonovan/LDoc
