

![Exoberry](https://i.ibb.co/vwP0vY0/Exoberry.png)

![Discord Channel](https://avatars3.githubusercontent.com/u/1965106?s=16&v=4) [Discord Chat Channel](https://discord.gg/adkVsMFW)


# What is Exoberry?
Exoberry is an exokernel written for the Raspberry Pi 3. 
# How to Install
To install Exoberry you will need

- Raspbery Pi 3 Model B
- USB to TTL serial cable
- SD card with installed Raspbian OS (2017 Version)
- The Exoberry image either built from source or downloaded from releases.

1. Copy `kernel8.img` file to the `boot` partition of your Raspberry Pi flash card and delete the other `kernel*.img` files on your SD card. 

2. Put the following lines in config.txt 

   ```bash
   kernel_old=1
   disable_commandline_tags=1
   ```

3. Connect the USB-to-TTL serial cable

4. Power on your Raspberry Pi

# Contributing
We are always looking for more people to help with coding, spreading the word, or simply just hanging out on [the chat](https://discord.gg/adkVsMFW).

This is just a fun project. If you have any cool idea, just submit an issue. 

# Building from Source
```bash
git clone https://github.com/MutexUnlocked/exoberry.git
cd exoberry
make
```

You should now see the kernel image in your current directory.

# Credits

- [raspberry-pi-os](https://github.com/s-matyukevich/raspberry-pi-os) devs

