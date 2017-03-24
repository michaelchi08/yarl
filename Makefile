include config.mk

all: mkdirs gtest libbattery

mkdirs:
	@mkdir -p build
	@mkdir -p build/bin
	@mkdir -p build/obj
	@mkdir -p build/lib
	@mkdir -p build/tests

gtest:
	@cd $(GTEST_LIB_DIR) && make -s && ar -rv libgtest.a gtest-all.o

libbattery:
	@make -s -C src
	@make -s -C tests

rmdirs:
	@rm -rf build

clean: rmdirs
	@echo "cleaning ..."
	@echo "done! :)"

done:
	@echo "done! :)"
