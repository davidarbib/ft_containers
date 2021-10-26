#!/bin/sh
rm current_fix
make current_fix FT=1
./current_fix > ft
rm current_fix
make current_fix
./current_fix > std
diff std ft
