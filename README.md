# The Eurace@Unibi Model

This is the source code of the Eurace@Unibi Model.

**Version history:**

1.0.0 (April 2014)

1.0.1 (April 2016)

**Dependencies**

GCC 4.4 or higher (or other C compiler)

GSL 2.4 or higher (GNU  Scientific  Library)

FLAME XParser 0.17.1 (https://github.com/FLAME-HPC/xparser/archive/0.17.1.tar.gz)

FLAME Libmboard 0.3.1 (https://github.com/FLAME-HPC/libmboard/archive/0.3.1.zip)


# Pre-installed FLAME libraries and model source code

There is a virtual appliance with everything pre-compiled: the FLAME components XParser and Libmboard, and the model source code (currently v1.0).

Dependency: Oracle VirtualBox (https://www.virtualbox.org/), or any other virtualization client for ova files.

Download link:
https://gregorboehl.com/live/etace-v.0.997.1.ova

Documentation:
http://www.wiwi.uni-bielefeld.de/lehrbereiche/vwl/etace/Eurace_Unibi/Virtual_Appliance

# Installation of FLAME libraries on stand-alone systems and building the model

Step 2-4 (installation of FLAME libraries) can also be run via a script
`./scripts/install_flame.sh`.

## 1. Prepare system requirements

Make sure to have `cunit` and `gsl` installed.
- On Debian-based systems: `sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev libgsl-dev`.
- On macOS: `brew install cunit gsl`.
- On Windows (TODO: test on appveyor): `TODO`.

## 2. Install libmboard

On top of the repo root directory, download libmboard 0.3.1
(https://github.com/FLAME-HPC/libmboard/archive/0.3.1.tar.gz) and extract the tarball

```bash
mkdir libmboard
cd libmboard-0.3.1
chmod +x autogen.sh
./autogen.sh
# Remove --disable-parallel if you have mpi installed
./configure --prefix=$(cd ../libmboard; pwd) --disable-parallel
make
make install
# back to the repo root directory
cd ..
```

## 3. Install xparser

Download xparser 0.17.1 (https://github.com/FLAME-HPC/xparser/archive/0.17.1.tar.gz) and
extract to xparser/ directory on top of the repo root directory.
```bash
cd xparser
make
# back to the repo root directory
cd ..
```

## 4. Generate makefile for the model
```bash
cd xparser
./xparser ../eurace_model.xml
# back to the repo root directory
cd ..
```

## 5. Build the model

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

How to cite
--
Any publication that contains results derived from the Eurace@Unibi Soutrce Code must contain the following (or similar) acknowledgement:

This work uses (a modified version of) the Eurace@Unibi model source code, developed by Herbert Dawid, Simon Gemkow, Philipp Harting, Sander van der Hoog and Michael Neugart. More details on the Eurace@Unibi model can be found in these publications:

Dawid, H., Harting, P., van der Hoog, S., & Neugart, M. (2018a). Macroeconomics with heterogeneous agent models: Fostering transparency, reproducibility and replication. Journal of Evolutionary Economics. DOI:10.4119/unibi/2902981

Dawid, H., Gemkow, S., Harting, P., van der Hoog, S., & Neugart, M. (2018b). Agent-based macroeconomic modeling and policy analysis: The Eurace@Unibi Model. In S.-H. Chen, M. Kaboudan, & Y.-R. Du (Eds.), The Oxford Handbook of Computational Economics and Finance (Ch. 17, pp. 490–519). Oxford: Oxford University Press. Available online as Working Paper: urn:nbn:de:0070-pub-26224984

BiBTeX:

@INCOLLECTION{Dawid_2018,
	Author = {H. Dawid and S. Gemkow and P. Harting and S. van der Hoog and M. Neugart},
	Title = {{Agent-Based Macroeconomic Modeling and Policy Analysis: {The Eurace@Unibi} Model}},
	Editor = {Chen, S-H and Kaboudan M. and Du, Y.-R.},
	Booktitle = {The Oxford Handbook of Computational Economics and Finance},
	Publisher = {Oxford University Press},
	Year = {2018},
	Chapter = {17},
	Pages = {490-519},
}

@ARTICLE{Dawid_2019,
	author       = {Dawid, Herbert and Harting, Philipp and {van der Hoog}, Sander and Neugart, Michael},
	title        = {{A Heterogeneous Agent Macroeconomic Model for Policy Evaluation: Improving Transparency and Reproducibility}},
	year         = {2019},
	journal 	  = {Journal of Evolutionary Economics},
}


Copyright
---------

Copyright (c) 2014-2019 Herbert Dawid, Simon Gemkow, Philipp Harting, Sander van der Hoog, Michael Neugart.

License
--

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This software is licensed under the <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

Disclaimer
--

The package is provided by the owner and contributors "as is' and without any express or implied warranties. The implied warranties of merchantability, fitness for a particular purpose, or non-infringement are disclaimed to the extent permitted by your local law. unless required by law, no owner or contributor will be liable for any direct, indirect, incidental, or consequential damages arising in any way out of the use of the package, even if advised of the possibility of such damage.
