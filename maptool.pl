#!/usr/bin/perl

use strict;
use warnings;

my $dim = $ARGV[0];

unless(defined($dim) && ($dim > 0 && $dim < 100)){
    die "usage  maptool <row/column size>";
}

my @tiles;

my $mid_point = $dim / 2;

my $total_size = $dim * $dim;
my $mid_row = (($mid_point*$dim)+$mid_point);
#my $mid_row = $total_size / 2;
for my $num (0..$total_size-1){
    $tiles[$num] = 7;
    if (($num % $dim) == $mid_point){
        if($num == $mid_row){
            $tiles[$num] = 10;
        } else {
            $tiles[$num] = 9;
        }
    #} elsif (abs($num -$mid_row) < $mid_point ){
    #    print "num / dim = ".($num/$dim)."\n";
    } elsif (int($num /$dim) == $mid_point){
        #unless(($num / $dim)==$mid_row){
            unless($tiles[$num] == 10){
                $tiles[$num] = 8;
            }
        #}
    }
}

map { print $_ . "\n" if defined $_; } @tiles;
