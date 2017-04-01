include config.mk

all: mkdirs libyarl

mkdirs:
	@mkdir -p build
	@mkdir -p build/bin
	@mkdir -p build/obj
	@mkdir -p build/lib
	@mkdir -p build/tests

run_tests: libyarl
	@./build/bin/test_runner --silence-stdcout

libyarl:
	@make -s -C src
	@make -s -C tests

rmdirs:
	@rm -rf build

clean: rmdirs
	@echo "cleaning ..."
	@echo "done! :)"

done:
	@echo "done! :)"
