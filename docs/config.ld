project='LNewt'
title='Lua Bindings for Newt Library'
description='Lnewt Simple Library.'

-- format - 'markdown|discount|lunamark|plain|backticks'
format='discount'
all=true
colon=false
--charset='en_GB.UTF-8'
-- Make the docs prettier
pretty='lua'
style='!pale'
backtick_references=false

add_language_extension('lua','c')

-- More fitting section names
kind_names={topic='Documentation', module='Libraries', script='Sample files'}
--kind_names={topic='Manual',script='Programs'}

readme='doc.md'

-- Input folders do Document
file={
	-- C part of LNewt Library
	'../src',
	--'../include'
	'../test'
}

-- Output Documents
dir='../docs'

-- See references to examples..
--examples = {
--	'../test',
--	exclude = {
--		'../test/edev1.lua'
--	}
--}