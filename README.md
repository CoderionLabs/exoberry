DEOS
=======================
**[Mailing List](https://docs.google.com/forms/d/e/1FAIpQLSes4ibh1F-PTGdaPns6k446ODwOSNaju3DksLgOB_Zo-IMu_Q/viewform?usp=sf_link)
| [![Build Status](https://travis-ci.org/friedrich12/DEOS.svg?branch=master)](https://travis-ci.org/friedrich12/DEOS)**


![alt text](https://upload.wikimedia.org/wikipedia/commons/f/f2/Exokernel_revised%28english%29.png)


Graphic overview of an exokernel. Exokernels are much smaller than a normal kernels \(monolithic kernels\). They give more direct access to the hardware, thus removing most abstractions

The distributed exokernel operating system (DEOS) is an open-source operating system.
That targets distributed systems such as clusters and grids. DEOS is designed for these systems
and performace on these systems should be better than the average OS. This project is inspired from
Dawson Engler's work of the M.I.T exokernel.

Haiku is an open-source operating system that specifically targets personal
computing. Inspired by the BeOS, Haiku is fast, simple to use, easy to learn
and yet very powerful.

**Motivation**

Traditionally kernel designers have sought to make individual hardware resources invisible to application programs by requiring the programs to interact with the hardware via some abstraction model. These models include file systems for disk storage, virtual address spaces for memory, schedulers for task management, and sockets for network communication. These abstractions of the hardware make it easier to write programs in general, but limit performance and stifle experimentation in new abstractions. A security-oriented application might need a file system that does not leave old data on the disk, while a reliability-oriented application might need a file system that keeps such data for failure recovery.

One option is to remove the kernel completely and program directly to the hardware, but then the entire machine would be dedicated to the application being written \(and, conversely, the entire application codebase would be dedicated to that machine\). The exokernel concept is a compromise: let the kernel allocate the basic physical resources of the machine \(e.g. disk blocks, memory pages, and processor time\) to multiple application programs, and let each program decide what to do with these resources. The program can then link to a support library that implements the abstractions it needs \(or it can implement its own\).

Goals
------------
 * Clean, code. 
 * Minimal configuration required.
 * Clean, clear, concise code.
 * High performance for web servers.
 * Long term support.
 * Distributed system friendly.

Trying DEOS
---------------
DOES right now does not provide images. See Compiling to create and image.

Compiling DEOS
---------------
Clone the repository.

```
$ git clone https://github.com/friedrich12/DEOS/ DEOS
```
Make sure gcc-multilib is installed.

```
$ sudo apt-get update
$ sudo apt-get install gcc-multilib
```

Go to directory and run make and make qemu.
```
$ cd DEOS
$ make
$ make qemu
```

Contributing
-------------------
DEOS is a meritocratic open source project with a large variety of tasks. Even if you can't write code, you can still help! DEOS needs designers, \(technical\) writers, translators, testers... Get involved and help out!

## Contributing code
To submit code fork this respository and submit a pull request like usual. 

## Contributing documentation
Write now nothing is really documented. Just find an undocumented class, write
documentation for it, and [submit a patch](https://github.com/friedrich12/DEOS/PATCHES.md).

## Contributing software ports
Right now there is not a software porter see issue 8.

## Exokernel?

[https://en.wikipedia.org/wiki/Exokernel](https://en.wikipedia.org/wiki/Exokernel) [ ](http://wiki.osdev.org/Exokernel)

[http://wiki.osdev.org/Exokernel](http://wiki.osdev.org/Exokernel)

[https://pdos.csail.mit.edu/archive/exo/theses/index.html](https://pdos.csail.mit.edu/archive/exo/theses/index.html)

[https://pdos.csail.mit.edu/archive/exo/exo-slides/sld001.htm](https://pdos.csail.mit.edu/archive/exo/exo-slides/sld001.htm)
[Recommended read](https://www.openu.ac.il/home/wiseman/2os/microkernels/exokernel.pdf)
