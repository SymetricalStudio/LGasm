# LGasm
 LGasm - assembly-like launguage for developing games

# Usage
Run LGasm script:
```
lgasm some_script.lgs
```

# How to Code
Window:
```
at LGASM

.start
wt Example
:

.update
dly 60
cls BLACK
:
```

Drawing Pixels:
```
at LGASM

.start
wt Example
:

.update
dly 60
cls BLACK
spx 30 30 WHITE
:
```

Simple Movement:
```
at LGASM

.start
wt Example
nmbr x 30
nmbr y 30
onkey w adn y -1
onkey a adn x -1
onkey s adn y 1
onkey d adn x 1
:

.update
dly 60
cls BLACK
spx 30 30 WHITE
:
```

# Compile
At first, compile a LGasmGraphics (it uses SDL2 to make some stuff upper)
```
make graphics
```

And after that, compile interpretator
```
make compiler
```

And that's it ready!
