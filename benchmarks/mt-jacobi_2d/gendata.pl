#!/usr/bin/perl -w
#==========================================================================
# matmul_gendata.pl
#
# Author : Christopher Batten (cbatten@mit.edu)
# Date   : April 29, 2005
#
(our $usageMsg = <<'ENDMSG') =~ s/^\#//gm;
#
# Simple script which creates an input data set and the reference data
# for the matmul benchmark.
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
  print " Usage: matmul_gendata.pl [options] \n";
  print "\n";
  print " Options:\n";
  print "  --help  print this message\n";
  print "  --size  size of input data [1000]\n";
  print "  --seed  random seed [1]\n";
  print "  --Dtype Data type [int] , float, double\n";
  print "$usageMsg";

  exit();
}

sub processCommandLine()
{

  $opts{"help"} = 0;
  $opts{"size"} = 1000;
  $opts{"seed"} = 1;
  $opts{"Dtype"} = "double";
  Getopt::Long::GetOptions( \%opts, 'help|?', 'size:i', 'seed:i', 'Dtype:s' ) or usage();
  $opts{"help"} and usage();
  my @types=('double','int','float');
  unless ( grep( /^$opts{Dtype}$/, @types ) ) {
     print "Error: $opts{Dtype} is an unsupported data type. Valid values are @types\n";
     exit ();
  } 

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

  print "static data_t ".$arrayName."[ARRAY_SIZE] __attribute__((aligned (1024))) = \n";
  print "{\n";

  if ( $arrayLen <= $numCols ) {
    print "  ";
    for ( my $i = 0; $i < $arrayLen; $i++ ) {
      print sprintf("%f",$arrayRef->[$i]);
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
        print sprintf("%f",$arrayRef->[$index]);
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
        print sprintf("%3f",$arrayRef->[$index]);
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
# Matmul
#--------------------------------------------------------------------------

# http://answers.oreilly.com/topic/418-how-to-multiply-matrices-in-perl/

sub jacobi_2d {
    my ($m1,$m2) = @_;
    my ($i, $j) = 1;
  
    for ( my $i = 1; $i < $opts{"size"}-1; $i++ ) {
        for ( my $j = 1; $j < $opts{"size"}-1; $j++ ) {
            $m2->[$i][$j] = (0.2) * ($m1->[$i][$j] + $m1->[$i][$j-1] + $m1->[$i][1+$j] + $m1->[1+$i][$j] + $m1->[$i-1][$j]);
        }
    }
    return $m2;
}

sub range { 0 .. ($_[0] - 1) }


sub veclen {
    my $ary_ref = $_[0];
    my $type = ref $ary_ref;
    if ($type ne "ARRAY") { die "$type is bad array ref for $ary_ref" }
    return scalar(@$ary_ref);
}

sub matdim {
    my $matrix = $_[0];
    my $rows = veclen($matrix);
    my $cols = veclen($matrix->[0]);
    return ($rows, $cols);
}

#--------------------------------------------------------------------------
# Main
#--------------------------------------------------------------------------

sub main()
{

  processCommandLine();

  # create random input arrays
  my $mat_values1;
  my $mat_values1_tmp;
  my $mat_values2;
  my $mat_values2_tmp;
  for ( my $i = 0; $i < $opts{"size"}; $i++ ) {
    for ( my $j = 0; $j < $opts{"size"}; $j++ ) {
      $mat_values1->[$i][$j]     = ($i*($j+2) + 2) / $opts{"size"} ;
      $mat_values1_tmp->[$i][$j] = ($i*($j+2) + 2) / $opts{"size"} ;
      $mat_values2->[$i][$j]     = ($i*($j+3) + 3) / $opts{"size"} ;
      $mat_values2_tmp->[$i][$j] = ($i*($j+3) + 3) / $opts{"size"} ;
    }
  }

  # perform matmul
  my $m2_results = jacobi_2d($mat_values1_tmp, $mat_values2_tmp);
  my $m1_results = jacobi_2d($m2_results,$mat_values1_tmp);
  
  # translate 2d arrays to 1d-somethings (I don't know how to code in perl - Chris)
  my @values1;
  my @values2;
  my @results1;
  my @results2;
  for ( my $i = 0; $i < $opts{"size"}; $i++ ) {
    for ( my $j = 0; $j < $opts{"size"}; $j++ ) {
    my $value1 = $mat_values1->[$i][$j];
    my $value2 = $mat_values2->[$i][$j];
    my $result1 = $m1_results->[$i][$j];
    my $result2 = $m2_results->[$i][$j];
    push( @values1, $value1 );
    push( @values2, $value2 );
    push( @results1, $result1 );
    push( @results2, $result2 );
    }
  }

  print "\n#ifndef __DATASET_H";
  print "\n#define __DATASET_H";
  print "\n\#define ARRAY_SIZE ".($opts{"size"}*$opts{"size"})." \n\n";
  print "\n\#define DIM_SIZE ".$opts{"size"}." \n\n";
  
  print "\n\#define DATA_TYPE\n"; 
  print "typedef $opts{Dtype} data_t;\n";
    
   
  printArray( "input1_data", \@values1 );
  printArray( "input2_data", \@values2 );
  printArray( "verify_data1", \@results1);
  printArray( "verify_data2", \@results2);

  print "\n#endif //__DATASET_H";
 
}

main();

