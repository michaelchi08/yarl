include config.mk

all: mkdirs gtest libyarl

mkdirs:
	@mkdir -p build
	@mkdir -p build/bin
	@mkdir -p build/obj
	@mkdir -p build/lib
	@mkdir -p build/tests

run_tests: libyarl
	@./build/bin/test_runner --silence-stdcout

gtest:
	@cd $(GTEST_LIB_DIR) && make -s && ar -r libgtest.a gtest-all.o

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
