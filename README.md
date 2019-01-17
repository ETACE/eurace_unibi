# The Eurace@Unibi Model

This is the source code of the Eurace@Unibi Model.

# Current version: 

1.0.1 (April 2016)

# Pre-installed version

There is a virtual appliance with everything pre-compiled (all FLAME dependencies, the included model is at v1.0):

Download link:
https://gregorboehl.com/live/etace-v.0.997.1.ova

Documentation:
http://www.wiwi.uni-bielefeld.de/lehrbereiche/vwl/etace/Eurace_Unibi/Virtual_Appliance

# Installation

## 1. Prepare system requirements

Make sure to have `cunit` and `gsl` installed.
- On Debian-based systems: `sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev libgsl-dev`.
- On macOS: `brew install cunit gsl`.
- On Windows (TODO: test on appveyor): `TODO`.

## 2. Install libmboard

On top of the repo root directory, download libmboard master version
(https://github.com/FLAME-HPC/libmboard/archive/master.zip has more
bugfixes since 0.3.1) and unzip it

```bash
mkdir libmboard
cd libmboard-master
./autogen.sh
# Remove --disable-parallel if you have mpi installed
./configure --prefix=$(cd ../libmboard; pwd) --disable-parallel
make
make install
cd .. # back to the repo root directory
```

## 3. Install xparser and generate makefile for the model

Download xparser 0.17.1 (https://github.com/FLAME-HPC/xparser/archive/0.17.1.tar.gz) and
extract to xparser/ directory on top of the repo root directory.
```bash
cd xparser
make
./xparser ../eurace_model.xml
cd ..
```

## 4. Build the model

Be sure to replace LIBMBOARD_DIR in Makefile from `/usr/local` to
`$(PWD)/libmboard`.
Finally, run `make`, which should compile everything if the previous steps are
executed correctly.

## Further Links:

1. [http://www.wiwi.uni-bielefeld.de/lehrbereiche/vwl/etace/Eurace_Unibi/](http://www.wiwi.uni-bielefeld.de/lehrbereiche/vwl/etace/Eurace_Unibi/)
2. [https://pub.uni-bielefeld.de/data/2900767](https://pub.uni-bielefeld.de/data/2900767)
3. [http://www.flame.ac.uk](http://www.flame.ac.uk)


Contributing
------------

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Added some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

Copyright
---------

Copyright (c) 2014-2019 Herbert Dawid, Simon Gemkow, Philipp Harting, Sander van der Hoog, Michael Neugart. See LICENSE for further details.
