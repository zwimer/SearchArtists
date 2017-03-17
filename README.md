# Search Artists

This is a handy little tool that will allow you to search Apple for your favorite artist's media.

## Disclaimer

This application preforms only minor error checking and relies on multiple external libraries. While the application itself should be free of leaks, I cannot guarantee the same for the external libraries; nor can I guarantee that they function properly on every operating system.

## Requirements

This application requires a C++14 compiler, json.hpp (included), and libcurl.

## Installation Instructions

First clone this repository
```bash
git clone https://github.com/zwimer/SearchArtists
```

Next make a build directory and cd into it
```bash
mkdir SearchArtists/build && SearchArtists/build 
```

Then run qmake followed by make
```bash
qmake ../Eaton.pro && make
```

## Usage

This application takes no command like arguments.
