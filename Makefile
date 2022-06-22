ARCH ?= x86_64

# Check that the architecture is supported and set relevant variables.
ifeq ($(ARCH),x86_64)
    override EFI_ARCH := X64
else
    $(error Architecture $(ARCH) not supported)
endif

.PHONY: all
all: recos.iso

.PHONY: all-hdd
all-hdd: recos.hdd

.PHONY: run
run: recos.iso
	qemu-system-$(ARCH) -serial stdio -vga none -device virtio-vga,xres=960,yres=720 -M q35 -m 2G -cdrom recos.iso -boot d

.PHONY: run-uefi
run-uefi: ovmf-$(EFI_ARCH) recos.iso
	qemu-system-$(ARCH) -serial stdio -vga none -device virtio-vga,xres=960,yres=720 -M q35 -m 2G -bios ovmf-$(EFI_ARCH)/OVMF.fd -cdrom recos.iso -boot d

.PHONY: run-hdd
run-hdd: recos.hdd
	qemu-system-$(ARCH) -serial stdio -vga none -device virtio-vga,xres=960,yres=720 -M q35 -m 2G -hda recos.hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf-$(EFI_ARCH) recos.hdd
	qemu-system-$(ARCH) -serial stdio -vga none -device virtio-vga,xres=960,yres=720 -M q35 -m 2G -bios ovmf-$(EFI_ARCH)/OVMF.fd -hda recos.hdd

ovmf-$(EFI_ARCH):
	mkdir -p ovmf-$(EFI_ARCH)
	cd ovmf-$(EFI_ARCH) && curl -o OVMF-$(EFI_ARCH).zip https://efi.akeo.ie/OVMF/OVMF-$(EFI_ARCH).zip && 7z x OVMF-$(EFI_ARCH).zip

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v3.0-branch-binary --depth=1
	make -C limine

.PHONY: kernel
kernel:
	$(MAKE) -C src
	
recos.iso: limine kernel
	rm -rf iso_root
	mkdir -p iso_root
	cp src/kernel.elf \
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o recos.iso
	limine/limine-deploy recos.iso
	rm -rf iso_root

recos.hdd: limine kernel
	rm -f recos.hdd
	dd if=/dev/zero bs=1M count=0 seek=64 of=recos.hdd
	parted -s recos.hdd mklabel gpt
	parted -s recos.hdd mkpart ESP fat32 2048s 100%
	parted -s recos.hdd set 1 esp on
	limine/limine-deploy recos.hdd
	sudo losetup -Pf --show recos.hdd >loopback_dev
	sudo mkfs.fat -F 32 `cat loopback_dev`p1
	mkdir -p img_mount
	sudo mount `cat loopback_dev`p1 img_mount
	sudo mkdir -p img_mount/EFI/BOOT
	sudo cp -v src/kernel.elf limine.cfg limine/limine.sys img_mount/
	sudo cp -v limine/BOOT$(EFI_ARCH).EFI img_mount/EFI/BOOT/
	sync
	sudo umount img_mount
	sudo losetup -d `cat loopback_dev`
	rm -rf loopback_dev img_mount

.PHONY: clean
clean:
	rm -rf iso_root recos.iso recos.hdd
	$(MAKE) -C src clean

.PHONY: distclean
distclean: clean
	rm -rf limine ovmf-$(EFI_ARCH)
	$(MAKE) -C src distclean