thesis
======

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

