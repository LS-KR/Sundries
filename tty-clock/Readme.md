
## tty-clock

Show a clock in your tty.  
```
usage: tty-clock [-hsc1Sb] [-C Color] [-t ticks] [-a nsticks]
    -h         show this page
    -s         show second
    -c         center the clock when start
    -1         show once
    -C Color   change color: 0~F or RGB color
    -S         screen saver mode
    -t ticks   set the delay between refresh (default:1000 ms)
    -a nsticks set the delay between refresh (microsecond, add to -t ticks)
    -b         enable blinking

keyboard shortcuts:
    Q: quit tty-clock
    C: center the clock
    M: Locate the clock at topleft
    S: show/unshow the second
    E: Change color
```