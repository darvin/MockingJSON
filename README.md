[![Build Status](https://travis-ci.org/darvin/MockingJSON.svg?branch=master)](https://travis-ci.org/darvin/MockingJSON) [![Gitter](https://badges.gitter.im/Join Chat.svg)](https://gitter.im/darvin/MockingJSON?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)


#MockingJSON


Tiny [Scheme](http://en.wikipedia.org/wiki/Scheme_(programming_language))/[Lisp](http://en.wikipedia.org/wiki/Lisp_(programming_language)) dialect, subset of [JSON](http://en.wikipedia.org/wiki/JSON)

## Examples

```json
["+", 2, 4]
```
    
returns `6`

```json
["begin",
    ["define", ["fib", "n"],
      ["if", ["=", "n", 1],
          0,
          ["if", ["=", "n", 2],
              1
              ["+", ["fib", ["-", "n", 1]] ["fib", ["-", "n", 2]]]]]],
    ["fib", 13]]
```

returns `233`

```json
["begin", 
    ["write", "Hello World!"],
    ["newline"]]
```

prints `Hello World!\n`


## ***

*Our hearts burn for [Mike Brown](http://en.wikipedia.org/wiki/Shooting_of_Michael_Brown) and for every victim of [racism](http://en.wikipedia.org/wiki/Black_genocide) and [police brutality](http://en.wikipedia.org/wiki/Police_brutality#Russia) around the globe. No forgiveness!*
