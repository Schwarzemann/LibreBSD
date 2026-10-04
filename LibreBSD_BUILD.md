# LibreBSD Build Guide

This file records the known-good commands for building the NetBSD
10.2_STABLE base used by LibreBSD on Fedora 44.

## Build Environment

Target:

- Machine: `amd64`
- Architecture: `x86_64`
- Base: NetBSD `10.2_STABLE`
- Host: Fedora 44
- Source tree: `/mnt/storage/LibreBSD`
- Object directory: `/mnt/storage/librebsd-obj`
- Tool directory: `/mnt/storage/librebsd-tools`

GCC 15 is used for the host-side bootstrap tools. On this host, GCC 15
defaults to C23, while the NetBSD 10 tree contains old host-tool code
(notably GNU make 3.81) that does not build correctly under that
default. `HOST_CFLAGS="-O -std=gnu17"` therefore forces the host tools
to build as GNU C17.

## Install the Host Compiler

```bash
sudo dnf install gcc15 gcc15-c++
```

Verify the compiler binaries:

```bash
/usr/bin/gcc-15 --version
/usr/bin/g++-15 --version
```

## Clean Build Directories

Only do this when a completely fresh build is required. It removes all
previously generated objects and tools.

```bash
rm -rf /mnt/storage/librebsd-obj /mnt/storage/librebsd-tools
```

## Build the Toolchain

From the LibreBSD source directory:

```bash
cd /mnt/storage/LibreBSD
```

Build the NetBSD host and cross-compilation tools:

```bash
HOST_CC=/usr/bin/gcc-15 HOST_CXX=/usr/bin/g++-15 HOST_CFLAGS="-O -std=gnu17" ./build.sh -U -O ../librebsd-obj -T ../librebsd-tools -j12 -m amd64 tools
```

A successful run should end with output similar to:

```text
Tools built to /mnt/storage/LibreBSD/../librebsd-tools
build.sh ended: ...
===> .
```

## Build the System

After the toolchain has been built, build the NetBSD/LibreBSD system:

```bash
HOST_CC=/usr/bin/gcc-15 HOST_CXX=/usr/bin/g++-15 HOST_CFLAGS="-O -std=gnu17" ./build.sh -U -O ../librebsd-obj -T ../librebsd-tools -j12 -m amd64 build
```

Do not delete `librebsd-obj` or `librebsd-tools` between the toolchain
and system builds. The existing tools are intended to be reused.

Running `build` separately is optional if you intend to run `release`,
because the `release` target performs the necessary system build stages.

## Build a Release

To build the complete release artifacts:

```bash
HOST_CC=/usr/bin/gcc-15 HOST_CXX=/usr/bin/g++-15 HOST_CFLAGS="-O -std=gnu17" ./build.sh -U -O ../librebsd-obj -T ../librebsd-tools -j12 -m amd64 release
```

Release output is placed under:

```text
/mnt/storage/librebsd-obj/releasedir/
```

## Inspect Release Files

List the generated release artifacts:

```bash
find ../librebsd-obj/releasedir -maxdepth 4 -type f | sort
```

For an amd64 release, the bootable installation ISO should be located at:

```text
/mnt/storage/librebsd-obj/releasedir/amd64/installation/cdrom/boot.iso
```

Verify that the ISO exists:

```bash
ls -lh ../librebsd-obj/releasedir/amd64/installation/cdrom/boot.iso
```

## Boot the Release in QEMU

Boot the freshly built system using QEMU with KVM acceleration:

```bash
qemu-system-x86_64 -enable-kvm -m 2G -smp 2 -cdrom ../librebsd-obj/releasedir/amd64/installation/cdrom/boot.iso -boot d
```

The QEMU options mean:

- `-enable-kvm` — use hardware virtualization for better performance.
- `-m 2G` — give the virtual machine 2 GiB of RAM.
- `-smp 2` — give the virtual machine two virtual CPUs.
- `-cdrom .../boot.iso` — attach the generated installation ISO.
- `-boot d` — boot from the virtual CD-ROM.

