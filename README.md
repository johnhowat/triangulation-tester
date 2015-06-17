# triangulation-tester

An implementation of several methods of polygon triangulation. Outputs a PNG file that shows the triangulation, as well as some statistics about it.

## Requirements

This project is stord as a Qt project, but the code can also be compiled by hand.

You will need the [PNGWriter Library](http://pngwriter.sourceforge.net/).

## Usage

    $ ./triangulate ../test/big.txt
    
The specified file should consist of the points in the polygon (in the order they appear on the boundary): one per line, with each coordinate separated by a space.

For testing purposes, you can run

    $ test/generate-regular-ngon.pl 10 10-gon.txt

To generate a regular 10-sided polygon. The first parameter is the number of sides, and the second parameter is the name of the output file.
