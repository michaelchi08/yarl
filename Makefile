include config.mk

default: all done

all: mkdirs
	@make -s -C src
	# @make -s -C tests

debug: mkdirs
	@make -C src
	# @make -C tests

mkdirs:
	@mkdir -p build
	@mkdir -p build/bin
	@mkdir -p build/obj
	@mkdir -p build/lib

rmdirs:
	@rm -rf build

clean: rmdirs
	@echo "cleaning ..."
	@echo "done! :)"

done:
	@echo "done! :)"
