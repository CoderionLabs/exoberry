# DEOS

The digital exokernel operating system.

[![Build Status](https://travis-ci.org/friedrich12/DEOS.svg?branch=master)](https://travis-ci.org/friedrich12/DEOS)

![](/assets/import.png)

Graphic overview of an exokernel. Exokernels are much smaller than a normal kernels \(monolithic kernels\). They give more direct access to the hardware, thus removing most abstractions

**Motivation**

Traditionally kernel designers have sought to make individual hardware resources invisible to application programs by requiring the programs to interact with the hardware via some abstraction model. These models include file systems for disk storage, virtual address spaces for memory, [schedulers](https://en.wikipedia.org/wiki/Scheduling_%28computing%29) for task management, and [sockets](https://en.wikipedia.org/wiki/Berkeley_sockets) for network communication. These abstractions of the hardware make it easier to write programs in general, but limit performance and stifle experimentation in new abstractions. A security-oriented application might need a file system that does not leave old data on the disk, while a reliability-oriented application might need a file system that keeps such data for failure recovery.

One option is to remove the kernel completely and program directly to the hardware, but then the entire machine would be dedicated to the application being written \(and, conversely, the entire application codebase would be dedicated to that machine\). The exokernel concept is a compromise: let the kernel allocate the basic physical resources of the machine \(e.g. [disk](https://en.wikipedia.org/wiki/Computer_disk) blocks, [memory pages](https://en.wikipedia.org/wiki/Memory_page), and processor time\) to multiple application programs, and let each program decide what to do with these resources. The program can then link to a support library that implements the abstractions it needs \(or it can implement its own\).

For more see

[https://en.wikipedia.org/wiki/Exokernel](https://en.wikipedia.org/wiki/Exokernel) [ ](http://wiki.osdev.org/Exokernel)

[http://wiki.osdev.org/Exokernel](http://wiki.osdev.org/Exokernel)

[https://pdos.csail.mit.edu/archive/exo/theses/index.html](https://pdos.csail.mit.edu/archive/exo/theses/index.html)

[https://pdos.csail.mit.edu/archive/exo/exo-slides/sld001.htm](https://pdos.csail.mit.edu/archive/exo/exo-slides/sld001.htm)

**Contributing**

DEOS is a meritocratic open source project with a large variety of tasks. Even if you can't write code, you can still help! DEOS needs designers, \(technical\) writers, translators, testers... Get involved and help out! [Join the mailling list.](https://docs.google.com/forms/d/e/1FAIpQLSes4ibh1F-PTGdaPns6k446ODwOSNaju3DksLgOB_Zo-IMu_Q/viewform?usp=sf_link)

**Contributing code**

Right now there seems to be nothing to say about the project yet. Right now we need people to build the exokernel if you can submit any code to build the exokernel, please submit a pull request.

