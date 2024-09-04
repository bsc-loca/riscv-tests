#!/usr/bin/perl -w
#==========================================================================
# gendata.pl
#
# Author : Christopher Batten (cbatten@mit.edu)
# Date   : April 29, 2005
#
(our $usageMsg = <<'ENDMSG') =~ s/^\#//gm;
#
# Simple script which creates an input data set and the reference data
# for the mt-stream-copy benchmark.
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
  print " Usage: gendata.pl [options] \n";
  print "\n";
  print " Options:\n";
  print "  --help  print this message\n";
  print "  --size  size of input data [1000]\n";
  print "  --seed  random seed [1]\n";
  print "  --Dtype Data type [double] , float, int, long\n";
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
  
  my @types=('double','int','float','long');
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

  print  "static data_t ".$arrayName."[ARRAY_SIZE] = \n";
  print  "{\n";

  if ( $arrayLen <= $numCols ) {
    print  "  ";
    for ( my $i = 0; $i < $arrayLen; $i++ ) {
      print  sprintf("%3d",$arrayRef->[$i]);
      if ( $i != $arrayLen-1 ) {
        print  ", ";
      }
    }
    print  "\n";
  }

  else {
    my $numRows = int($arrayLen/$numCols);
    for ( my $j = 0; $j < $numRows; $j++ ) {
      print  "  ";
      for ( my $i = 0; $i < $numCols; $i++ ) {
        my $index = $j*$numCols + $i;
        print  sprintf("%3d",$arrayRef->[$index]);
        if ( $index != $arrayLen-1 ) {
          print  ", ";
        }
      }
      print  "\n";
    }

    if ( $arrayLen > ($numRows*$numCols) ) {
      print  "  ";
      for ( my $i = 0; $i < ($arrayLen-($numRows*$numCols)); $i++ ) {
        my $index = $numCols*$numRows + $i;
        print  sprintf("%3d",$arrayRef->[$index]);
        if ( $index != $arrayLen-1 ) {
          print  ", ";
        }
      }
      print  "\n";
    }

  }

  print   "};\n\n";
}




#------------------------------------------------------------------------
#	Axpy
#------------------------------------------------------------------------


sub stream_copy_block {
	my ( $x, $y , $N) =@_;
	my $r;
	for (my $i=0; $i < $N; $i++) {
	         $r->[$i] = $y->[$i];
           #  $r->[$i] += $alpha * $y->[$i];
     }
     return $r;
}





#--------------------------------------------------------------------------
# Main
#--------------------------------------------------------------------------

sub main()
{
  
  my $in_max =500; #should be int
  processCommandLine();
  srand($opts{"seed"});

  my @X;
  my @Y;
  my @Z;
  my @R;

  # create random input arrays
  my $x;
  my $y;
  my $z;
  
  for ( my $i = 0; $i < $opts{"size"}; $i++ ) {   
      $x->[$i] = int(rand((1<<31)-1));
      $y->[$i] = int(rand((1<<31)-1));  
      $z->[$i] = int(rand((1<<31)-1));  
      push( @X, $x->[$i] );
      push( @Y, $y->[$i] ); 
      push( @Z, $z->[$i] );   
  }
	
  
   my $r = stream_copy_block ($x, $y , $opts{"size"});


 for ( my $i = 0; $i < $opts{"size"}; $i++ ) {      
      push( @R, $r->[$i] );
  }

  print  "#ifndef __DATASET_H \n";
  print  "#define __DATASET_H \n\n";
  
  print  "#define ARRAY_SIZE ".($opts{"size"})." \n\n";
 
  print  "#define DATA_TYPE\n";  
  print  "typedef $opts{Dtype} data_t;\n\n";


  printArray( "input1_data", \@X );
  printArray( "input2_data", \@Y );
  printArray( "verify_data", \@R);

  print  "#endif //__DATASET_H \n";
 
}

main();

