# LibreBSD Roadmap

This roadmap describes the current development plan for LibreBSD, a NetBSD-derived operating system being developed primarily as a systems-programming learning project.

The goal is not to make LibreBSD different from NetBSD as quickly as possible. The goal is to understand each subsystem, make deliberate changes, and gradually develop a coherent identity for the system.

A successful LibreBSD is one where the developer understands the changes being made and can explain why they exist.

## Current Baseline

The initial development baseline has been established:

- NetBSD `10.2_STABLE` source tree
- Target architecture: `amd64` / `x86_64`
- Development host: Fedora 44
- NetBSD toolchain successfully built
- Complete NetBSD release successfully built
- Bootable `boot.iso` successfully generated
- Release successfully booted in QEMU
- GCC 15 is used for host tools with GNU17 compatibility flags
- QEMU is the primary development and testing environment

The basic development cycle is now:

```text
Understand
    ↓
Change
    ↓
Build
    ↓
Boot/Test in QEMU
    ↓
Review Diff
    ↓
Commit
    ↓
Push
```

---

# Month 1 — Project Foundation and Identity

## Goals

Establish LibreBSD as a clearly identifiable project without making invasive changes to NetBSD.

The first month should primarily be about learning how the NetBSD source tree is organized and how relatively simple source changes propagate into the final operating system.

## Tasks

- Preserve and tag the known-good pristine NetBSD baseline.
- Become familiar with the major NetBSD source directories.
- Maintain documentation for the build and testing process.
- Establish an initial LibreBSD versioning scheme.
- Add initial LibreBSD system identity.
- Change appropriate login banners.
- Change appropriate MOTD text.
- Investigate where operating-system identification is generated.
- Investigate how `uname` obtains system information.
- Investigate installer-visible branding.
- Learn which occurrences of `NetBSD` are branding and which are compatibility identifiers.
- Avoid blindly replacing every occurrence of `NetBSD`.

Important source areas to explore:

```text
sys/        Kernel
bin/        Essential userland commands
sbin/       Essential system administration commands
usr.bin/    General user commands
usr.sbin/   System administration programs
lib/        System libraries
etc/        System configuration
distrib/    Installation and release infrastructure
share/      Shared data, documentation and build infrastructure
```

## First Visible Goal

The first satisfying LibreBSD milestone should be something simple such as booting QEMU and seeing:

```text
Welcome to LibreBSD
```

The important part is knowing exactly which source files produced that result.

## Milestone

By the end of Month 1:

- LibreBSD builds successfully.
- LibreBSD boots successfully.
- The system has an initial LibreBSD identity.
- The pristine NetBSD baseline remains identifiable in Git.
- The build process is documented.
- The developer understands the basic layout of the NetBSD source tree.

---

# Month 2 — Userland Development

## Goals

Learn how programs are integrated into the NetBSD base system.

Rather than immediately modifying complicated kernel code, use small userland programs to learn how NetBSD organizes, builds, installs and documents software.

## Tasks

- Select several small NetBSD utilities.
- Read their source code.
- Understand their Makefiles.
- Follow a program from source code to compilation.
- Understand how programs are installed into `DESTDIR`.
- Follow the program into the final release image.
- Study NetBSD coding conventions.
- Study NetBSD manual pages.
- Write the first LibreBSD-specific userland utility.
- Add the utility properly to the build system.
- Write a manual page for it.

A possible first program could be:

```text
/usr/bin/librebsd-info
```

Possible output:

```text
LibreBSD 0.1-dev
Base: NetBSD 10.2_STABLE
Architecture: amd64
Kernel: ...
```

The exact design should only be decided after understanding how NetBSD already exposes this information.

## Things to Learn

During this stage, become comfortable with:

```text
Makefiles
BSD make
DESTDIR
installation paths
manual pages
NetBSD source conventions
system headers
basic libc interfaces
```

## Milestone

By the end of Month 2, LibreBSD should contain at least one original userland program that:

- Is stored properly in the source tree.
- Uses the normal NetBSD build infrastructure.
- Is automatically compiled.
- Is automatically installed.
- Appears in the resulting LibreBSD system.
- Has a manual page.
- Is understood completely by the developer.

---

# Month 3 — Kernel Fundamentals

## Goals

Begin understanding and modifying the NetBSD kernel without attempting major architectural changes.

The purpose of this stage is to become comfortable navigating kernel code.

## Source Areas

Spend significant time exploring:

```text
sys/kern/
sys/sys/
sys/arch/amd64/
```

Understand the approximate boot path:

```text
Bootloader
    ↓
Kernel entry
    ↓
amd64 machine-dependent initialization
    ↓
Machine-independent kernel initialization
    ↓
init
    ↓
Userland
```

## Tasks

- Find the amd64 kernel entry path.
- Follow early kernel initialization.
- Learn how the `GENERIC` kernel configuration is assembled.
- Understand machine-dependent code.
- Understand machine-independent code.
- Learn where kernel messages originate.
- Study kernel configuration files.
- Study how kernel options are enabled.
- Add a harmless LibreBSD kernel identification message.
- Study the NetBSD sysctl infrastructure.
- Implement a small read-only LibreBSD-specific kernel interface.

