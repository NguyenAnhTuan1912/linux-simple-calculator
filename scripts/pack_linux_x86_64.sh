#!/bin/bash

tar -cf bin/tunacalc_linux_x86_64.tar bin/install bin/tunacalc
gzip --best bin/tunacalc_linux_x86_64.tar

# Test again
tar -tvf bin/tunacalc_linux_x86_64.tar.gz