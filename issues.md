# Expected Issues

```bash
==15322== Syscall param writev(vector[0]) points to uninitialised byte(s)
==15322==    at 0x4BD1864: writev (writev.c:26)
==15322==    by 0x4CC6ACA: ??? (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==15322==    by 0x4CC6C4E: ??? (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==15322==    by 0x4CC7D7E: xcb_writev (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==15322==    by 0x48C10B8: _XSend (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==15322==    by 0x48C6148: _XReadEvents (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==15322==    by 0x48C652B: XWindowEvent (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==15322==    by 0x114945: mlx_int_wait_first_expose (in /home/carl-samaha/42/Milestone 4/Cube3D/cub3D)
==15322==    by 0x114675: mlx_new_window (in /home/carl-samaha/42/Milestone 4/Cube3D/cub3D)
==15322==    by 0x10FEE5: app_init (in /home/carl-samaha/42/Milestone 4/Cube3D/cub3D)
==15322==    by 0x10FBE9: main (in /home/carl-samaha/42/Milestone 4/Cube3D/cub3D)
==15322==  Address 0x4d26acc is 28 bytes inside a block of size 16,384 alloc'd
==15322==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==15322==    by 0x48B042D: XOpenDisplay (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==15322==    by 0x114426: mlx_init (in /home/carl-samaha/42/Milestone 4/Cube3D/cub3D)
==15322==    by 0x10FEA5: app_init (in /home/carl-samaha/42/Milestone 4/Cube3D/cub3D)
==15322==    by 0x10FBE9: main (in /home/carl-samaha/42/Milestone 4/Cube3D/cub3D)
==15322==  Uninitialised value was created by a stack allocation
==15322==    at 0x114850: mlx_int_anti_resize_win (in /home/carl-samaha/42/Milestone 4/Cube3D/cub3D)
```
