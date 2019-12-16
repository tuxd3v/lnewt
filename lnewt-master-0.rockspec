rockspec_format	= "1.0"
package		= "lnewt"
version		= "master-0"
description = {
	summary		= "Lua 5.3 Newt Library Bindings..",
	detailed	= [[
		This Library, provide support bindings for Newt Library.
	]],
	homepage	= "https://github.com/tuxd3v/lnewt",
	license		= "See License..",
	maintainer	= "tuxd3v <tuxd3v@sapo.pt>"
}
source = {
	url	= "git://github.com/tuxd3v/lnewt",
	branch	= "master"
}
dependencies = {
	supported_platforms	= "linux",
	"lua >= 5.3"
	--[["lua-dev >= 5.3"
		he doesn't know what is lua5.3-dev, needed to provide "lualib.h","lauxlib.h","lua.h" headers to build shared library..
		That package is provided by apt-get( Operating System Pkg Manager ), Luarocks doesn't know about, but no problem..
	]]
}
build = {
	type			= "make",
	makefile		= "Makefile",
	build_target		= "all",
	build_pass		= true,
	build_variables		= {},
	install_target		= "install",
	install_pass		= true,
	install_variables	= { LDIR="/usr/local/lib/luarocks/rocks/" .. package .. "/" .. version },
	variables		= {},
	modules			= { ats = "src/lnewt.c" }
}