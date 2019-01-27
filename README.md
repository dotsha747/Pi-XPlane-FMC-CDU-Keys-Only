# Pi-XPlane-FMC-CDU-Keys-Only

I was asked if I could add support for the standard X-Plane 737 FMC
(not the Zibo mod). 

There are a couple of issues with this, the main one being that the
standard X-Plane 737 FMC doesn't export datarefs containing the 
contents of the screen. So there would be no way to replicate the
display of the FMC on the Pi's HDMI output. There are only "commands"
to simulate pressing of the keys.

It was suggested to me that the "ExtTexture" plugin can be used
to replicate the image of the FMC for output onto separate computers.
So there is no need for the Pi to render the display in this case,
it just needs to trigger the key commands.

A complicating issue here is that in the Pi-Xplane-FMC, there is a
startup menu that connects to X-Plane and lets the user select 
which FMC software to interface with. If the Pi's HDMI output is
not connected to anything, it would be quite hard to select from
this screen.

After a bit of a re-think, I realised it was easier to bypass the
whole Pi-XPlane-FMC-CDU program and write up a new program. This
new one is a lot simpler, it just combines my libXPlane-UDP-Client
library with the keyboard scanning code from Pi-XPlane-FMC-CDU.
No display needed. Heck, we don't even need the ExtPlane plugin,
as libXPlane-UDP-Client is capable of sending commands to X-Plane
already!

BUILDING

I recommend just using the prebuilt binaries (see below), but if 
you want to build from source code, clone this repository to your 
Pi and execute:

make
make install


PREBUILD PACKAGE QUICK INSTALLATION

Prebuilt .deb binaries are available for raspbian "Stretch".

You can skip the following steps if you've already installed 
Pi-XPlane-FMC-CDU on your pi:

- Install the repository public key:
  - wget -O- http://repo.shahada.abubakar.net/pubkey.asc | sudo apt-key add -
	  
- Add the APT source:
  - cd /etc/apt/sources.list.d
  - sudo wget http://repo.shahada.abubakar.net/repo.shahada.abubakar.net.sources.list

To install the Pi-XPlane-FMC-CDU-Keys-Only program:

- Install the binaries:

  - sudo apt-get update
  - sudo apt-get install pi-xplane-fmc-cdu-keys-only

Note that you can only start either Pi-XPlane-FMC-CDU OR
Pi-XPlane-FMC-CDU-Keys-Only automatically. You can control which
is enabled or disabled using systemctl:

  - sudo systemctl disable piXPlaneFMCCDU
  - sudo systemctl enable piXPlaneFMCCDUKeysOnly

or

  - sudo systemctl enable piXPlaneFMCCDU
  - sudo systemctl disable piXPlaneFMCCDUKeysOnly
