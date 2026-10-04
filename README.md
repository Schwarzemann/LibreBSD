# The LibreBSD Project

LibreBSD is an experimental BSD operating system derived from
NetBSD 10.2_STABLE.

The project is currently in early development. Its primary goals are to
explore operating-system development, gradually develop a distinct
LibreBSD identity, and experiment with improvements to the NetBSD base
while retaining its portability and clean design.

## Current Status

LibreBSD is currently **0.1-dev**.

The system can be built for amd64 and booted under QEMU. Development is
currently focused on:

- System and kernel identification
- Release and installation media
- Userland development
- Understanding and documenting the NetBSD kernel architecture
- LibreBSD-specific kernel development

LibreBSD is not currently intended for production use.

## Source Base

LibreBSD is derived from NetBSD 10.2_STABLE.

The original NetBSD source tree is preserved in the Git history, and the
upstream README can be found in `README.NetBSD.md`.

LibreBSD retains the copyright and license notices of NetBSD and all
other upstream components.

## Source Code

Development takes place in this repository. Changes are made
incrementally so that the differences from upstream NetBSD remain
understandable and traceable.

## Releases

LibreBSD is currently under active development. Development images
should be considered experimental and may contain incomplete or broken
functionality.

## License

LibreBSD contains software originating from NetBSD and other projects.
Individual files and components remain subject to their respective
copyright and license terms.

See the copyright and license notices included throughout the source
tree for details.