A possible experiment:

```text
kern.librebsd.version
```

For example:

```bash
sysctl kern.librebsd.version
```

could eventually return:

```text
kern.librebsd.version = 0.1-dev
```

The purpose is not that LibreBSD desperately needs this sysctl.

The purpose is learning the complete path between kernel state and userland.

## First Kernel Feature

After becoming comfortable with small kernel modifications, implement a tiny experimental feature.

For example, an experimental system information interface or syscall could be used to understand:

```text
Userspace
    ↓
libc / syscall interface
    ↓
System call table
    ↓
Kernel implementation
    ↓
Return to userspace
```

Experimental learning features do not necessarily need to remain permanently in LibreBSD.

Git preserves the work even if an experiment is later removed.

## Milestone

By the end of Month 3:

- Kernel source navigation is becoming comfortable.
- The basic boot sequence is understood.
- Machine-dependent and machine-independent code can be distinguished.
- At least one original kernel modification has been made.
- At least one kernel/userland interface has been studied or implemented.
- The resulting kernel still builds and boots reliably.

---

# Month 4 — Core Kernel Subsystems

## Goals

Move beyond superficial kernel modifications and begin understanding the major operating-system subsystems.

Study these areas approximately in this order:

```text
Processes
    ↓
Virtual Memory
    ↓
VFS / Filesystems
    ↓
Networking
```

---

## Processes

Study:

- Process creation
- `fork`
- `exec`
- Process termination
- Signals
- Scheduling
- Process credentials
- Permissions
- Process structures
- Parent/child relationships

Try to trace a process from creation until termination.

---

## Virtual Memory

Study:

- Virtual address spaces
- Pages
- Page faults
- Memory mappings
- Anonymous memory
- Kernel memory
- User memory
- Machine-dependent MMU code
- Interaction between amd64 code and machine-independent VM code

The goal is not to completely understand the VM subsystem immediately.

The goal is to gradually become capable of following what happens when memory is allocated, mapped, accessed and released.

---

## VFS and Filesystems

Trace ordinary operations such as:

```text
open()
read()
write()
close()
```

Follow them from the userland system call through:

```text
System call
    ↓
Kernel syscall implementation
    ↓
VFS
    ↓
Filesystem
    ↓
Device/storage layer
```

Study how NetBSD separates generic filesystem functionality from individual filesystem implementations.

---

## Development Tools

Become comfortable using tools such as:

```text
git grep
grep
find
ctags
GDB
QEMU
kernel debugging facilities
```

A major skill to develop is not memorizing the kernel.

The important skill is being able to say:

```text
"I don't know how this works yet,
but I know how to trace it."
```

## Milestone

By the end of Month 4, it should be possible to select an ordinary operating-system operation and explain its approximate path through the kernel.

---

# Month 5 — Security and Hardening

## Goals

Begin developing an actual security philosophy for LibreBSD.

At this point OpenBSD can become an important source of ideas and comparison.

However, OpenBSD code should not simply be copied into LibreBSD.

For every possible feature, ask:

```text
What problem does this solve?
        ↓
How does NetBSD currently handle it?
        ↓
How does OpenBSD handle it?
        ↓
What assumptions differ between the systems?
        ↓
Would the design make sense in NetBSD?
        ↓
Can it be implemented or adapted cleanly?
```

## Areas to Study

- Memory-protection defaults
- Privilege separation
- Process hardening
- Kernel information exposure
- Compiler hardening
- Secure defaults
- Service defaults
- Attack-surface reduction
- Permissions
- Kernel security mechanisms

## First Security Work

Prefer small, understandable improvements.

For example, identify one legacy or undesirable default in NetBSD and investigate whether LibreBSD should use a safer default.

Document:

```text
What NetBSD currently does
Why it behaves that way
What security implications exist
What alternatives exist
What LibreBSD changes
Why LibreBSD changes it
```

Do not begin by trying to transplant a massive OpenBSD security subsystem.

## Milestone

By the end of Month 5, LibreBSD should have at least one deliberate security or hardening difference from its NetBSD base, backed by technical reasoning and documentation.

---

# Month 6 — Networking and First Substantial LibreBSD Feature

## Goals

Develop a working understanding of the networking stack and begin designing a more substantial LibreBSD-specific feature.

Trace:

```text
Application
    ↓
socket()
    ↓
Socket layer
    ↓
TCP / UDP
    ↓
IP
    ↓
Network interface
    ↓
Device driver
```

## Tasks

- Study NetBSD socket implementation.
- Trace creation of a socket.
- Trace a simple TCP connection.
- Study TCP and UDP handling.
- Study IP packet processing.
- Study network interfaces.
- Study packet input paths.
- Study packet output paths.
- Study the relationship between protocol code and drivers.
- Compare selected NetBSD networking code with FreeBSD.
- Compare selected NetBSD networking code with OpenBSD.
- Identify a contained improvement or missing feature.
- Design the change before implementing it.

Do not attempt something enormous such as:

