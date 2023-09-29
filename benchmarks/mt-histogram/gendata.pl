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
# for the histogram benchmark.
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
  print "  --Dtype Data type [char] , int\n";
  print "  --dev   [16] input data are randomly selected between 0 & size/dev value\n";
  print "$usageMsg";

  exit();
}

sub processCommandLine()
{

  $opts{"help"} = 0;
  $opts{"size"} = 1024;
  $opts{"seed"} = 1;
  $opts{"Dtype"} = "char";
  $opts{"dev"} = 16;
  Getopt::Long::GetOptions( \%opts, 'help|?', 'size:i', 'seed:i', 'Dtype:s' , 'dev:i') or usage();
  $opts{"help"} and usage();
  
  my @types=('char','int');
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
  my $arraysize = $_[2];
  my $Dtype = $_[3];
 
  my $numCols = 20;
  my $arrayLen = scalar(@{$arrayRef});

  print  "static $Dtype ".$arrayName."[$arraysize] __attribute__((aligned (1024))) = \n";
  print  "{\n";

  if ( $arrayLen <= $numCols ) {
    print  "  ";
    for ( my $i = 0; $i < $arrayLen; $i++ ) {
      print  sprintf("%g",$arrayRef->[$i]);
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
        print  sprintf("%g",$arrayRef->[$index]);
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
        print  sprintf("%g",$arrayRef->[$index]);
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
#	 histogram
#------------------------------------------------------------------------


sub histogram {
	my ( $x, $N,$M) =@_;
	my $r;
	for (my $i=0; $i < $M; $i++) {
	 	$r->[$i] =0;
	}
	for (my $i=0; $i < $N; $i++) {
	         $r->[$x->[$i]] ++;            
    }
     return $r;
}





#--------------------------------------------------------------------------
# Main
#--------------------------------------------------------------------------

sub main()
{

  processCommandLine();
  my $max = int($opts{"size"}/$opts{"dev"}); 
  
  srand($opts{"seed"});
  

  my @X;
  my @R;
  my @Y;

  # create random input arrays
  my $x;
  my $y;
  for ( my $i = 0; $i < $opts{"size"}; $i++ ) {   
      $x->[$i] = int(rand($max));     
      push( @X, $x->[$i] );   
  }
	
  
   my $r = histogram ($x, $opts{"size"},$max);


 for ( my $i = 0; $i < $max; $i++ ) {      
      push( @R, $r->[$i] );
  }

  for ( my $i = 0; $i < $max; $i++ ) {      
      push( @Y, 0 );
  }

  print  "\n#ifndef __DATASET_H";
  print  "\n#define __DATASET_H";
  print  "\n\#define ARRAY_SIZE ".($opts{"size"})." \n";
  print  "\n\#define HISTOGRAM_SIZE ".($max)." \n";
  print  "\n\#define DATA_TYPE\n";  
  print  "\ntypedef $opts{Dtype} data_t;\n";


  printArray( "input_data", \@X, $opts{"size"},"data_t"); 
  printArray( "result_data", \@Y, $max ,"unsigned int" );
  printArray( "verify_data", \@R, $max ,"unsigned int" );

  print  "\n#endif //__DATASET_H";
 
}

main();

