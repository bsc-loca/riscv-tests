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
  print "  --file  file name (*.mtx) [nv1] \n";
  print "$usageMsg";

  exit();
}

sub processCommandLine()
{
  $opts{"help"} = 0;
  $opts{"seed"} = 1;
  $opts{"file"} = "nv1";
  Getopt::Long::GetOptions( \%opts, 'help|?', 'seed:i', 'file:s' ) or usage();
  $opts{"help"} and usage();
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

  print "static ".$data_t." ".$arrayName."[".$arraySize."] __attribute__((aligned (1024))) = \n";
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
        #push @VAL, $val * 1000000000000;
        push @VAL, $val ;
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
    my @Y;
    for (my $i = 0; $i < $cols+1; $i++)
    {
        push @X, int(rand(255)) + 1;
    }
    for (my $i = 0; $i < $rows+1; $i++)
    {
        push @Y, 0;
    }
    #-------------------------------------------------------------------------------
    my @REF = spmv(\@PTR, \@COL, \@VAL, \@X, $rows); 
    
    my $dat_size = (((($rows+1)*8) + (($nnz*2)*8) + ($cols*8) + ($rows*8)) / 1024) / 1024;
    print sprintf ("\/\/ data size: %0.1f MB\n",$dat_size);
    my $r_size = $rows+1;
    my $c_size = $cols+1;
    #Display header file
    print  "#ifndef __DATASET_H \n";
    print  "#define __DATASET_H\n\n";
    print  "#define NROW ".$r_size." \n";
    print  "#define NCOL ".$c_size." \n";
    print  "#define NNZ " .$nnz." \n\n";
    
    print  "#define DATA_TYPE \n\n";
    
    print  "typedef double data_t;\n\n";
    
    printArray("ptr", \@PTR, "NROW+1", "0", "long");
    printArray("col", \@COL, "NNZ"   , "0", "long");
    printArray("val", \@VAL, "NNZ"   , "14");
    printArray("x"  , \@X  , "NCOL"  , "0" );
    printArray("y"  , \@Y  , "NROW"  , "0" );
    printArray("ref", \@REF, "NROW"  , "14" );

    print "\n#endif //__DATASET_H\n";

    print STDERR sprintf ("Generated data size: %0.1f MB\n",$dat_size),
}

main();
