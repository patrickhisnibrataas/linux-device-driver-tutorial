obj-m := devicedriver.o

all:
	make -C ~/git/linux-internal M=$(PWD) modules
	make -C ~/git/linux-internal M=$(PWD) INSTALL_MOD_PATH=$(PWD) modules_install

clean:
	make -C ~/git/linux-internal M=$(PWD) clean
	rm -rf lib