```text
"Port the FreeBSD networking stack."
```

Instead, identify something contained:

```text
Diagnostic facility
Small protocol improvement
Kernel statistic
Security improvement
Missing functionality
Useful networking interface
```

## Milestone

By the end of Month 6, implement or begin implementing the first substantial LibreBSD feature based on the knowledge accumulated during the previous months.

---

# Longer-Term Direction

After approximately six months, stop and review what LibreBSD has actually become.

Do not decide too early that LibreBSD must fit one particular category.

Possible future directions include:

- Security-focused BSD
- Simple/minimal BSD
- General-purpose Unix-like system
- Systems-programming research platform
- Server-oriented BSD
- Desktop-oriented BSD
- Experimental operating-system platform

The direction should emerge from actual development experience rather than being imposed prematurely.

---

# Architecture Support

Initially support:

```text
amd64
```

Keep QEMU as the primary reproducible development platform.

Possible later architecture:

```text
aarch64
```

Additional architectures should only be considered after the amd64 system and development workflow are mature.

Portability should still be considered when writing new code, even while amd64 remains the only actively tested LibreBSD architecture.

---

# Things to Postpone

Do not prioritize these during the early stages:

- A new package manager
- A new init system
- A replacement libc
- A new filesystem
- A completely new network stack
- A desktop environment
- Large-scale driver work
- Supporting many architectures
- Huge FreeBSD subsystem ports
- Huge OpenBSD subsystem ports
- Large rewrites merely to make LibreBSD different
- A rushed LibreBSD 1.0 release

These can become future projects if a concrete technical reason develops.

---

# Porting Philosophy

Do not port software or kernel code merely to make LibreBSD different.

Before porting something from FreeBSD, OpenBSD, NetBSD-current or another operating system, determine:

1. What problem does the existing NetBSD implementation have?
2. What does the alternative implementation improve?
3. How does the alternative implementation work?
4. What assumptions does it make about its original operating system?
5. How would it integrate with NetBSD architecture?
6. Can the change be maintained over time?
7. Is porting actually better than implementing a smaller native solution?

Prefer:

```text
Small
Understandable
Testable
Maintainable
Documented
```

over:

```text
Large
Impressive
Copied
Poorly understood
Difficult to maintain
```

---

# Development Workflow

For each non-trivial feature, create a development note containing:

```text
Problem

What currently happens?

What do I want to happen?

Where in NetBSD is this implemented?

How does the existing implementation work?

How do other BSDs solve it?

Proposed implementation

Testing method

Result

What did I learn?
```

Use feature branches:

```bash
git switch librebsd-main
git switch -c feature/name
```

Then follow:

```text
Edit
    ↓
Build
    ↓
Boot/Test
    ↓
Inspect behavior
    ↓
git diff
    ↓
Review
    ↓
Commit
    ↓
Push
```

Possible future Git history:

```text
librebsd: add initial system identity
etc: add LibreBSD login banner
usr.bin: add librebsd-info
sys: expose LibreBSD version through sysctl
amd64: add ...
kern: add ...
security: harden ...
net: implement ...
```

---

# Documentation

Development should be documented alongside the code.

The LibreBSD website can eventually document:

```text
librebsd.libreunix.com
```

Possible sections:

```text
About
Roadmap
Build Guide
Development Log
Documentation
Architecture
Source Code
Experiments
```

Development logs should record not only successful changes but also problems encountered during development.

For example:

```text
Building NetBSD 10.2_STABLE on Fedora 44
GCC 15 and C23 compatibility
Bootstrapping the NetBSD toolchain
Producing the first LibreBSD ISO
Understanding NetBSD userland
Entering the NetBSD kernel
```

This creates a historical record of how LibreBSD developed.

---

# Approximate Timeline

```text
Month 1
Foundation
Source-tree exploration
LibreBSD identity
Build/release workflow
        ↓
Month 2
Userland
BSD make
Manual pages
First LibreBSD utility
        ↓
Month 3
Kernel fundamentals
Boot process
Kernel configuration
sysctl
First kernel modifications
        ↓
Month 4
Processes
Virtual memory
VFS
Filesystem architecture
        ↓
Month 5
Security research
Hardening
OpenBSD comparison
First security changes
        ↓
Month 6
Networking
FreeBSD/OpenBSD comparison
First substantial LibreBSD feature
        ↓
After Month 6
Evaluate LibreBSD's direction
Choose larger projects
Expand architecture support when justified
```

---

# Core Principle

The primary purpose of LibreBSD is learning systems programming and operating-system development.

Twenty small changes that are completely understood are more valuable than hundreds of thousands of lines imported from another operating system without understanding their design.

LibreBSD should evolve through:

```text
Understand NetBSD
        ↓
Identify a problem or opportunity
        ↓
Research existing designs
        ↓
Design a small solution
        ↓
Implement it
        ↓
Build it
        ↓
Test it
        ↓
Document what was learned
        ↓
Repeat
```

The objective is not to make LibreBSD different as quickly as possible.

The objective is to gradually reach the point where LibreBSD is different because there are understood, technically justified reasons for those differences.