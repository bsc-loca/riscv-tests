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
  print "  --Dtype Data type [uint32_t], uint64_t \n";
  print "  --dev   [16] input data are randomly selected between 0 & size/dev value\n";
  print "$usageMsg";

  exit();
}

sub processCommandLine()
{

  $opts{"help"} = 0;
  $opts{"size"} = 1024;
  $opts{"seed"} = 1;
  $opts{"Dtype"} = "uint32_t";
  $opts{"dev"} = 16;
  Getopt::Long::GetOptions( \%opts, 'help|?', 'size:i', 'seed:i', 'Dtype:s' , 'dev:i') or usage();
  $opts{"help"} and usage();
  
  my @types=('uint32_t','uint64_t');
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

  print  "static $Dtype ".$arrayName."[$arraysize] = \n";
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

  print  "#ifndef __DATASET_H\n";
  print  "#define __DATASET_H\n\n";
  print  "#define ARRAY_SIZE ".($opts{"size"})." \n";
  print  "#define HISTOGRAM_SIZE ".($max)." \n\n";
  print  "#define DATA_TYPE\n";  
  print  "typedef $opts{Dtype} data_t;\n\n";


  printArray( "input_data", \@X, $opts{"size"},"data_t"); 
  printArray( "verify_data", \@R, $max ,"data_t" );

  print "static data_t result_data[HISTOGRAM_SIZE] = {0}; \n\n";
  
  print  "#endif //__DATASET_H \n";
 
}

main();

