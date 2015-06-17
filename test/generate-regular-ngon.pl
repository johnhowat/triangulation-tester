#!/usr/bin/perl

use strict;

my $radius = 100;
my $pi = 4*atan2(1,1);

my $n = shift;
my $file = shift;

open(OUTPUT, ">$file") || die("Couldn't create $file: $!\n");
for(my $i = 0; $i < $n; $i++) {
	my $x = sprintf("%.10f", $radius * cos(2 * $pi * $i / $n));
	my $y = sprintf("%.10f", $radius * sin(2 * $pi * $i / $n));
	print OUTPUT "$x $y\n";
}
close(OUTPUT);
