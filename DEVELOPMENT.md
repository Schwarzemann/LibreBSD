# LibreBSD Development Workflow

This document is a quick reference for making and pushing changes to LibreBSD.

## Repository Setup

LibreBSD uses two Git remotes:

- `origin` — private LibreBSD repository.
- `upstream` — official NetBSD source repository.

Check them with:

```bash
git remote -v
```

Expected:

```text
origin    https://github.com/Schwarzemann/LibreBSD.git (fetch)
origin    https://github.com/Schwarzemann/LibreBSD.git (push)
upstream  https://github.com/NetBSD/src.git (fetch)
upstream  DISABLED (push)
```

The main LibreBSD development branch is:

```text
librebsd-main
```

The `netbsd-10` branch should remain an upstream tracking branch.

---

## Before Starting Work

Make sure you are on the LibreBSD branch:

```bash
git switch librebsd-main
```

Check the repository:

```bash
git status
```

You should normally see:

```text
On branch librebsd-main
Your branch is up to date with 'origin/librebsd-main'.

nothing to commit, working tree clean
```

Optionally pull your latest LibreBSD changes if work may have been done elsewhere:

```bash
git pull --ff-only
```

---

## Making a Change

Edit the source normally.

While working, inspect what you have changed:

```bash
git status
```

and:

```bash
git diff
```

For a particular file:

```bash
git diff path/to/file.c
```

Do not commit code that you do not understand.

Build and test the change before committing whenever practical.

---

## Committing a Change

First inspect everything:

```bash
git status
git diff
```

Stage only the files belonging to the change:

```bash
git add path/to/file.c
```

Multiple files can be staged:

```bash
git add file1.c file2.c
```

Check what will actually be committed:

```bash
git diff --cached
```

Then commit:

```bash
git commit -m "subsystem: short description of change"
```

Examples:

```text
kern: add initial process restriction support
netinet: improve TCP handling for ...
amd64: fix ...
libc: add interface for ...
docs: document LibreBSD build process
```

Prefer small, logically self-contained commits.

---

## Pushing to LibreBSD

Push committed changes with:

```bash
git push
```

Because `librebsd-main` tracks `origin/librebsd-main`, this pushes to the private LibreBSD repository.

Check the tracking configuration with:

```bash
git branch -vv
```

Expected relationship:

```text
librebsd-main -> origin/librebsd-main
netbsd-10     -> upstream/netbsd-10
```

Never push LibreBSD development to `upstream`.

---

## Creating a Feature Branch

For larger or experimental changes, create a branch from `librebsd-main`:

```bash
git switch librebsd-main
git switch -c feature/name
```

For example:

```bash
git switch -c feature/pledge
```

Work and commit normally.

Push the branch if it should be backed up:

```bash
git push -u origin feature/pledge
```

When the work is ready, it can later be merged into `librebsd-main`.

---

## Getting New NetBSD Changes

Fetch NetBSD without modifying LibreBSD:

```bash
git fetch upstream
```

This updates remote references such as:

```text
upstream/netbsd-10
```

It does **not** automatically modify `librebsd-main`.

To inspect upstream commits:

```bash
git log librebsd-main..upstream/netbsd-10 --oneline
```

Do not blindly merge upstream changes.

Review them first, especially once LibreBSD begins modifying the same subsystems.

---

## Comparing LibreBSD With NetBSD

See LibreBSD commits that aren't in upstream NetBSD:

```bash
git log upstream/netbsd-10..librebsd-main --oneline
```

See the source differences:

```bash
git diff upstream/netbsd-10..librebsd-main
```

Compare a particular file:

```bash
git diff upstream/netbsd-10..librebsd-main -- path/to/file.c
```

The original LibreBSD fork point is tagged:

```text
librebsd-base-0
```

Compare against the original pristine source:

```bash
git diff librebsd-base-0..librebsd-main
```

---

## If Something Goes Wrong

Before doing anything destructive:

```bash
git status
git diff
git log --oneline -10
```

Do **not** immediately use commands such as:

```text
git reset --hard
git clean -fd
git push --force
```

unless you understand exactly what they will remove.

If unsure, stop and investigate first. Git usually still has the work unless a destructive operation explicitly removes it.

---

## Normal Daily Workflow

Most LibreBSD development sessions should ultimately be this simple:

```bash
git switch librebsd-main
git status

# Edit source
# Build
# Test

git diff
git add <changed files>
git diff --cached
git commit -m "subsystem: describe the change"
git push
```

Then continue hacking.

## Rule

**Understand → Change → Build → Test → Review Diff → Commit → Push**

Keep `librebsd-main` in a state that is useful to return to. Use feature branches for experiments that may substantially break the system.
