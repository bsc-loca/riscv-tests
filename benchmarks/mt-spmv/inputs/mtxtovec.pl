#!/usr/bin/perl -w

(our $usageMsg = <<'ENDMSG') =~ s/^\#//gm;
#
# Simple script that translates a Sparse Matrix (*.mtx) to CSR format.
#
ENDMSG

use strict;
use warnings;
use Getopt::Long;

our %opts;

sub usage()
{

  print "\n";
  print " Usage: mtxtovec.pl [options] \n";
  print "\n";
  print " Options:\n";
  print "  --help  print this message\n";
  print "  --seed  random seed [1]\n";
  print "  --Dtype Data type [double] , float, int, long\n";
  print "  --file  file name (*.mtx) [nv1] \n";
  print "$usageMsg";

  exit();
}

sub processCommandLine()
{
  $opts{"help"}  = 0;
  $opts{"seed"}  = 1;
  $opts{"Dtype"} = "double";
  $opts{"file"}  = "nv1";
  Getopt::Long::GetOptions( \%opts, 'help|?', 'seed:i', 'Dtype:s', 'file:s' ) or usage();
  $opts{"help"} and usage();

  my @types=('double','int','float', 'long');
  unless ( grep( /^$opts{Dtype}$/, @types ) ) {
     print "Error: $opts{Dtype} is an unsupported data type. Valid values are @types\n";
     exit ();
  } 

}

#********************************************************
#********************************************************

sub printArray
{
  my $arrayName = $_[0];
  my $arrayRef  = $_[1];
  my $arraySize = $_[2];
  my $ndec      = $_[3]; #number of decimals
  my $data_t    = $_[4] ? $_[4] : "data_t" ;

  my $numCols = 20;
  my $arrayLen = scalar(@{$arrayRef});

  print "static ".$data_t." ".$arrayName."[".$arraySize."] = \n";
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
#------------------------------------------------------------
sub spmv{
    my($ptr,$col,$val,$x,$nrow) = @_;
    my @y;

    for (my $row = 0; $row < $nrow; $row++) {
        my $sum = 0;
        for (my $idx = $ptr->[$row]; $idx < $ptr->[$row+1]; $idx++) {
            $sum += $val->[$idx] * $x->[$col->[$idx]];
        }
        push(@y,$sum);
    }
    return @y
}

#***************************************************
# MAIN
#***************************************************

sub main()
{
    processCommandLine();
    srand($opts{"seed"});
    
    #-------------------------------------------------------------------------------
    my $filename = $opts{"file"}.".mtx";

    open(my $fh, '<', $filename) or die "Couldn't open file '$filename': $!";
    my ($rows, $cols, $nnz);
    my @ROW;
    my @COL;
    my @VAL;

    while (<$fh>) {
        next if /^%/;  # Skip comments
        if (/^(\d+)\s+(\d+)\s+(\d+)/) {
            ($cols, $rows, $nnz) = ($1, $2, $3);
            last;
        }
    }

    while (<$fh>) {
        my ($col, $row, $val) = split;
        push @COL, $col;
        push @ROW, $row;
        #push @VAL, $val * 10000000000000000;
        #push @VAL, $val ;
        if ($val > 0) { # positive
            #push @VAL,($opts{Dtype} eq 'double' || $opts{Dtype} eq 'float') ? (int(rand(999)) + 1) + ((int(rand(999)) + 1)/1000) : int(rand(999)) + 1;
            push @VAL, int(rand(999)) + 1
        } elsif ($val < 0) { #negative
            #push @VAL,($opts{Dtype} eq 'double' || $opts{Dtype} eq 'float') ? -((int(rand(999)) + 1) + ((int(rand(999)) + 1)/1000)) : -(int(rand(999)) + 1);
            push @VAL, -(int(rand(999)) + 1)
        } else { #zero
            push @VAL, 0 ;
        }
    }

    close($fh);
    
    #-------------------------------------------------------------------------------
    # get pointers
    my @PTR; 
    my $curr_row = 0;
    for(my $entry = 0; $entry < $nnz; $entry++)
    {
        my $idx_row = $ROW[$entry];
        if($idx_row == $curr_row+1)
        {
            $curr_row++;
            push @PTR, $entry;
        }
    }
    push @PTR, $nnz; 
    
    #-------------------------------------------------------------------------------
    # random numbers
    my @X;
    for (my $i = 0; $i < $cols+1; $i++)
    {
        push @X, int(rand(255)) + 1;
    }
    
    #-------------------------------------------------------------------------------
    my @REF = spmv(\@PTR, \@COL, \@VAL, \@X, $rows); 
  
    my $dtype_size = ($opts{Dtype} eq 'double' || $opts{Dtype} eq 'long') ? 8 : 4 ;  
    my $dat_size = (((($rows+1)*$dtype_size) + (($nnz*2)*$dtype_size) + ($cols*$dtype_size) + ($rows*$dtype_size)) / 1024) / 1024;
    print sprintf ("\/\/ data size: %0.1f MB\n",$dat_size);
    
    my $r_size = $rows+1;
    my $c_size = $cols+1;
   
    my $idata_t  = ($opts{Dtype} eq 'double' || $opts{Dtype} eq 'long')  ? 'uint64_t' : 'uint32_t';
    #my $dec_size = ($opts{Dtype} eq 'double' || $opts{Dtype} eq 'float') ? '5' : '0';
    my $dec_size = '0';

    #Display header file
    print  "#ifndef __DATASET_H \n";
    print  "#define __DATASET_H\n\n";
    
    print  "#define NROW ".$r_size." \n";
    print  "#define NCOL ".$c_size." \n";
    print  "#define NNZ " .$nnz." \n\n";
    
    print  "#define DATA_TYPE \n";
    print  "typedef ".$opts{Dtype}." data_t;\n\n";
    
    printArray("ptr", \@PTR, "NROW+1", "0", $idata_t);
    printArray("col", \@COL, "NNZ"   , "0", $idata_t);
    printArray("val", \@VAL, "NNZ"   , $dec_size );
    printArray("x"  , \@X  , "NCOL"  , "0" );
    printArray("ref", \@REF, "NROW"  , $dec_size );
    #printArray("y"  , \@Y  , "NROW"  , "0" );

    print "static data_t y[NROW] = {0}; \n\n";
    
    print "#endif //__DATASET_H\n";

    print STDERR sprintf ("Generated data size: %0.1f MB\n",$dat_size),
}

main();
