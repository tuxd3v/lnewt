Targetdoc  := ./doc

default: html

.PHONY: clean
clean:
	$(info ** Deleting Documentation, in $(Targetdoc) base folder **)
	@rm -rf $(Targetdoc)/./*

.PHONY: install
install:

.PHONY: html
html: clean
	$(info ** Genetating Documentation, in $(Targetdoc) base folder **)
	doxygen doxyfile.conf
#	@asciidoctor $(Style)  $(Src)

.PHONY: preview
preview: html
	$(info ** Showing Documentation, in $(Targetdoc) base folder **)
	@chromium ${PWD}/$(Targetdoc)/html/index.html
#	@google-chrome $(Html)

