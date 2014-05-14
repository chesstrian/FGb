# FGb Library

This work is based on Jean-Charles Faugère library for getting Gröbner Bases

Library is [here](http://www-polsys.lip6.fr/~jcf/Software/FGb/C%20API/index.html).

For compiling this:

```
apt-get install libgmp-dev
make
make test
```

For using this:

```
./main f n q display step block
```

Where:

* `f` is filename with polinomials.
* `n` is the number of variables, variables look like `x[i]`.
* `q` is a prime number for Gröbner Field.

Other values are for FGb library.

## Recommended Reading

* [Daniel Cabarcas Thesis](https://etd.ohiolink.edu/ap/10?0::NO:10:P10_ACCESSION_NUM:ucin1277120935)
* [FGb Paper](http://www-salsa.lip6.fr/~jcf/Papers/ICMS.pdf)
* [Ideals, Varieties and Algorithms](http://www.math.ku.dk/~holm/download/ideals-varieties-and-algorithms.pdf)
