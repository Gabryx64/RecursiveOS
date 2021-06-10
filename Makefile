KERNEL_HDD = disk.hdd

.PHONY: clean all run

all: $(KERNEL_HDD)

run: $(KERNEL_HDD)
	qemu-system-x86_64 -M q35 -m 2G -drive file=$(KERNEL_HDD),format=raw

debug: $(KERNEL_HDD)
	qemu-system-x86_64 -M q35 -m 2G -drive file=$(KERNEL_HDD),format=raw -s -S

echfs:
	git clone https://github.com/limine-bootloader/limine --branch=master

limine:
	git clone https://github.com/echfs/echfs --branch=latest-binary

src/kernel.elf:
	$(MAKE) -C src

echfs/echfs-utils: echfs
	make -C echfs echfs-utils

limine/limine-install: echfs
	make -C limine

$(KERNEL_HDD): limine/limine-install echfs/echfs-utils src/kernel.elf
	rm -f $(KERNEL_HDD)
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(KERNEL_HDD)
	parted -s $(KERNEL_HDD) mklabel gpt
	parted -s $(KERNEL_HDD) mkpart primary 2048s 100%
	./echfs/echfs-utils -g -p0 $(KERNEL_HDD) quick-format 512
	./echfs/echfs-utils -g -p0 $(KERNEL_HDD) import src/kernel.elf kernel.elf
	./echfs/echfs-utils -g -p0 $(KERNEL_HDD) import limine.cfg limine.cfg
	./echfs/echfs-utils -g -p0 $(KERNEL_HDD) import limine/limine.sys limine.sys
	./limine/limine-install $(KERNEL_HDD)

clean:
	rm -f $(KERNEL_HDD)
	$(MAKE) -C src clean
