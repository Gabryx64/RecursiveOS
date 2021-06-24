KERNEL_HDD = os.hdd
KERNEL_ISO = os.iso

.PHONY: clean all run

all: $(KERNEL_HDD) $(KERNEL_ISO)

run: $(KERNEL_HDD)
	qemu-system-x86_64 -M q35 -m 2G -cpu qemu64,level=11 -drive file=$(KERNEL_HDD),format=raw

debug: $(KERNEL_HDD)
	qemu-system-x86_64 -M q35 -m 2G -cpu qemu64,level=11 -drive file=$(KERNEL_HDD),format=raw -s -S

run-iso: $(KERNEL_HDD)
	qemu-system-x86_64 -M q35 -m 2G -cpu qemu64,level=11 -cdrom $(KERNEL_ISO)

debug-iso: $(KERNEL_HDD)
	qemu-system-x86_64 -M q35 -m 2G -cpu qemu64,level=11 -cdrom $(KERNEL_ISO) -s -S

echfs:
	git clone https://github.com/limine-bootloader/limine --branch=master

limine:
	git clone https://github.com/echfs/echfs --branch=latest-binary

src/kernel.elf:
	$(MAKE) -C src

echfs/echfs-utils: echfs
	make -C echfs echfs-utils

limine/limine-install: limine
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

$(KERNEL_ISO): limine/limine-install echfs/echfs-utils src/kernel.elf
	rm -rf $(KERNEL_ISO) iso_root
	mkdir -p iso_root
	cp -v src/kernel.elf limine.cfg limine/limine.sys \
      	limine/limine-cd.bin limine/limine-eltorito-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
    	-no-emul-boot -boot-load-size 4 -boot-info-table \
    	--efi-boot limine-eltorito-efi.bin \
    	-efi-boot-part --efi-boot-image --protective-msdos-label \
    	iso_root -o $(KERNEL_ISO)
	./limine/limine-install $(KERNEL_ISO)

clean:
	rm -rf $(KERNEL_HDD) $(KERNEL_ISO) iso_root
	$(MAKE) -C src clean
