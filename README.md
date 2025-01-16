## analyze core file 

```
gdb bin/test_darray core

# Show where the crash occurred
(gdb) bt

# Move to the relevant frame (if needed)
(gdb) frame n    # where n is the frame number

# Print variable values
(gdb) print array
(gdb) print i

# Examine memory
(gdb) x/10x array
```