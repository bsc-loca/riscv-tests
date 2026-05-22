#!/usr/bin/perl -w
#==========================================================================
# vvadd_gendata.pl
#
# Author : Christopher Batten (cbatten@mit.edu)
# Date   : April 29, 2005
#
(our $usageMsg = <<'ENDMSG') =~ s/^\#//gm;
#
# Simple script which creates an input data set and the reference data
# for the vvadd benchmark.
#
ENDMSG

use strict "vars";
use warnings;
no  warnings("once");
use Getopt::Long;

#--------------------------------------------------------------------------
# Command line processing
#--------------------------------------------------------------------------

our %opts;

sub usage()
{

  print "\n";
  print " Usage: vvadd_gendata.pl [options] \n";
  print "\n";
  print " Options:\n";
  print "  --help  print this message\n";
  print "  --size  size of input data [1000]\n";
  print "  --seed  random seed [1]\n";
  print "$usageMsg";

  exit();
}

sub processCommandLine()
{

  $opts{"help"} = 0;
  $opts{"size"} = 1000;
  $opts{"seed"} = 1;
  Getopt::Long::GetOptions( \%opts, 'help|?', 'size:i', 'seed:i' ) or usage();
  $opts{"help"} and usage();

}

#--------------------------------------------------------------------------
# Helper Functions
#--------------------------------------------------------------------------

sub printArray
{
  my $arrayName = $_[0];
  my $arrayRef  = $_[1];

  my $numCols = 20;
  my $arrayLen = scalar(@{$arrayRef});

  print "int ".$arrayName."[DATA_SIZE] = \n";
  print "{\n";

  if ( $arrayLen <= $numCols ) {
    print "  ";
    for ( my $i = 0; $i < $arrayLen; $i++ ) {
      print sprintf("%3d",$arrayRef->[$i]);
      if ( $i != $arrayLen-1 ) {
        print ", ";
      }
    }
    print "\n";
  }

  else {
    my $numRows = int($arrayLen/$numCols);
    for ( my $j = 0; $j < $numRows; $j++ ) {
      print "  ";
      for ( my $i = 0; $i < $numCols; $i++ ) {
        my $index = $j*$numCols + $i;
        print sprintf("%3d",$arrayRef->[$index]);
        if ( $index != $arrayLen-1 ) {
          print ", ";
        }
      }
      print "\n";
    }

    if ( $arrayLen > ($numRows*$numCols) ) {
      print "  ";
      for ( my $i = 0; $i < ($arrayLen-($numRows*$numCols)); $i++ ) {
        my $index = $numCols*$numRows + $i;
        print sprintf("%3d",$arrayRef->[$index]);
        if ( $index != $arrayLen-1 ) {
          print ", ";
        }
      }
      print "\n";
    }

  }

  print  "};\n\n";
}

#--------------------------------------------------------------------------
# Main
#--------------------------------------------------------------------------

sub main()
{

  processCommandLine();
  srand($opts{"seed"});

  my @values1;
  my @values2;
  my @sum;
  for ( my $i = 0; $i < $opts{"size"}; $i++ ) {
    my $value1 = int(rand(16777216));
    push( @values1, $value1 );

    my $B = $value1 & 0xFF;              # Bits [7:0]
    my $G = ($value1 >> 8) & 0xFF;       # Bits [15:8]
    my $R = ($value1 >> 16) & 0xFF;      # Bits [23:16]

    # Perform RGB to YUV conversion
    my $Y = int(0.299 * $R + 0.587 * $G + 0.114 * $B) & 0xFF;
    my $U = int(0.492 * ($B - $Y)) & 0xFF;   # +128 for unsigned range if needed
    my $V = int(0.877 * ($R - $Y)) & 0xFF;   # +128 for unsigned range if needed

    # Pack YUV back into a 32-bit word
    my $YUV = ($Y << 16) | ($U << 8) | $V;

    push( @sum, $YUV );
  }


  print "\n\#define DATA_SIZE ".$opts{"size"}." \n\n";
  printArray( "input1_data", \@values1 );
  printArray( "verify_data", \@sum );

}

main();

