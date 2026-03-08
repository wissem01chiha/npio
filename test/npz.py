#!/usr/bin/env python

import numpy as np

print(np.__version__)

a = np.arange(6, dtype=np.int8).reshape(1, 2, 3)

np.save('np_save', a)