For the initial baseline test, installation is not required. It is enough
to verify that:

1. The NetBSD bootloader starts.
2. The kernel boots successfully.
3. The NetBSD installer (`sysinst`) appears.

## Known-Good Build Sequence

For normal clean builds, the tested sequence is:

### 1. Enter the source tree

```bash
cd /mnt/storage/LibreBSD
```

### 2. Clean old build output if required

```bash
rm -rf /mnt/storage/librebsd-obj /mnt/storage/librebsd-tools
```

### 3. Build the toolchain

```bash
HOST_CC=/usr/bin/gcc-15 HOST_CXX=/usr/bin/g++-15 HOST_CFLAGS="-O -std=gnu17" ./build.sh -U -O ../librebsd-obj -T ../librebsd-tools -j12 -m amd64 tools
```

### 4. Build the release

```bash
HOST_CC=/usr/bin/gcc-15 HOST_CXX=/usr/bin/g++-15 HOST_CFLAGS="-O -std=gnu17" ./build.sh -U -O ../librebsd-obj -T ../librebsd-tools -j12 -m amd64 release
```

The separate `build` command can be skipped when going directly from
`tools` to `release`.

### 5. Inspect the release

```bash
find ../librebsd-obj/releasedir -maxdepth 4 -type f | sort
```

### 6. Verify the bootable ISO

```bash
ls -lh ../librebsd-obj/releasedir/amd64/installation/cdrom/boot.iso
```

### 7. Boot it in QEMU

```bash
qemu-system-x86_64 -enable-kvm -m 2G -smp 2 -cdrom ../librebsd-obj/releasedir/amd64/installation/cdrom/boot.iso -boot d
```

## Command Summary

Install GCC 15:

```bash
sudo dnf install gcc15 gcc15-c++
```

Verify GCC:

```bash
/usr/bin/gcc-15 --version
/usr/bin/g++-15 --version
```

Enter source tree:

```bash
cd /mnt/storage/LibreBSD
```

Clean:

```bash
rm -rf /mnt/storage/librebsd-obj /mnt/storage/librebsd-tools
```

Toolchain:

```bash
HOST_CC=/usr/bin/gcc-15 HOST_CXX=/usr/bin/g++-15 HOST_CFLAGS="-O -std=gnu17" ./build.sh -U -O ../librebsd-obj -T ../librebsd-tools -j12 -m amd64 tools
```

System:

```bash
HOST_CC=/usr/bin/gcc-15 HOST_CXX=/usr/bin/g++-15 HOST_CFLAGS="-O -std=gnu17" ./build.sh -U -O ../librebsd-obj -T ../librebsd-tools -j12 -m amd64 build
```

Release:

```bash
HOST_CC=/usr/bin/gcc-15 HOST_CXX=/usr/bin/g++-15 HOST_CFLAGS="-O -std=gnu17" ./build.sh -U -O ../librebsd-obj -T ../librebsd-tools -j12 -m amd64 release
```

List release files:

```bash
find ../librebsd-obj/releasedir -maxdepth 4 -type f | sort
```

Verify ISO:

```bash
ls -lh ../librebsd-obj/releasedir/amd64/installation/cdrom/boot.iso
```

Boot ISO:

```bash
qemu-system-x86_64 -enable-kvm -m 2G -smp 2 -cdrom ../librebsd-obj/releasedir/amd64/installation/cdrom/boot.iso -boot d
```

## Why `HOST_CFLAGS` Is Required

On Fedora 44, GCC 15 reports C23 as its default C language version:

```text
#define __STDC_VERSION__ 202311L
```

During the NetBSD tool build, the bundled GNU make 3.81 configure checks
fail under this modern default. One consequence is an incorrect:

```c
#define RETSIGTYPE int
```

which causes incompatible signal-handler declarations and other
compilation failures.

Forcing GNU17 for the host tools avoids this compatibility problem
without modifying the NetBSD source tree:

```bash
HOST_CFLAGS="-O -std=gnu17"
```

This flag applies to the host-side tools. It is not a change to the
target NetBSD/LibreBSD system's source code.