#!/usr/bin/perl

my $dim = $ARGV[0];

unless(defined($dim) && ($dim > 0 && $dim < 100)){
    die "usage  maptool <row/column size>";
}

my @tiles;

map { $_ = 7; } @tiles;


my $mid_point = $dim / 2;

my $total_size = $dim * $dim;

my $mid_row = $total_size / 2;
for my $num (1..$total_size){
    if (($num % $mid_point) == 0 ){
        $tiles[$num] = 9;
    }
    if (($num / $dim) == $mid_point){
        $tiles[$num] = 8;
    }
}

map { print $_ . "\n"; } @tiles;
