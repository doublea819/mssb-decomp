# Local patches to submodules

`port/extern/aurora` points at upstream aurora (bigmah/aurora), which this fork can't push to.
Our aurora changes are kept here as patches and on the local submodule branch `mssb-gameplay-fixes`.

Apply after a fresh clone / submodule update:

    git -C port/extern/aurora am ../../patches/aurora-mssb-gameplay-fixes.patch
