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
  print "  --Dtype Data type [float]\n";
  print "$usageMsg";

  exit();
}

sub processCommandLine()
{

  $opts{"help"} = 0;
  $opts{"size"} = 1000;
  $opts{"seed"} = 1;
  $opts{"Dtype"} = "float";
  Getopt::Long::GetOptions( \%opts, 'help|?', 'size:i', 'seed:i', 'Dtype:s' ) or usage();
  $opts{"help"} and usage();
  my @types=('float');
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
  my $ndec      = $_[2]; #number of decimals
  my $data_t    = $_[3] ? $_[3] : data_t ;

  my $numCols = 20;
  my $arrayLen = scalar(@{$arrayRef});

  print "static ".$data_t." ".$arrayName."[ARRAY_SIZE] __attribute__((aligned (1024))) = \n";
  print "{\n";

  if ( $arrayLen <= $numCols ) {
    print "  ";
    for ( my $i = 0; $i < $arrayLen; $i++ ) {
      print sprintf("%.".$ndec."f",$arrayRef->[$i]);
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
        print sprintf("%.".$ndec."f",$arrayRef->[$index]);
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
        print sprintf("%.".$ndec."f",$arrayRef->[$index]);
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



#--------------------------------------------------------------------------
# Main
#--------------------------------------------------------------------------

sub main()
{

    processCommandLine();

    #---------------------------------------------------------------
    # Open the file
    my $file = "optionData.txt";
    open(my $fh, '<', $file) or die "Couldn't open file '$file' $!";
                    
    my @s  ;
    my @k  ;
    my @r  ;
    my @v  ;
    my @t  ;
    my @pc ;
    my @dg ;
                    
    # Read the file line by line
    while (my $line = <$fh>) {
        while ($line =~ /\{(.*?)\}/g) {
            my $structure = $1;
            my @elements = split(',', $structure);
            push( @s , $elements[0] );
            push( @k , $elements[1] );
            push( @r , $elements[2] );
            push( @v , $elements[4] );
            push( @t , $elements[5] );
            push( @pc, $elements[6] =~ "P" ? 1 : 0 );
            push( @dg, $elements[8] );
        }
    }
            
    # Close the file
    close($fh);
    #---------------------------------------------------------------
    my $max = 1000;
    
    my @sptprice;
    my @strike;
    my @rate;
    my @volatility;
    my @otime;
    my @otype;
    my @DGrefval;
    my @result;

    for ( my $i = 0; $i < $opts{"size"}; $i++ ) {
        push( @sptprice  , $s  [$i % $max] );
        push( @strike    , $k  [$i % $max] );
        push( @rate      , $r  [$i % $max] );
        push( @volatility, $v  [$i % $max] );
        push( @otime     , $t  [$i % $max] );
        push( @otype     , $pc [$i % $max] );
        push( @DGrefval  , $dg [$i % $max] );
        push( @result    , 0               );
    }
    my $dat_size = (($opts{"size"}*4)*8)/1024;
    
    print "\/\/ data size: $dat_size KB\n";
    print "\n#ifndef __DATASET_H";
    print "\n#define __DATASET_H\n";
    print "\n\#define ARRAY_SIZE ".($opts{"size"})." \n";
    print "\#define NUM_RUNS   100 \n";
            
    print "\n\#define DATA_TYPE\n"; 
    print "typedef $opts{Dtype} data_t;\n\n";
    
    printArray( "otype"     , \@otype     , "0" , "int" );
    printArray( "sptprice"  , \@sptprice  , "2"  );
    printArray( "strike"    , \@strike    , "2"  );
    printArray( "rate"      , \@rate      , "4"  );
    printArray( "volatility", \@volatility, "2"  );
    printArray( "otime"     , \@otime     , "2"  );
    printArray( "DGrefval"  , \@DGrefval  , "18" );
    printArray( "priceDelta", \@result    , "0"  );

    print "\n#endif //__DATASET_H\n";

    print STDERR "Generated data size: $dat_size KB\n"
 
}

main();

